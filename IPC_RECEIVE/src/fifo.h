#ifndef FIFO_h
#define FIFO_h

void Write_Server_INFO(int  PID,int CHID){

	 FILE * fp;
	   /* open the file for writing*/
	   fp = fopen ("/tmp/myServer.info","w");
	   fprintf(fp,"%i \n", PID);
	   fprintf(fp,"%i \n", CHID);
	   fclose (fp);
}

void Read_Server_INFO(int *PID,int *CHID){
	FILE * fp = fopen("/net/VM_x86_Target01/tmp/myServer.info", "r");
	  if(fp == 0) {
	    perror("fopen");
	    exit(1);
	}
	  fscanf(fp,"%i",PID);
	  fscanf(fp,"%i",CHID);
	  fclose(fp);
}
#endif
