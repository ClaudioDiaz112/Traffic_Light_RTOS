
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include"IPC.h"
#include <sys/dispatch.h>

void *Client(void *data) {
    my_data msg;

    my_reply reply; // replymsg structure for sending back to client

    msg.ClientID = 600;      // unique number for this client
    msg.hdr.type = 0x22;     // We would have pre-defined data to stuff here

    msg.ClientID = 600; 	 // unique number for this client

    int server_coid;
    int index = 0;

    printf("  ---> Trying to connect to server named: %s\n", QNET_ATTACH_POINT);
    if ((server_coid = name_open(QNET_ATTACH_POINT, 0)) == -1)
    {
        printf("\n    ERROR, could not connect to server!\n\n");
        return EXIT_FAILURE;
    }

    printf("Connection established to: %s\n", QNET_ATTACH_POINT);

    // Do whatever work you wanted with server connection
    for (index=0; index < 5; index++) // send data packets
    {
    	// set up data packet
    	msg.data=10+index;

    	// the data we are sending is in msg.data
        printf("Client (ID:%d), sending data packet with the integer value: %d \n", msg.ClientID, msg.data);
        fflush(stdout);

        if (MsgSend(server_coid, &msg, sizeof(msg), &reply, sizeof(reply)) == -1)
        {
            printf(" Error data '%d' NOT sent to server\n", msg.data);
            	// maybe we did not get a reply from the server
            break;
        }
        else
        { // now process the reply
            printf("   -->Reply is: '%s'\n", reply.buf);
        }

        //sleep(5);	// wait a few seconds before sending the next data packet
    }

    // Close the connection
    printf("\n Sending message to server to tell it to close the connection\n");
    name_close(server_coid);

    return EXIT_SUCCESS;
}

void *Server(void *data) {
	printf("_mysigval size= %d\n", sizeof(_mysigval));
	printf("header size= %d\n", sizeof(msg_header_t));
	printf("my_data size= %d\n", sizeof(my_data));
	printf("my_reply size= %d\n", sizeof(my_reply));

   name_attach_t *attach;

   my_data msg;
    my_reply replymsg; // replymsg structure for sending back to client

    replymsg.hdr.type = 0x01;       // some number to help client process reply msg
    replymsg.hdr.subtype = 0x00;    // some number to help client process reply msg
    // Create a global name (/dev/name/local/...)
    if ((attach = name_attach(NULL, ATTACH_POINT, 0)) == NULL)
    // Create a global name (/dev/name/global/...)
    //if ((attach = name_attach(NULL, ATTACH_POINT, NAME_FLAG_ATTACH_GLOBAL)) == NULL)
    {
    	printf("\nFailed to name_attach on ATTACH_POINT: %s \n", ATTACH_POINT);
    	printf("\n Possibly another server with the same name is already running or you need to start the gns service!\n");
    	return EXIT_FAILURE;

    }


    printf("Server Listening for Clients on ATTACH_POINT: %s \n", ATTACH_POINT);

    	/*
 	 *  Server Loop
 	 */
    int rcvid=0, msgnum=0;  		// no message received yet
    int Stay_alive=0, living=0;	// server stays running (ignores _PULSE_CODE_DISCONNECT request)
    living =1;
    while (living)
    {
 	   // Do your MsgReceive's here now with the chid
        rcvid = MsgReceive(attach->chid, &msg, sizeof(msg), NULL);

        if (rcvid == -1)  // Error condition, exit
        {
            printf("\nFailed to MsgReceive\n");
            break;
        }

        // did we receive a Pulse or message?
        // for Pulses:
        if (rcvid == 0)  //  Pulse received, work out what type
        {
 		   printf("\nServer received a pulse from ClientID:%d ...\n", msg.ClientID);
 		   printf("Pulse received:%d \n", msg.hdr.code);

            switch (msg.hdr.code)
            {
 			   case _PULSE_CODE_DISCONNECT:
 				   printf("Pulse case:    %d \n", _PULSE_CODE_DISCONNECT);
 					// A client disconnected all its connections by running
 					// name_close() for each name_open()  or terminated
 				   if( Stay_alive == 0)
 				   {
 					   ConnectDetach(msg.hdr.scoid);
 					   printf("\nServer was told to Detach from ClientID:%d ...\n", msg.ClientID);
 					   living = 0; // kill while loop
 					   continue;
 				   }
 				   else
 				   {
 					   printf("\nServer received Detach pulse from ClientID:%d but rejected it ...\n", msg.ClientID);
 				   }
 				   break;

 			   case _PULSE_CODE_UNBLOCK:
 					// REPLY blocked client wants to unblock (was hit by a signal
 					// or timed out).  It's up to you if you reply now or later.
 				   printf("\nServer got _PULSE_CODE_UNBLOCK after %d, msgnum\n", msgnum);
 				   break;

 			   case _PULSE_CODE_COIDDEATH:  // from the kernel
 				   printf("\nServer got _PULSE_CODE_COIDDEATH after %d, msgnum\n", msgnum);
 				   break;

 			   case _PULSE_CODE_THREADDEATH: // from the kernel
 				   printf("\nServer got _PULSE_CODE_THREADDEATH after %d, msgnum\n", msgnum);
 				   break;

 			   default:
 				   // Some other pulse sent by one of your processes or the kernel
 				   printf("\nServer got some other pulse after %d, msgnum\n", msgnum);
 				   break;

            }
            continue;// go back to top of while loop
        }

        // for messages:
        if(rcvid > 0) // if true then A message was received
        {
 		   msgnum++;

 		   // If the Global Name Service (gns) is running, name_open() sends a connect message. The server must EOK it.
 		   if (msg.hdr.type == _IO_CONNECT )
 		   {
 			   MsgReply( rcvid, EOK, NULL, 0 );
 			   printf("\nClient messaged indicating that GNS service is running....");
 			   printf("\n    -----> replying with: EOK\n");
 			   msgnum--;
 			   continue;	// go back to top of while loop
 		   }

 		   // Some other I/O message was received; reject it
 		   if (msg.hdr.type > _IO_BASE && msg.hdr.type <= _IO_MAX )
 		   {
 			   MsgError( rcvid, ENOSYS );
 			   printf("\n Server received and IO message and rejected it....");
 			   continue;	// go back to top of while loop
 		   }

 		   // A message (presumably ours) received

 		   // put your message handling code here and assemble a reply message
 		   sprintf(replymsg.buf, "Message %d received", msgnum);
 		   printf("Server received data packet with value of '%d' from client (ID:%d), ", msg.data, msg.ClientID);
 		   	   fflush(stdout);
 		   	  // sleep(1); // Delay the reply by a second (just for demonstration purposes)

 		   printf("\n    -----> replying with: '%s'\n",replymsg.buf);
 		   MsgReply(rcvid, EOK, &replymsg, sizeof(replymsg));
        }
        else
        {
 		   printf("\nERROR: Server received something, but could not handle it correctly\n");
        }

    }

    // Remove the attach point name from the file system (i.e. /dev/name/local/<myname>)
    name_detach(attach, 0);

    return EXIT_SUCCESS;
	return NULL;
}







