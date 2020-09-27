#include <stdio.h>
#include <stdlib.h>

enum states { 	State0, State1, State2, State3, State4, State5, State6, State7,
				State8, State9, State10, State11, State12, State13, Emergency};
typedef enum {OFF, RED, YELLOW, GREEN, FLASHING_RED}Traffic_Light_States ;

 struct Intersection_Light_Outputs{
	int north_Light;
	int south_Light;
	int east_Light;
	int west_Light;

	int north_Left_Light;
	int south_Left_Light;
	int east_Left_Light;
	int west_Left_Light;

	int north_Ped_Light;
	int south_Ped_Light;
	int east_Ped_Light;
	int west_Ped_Light;
};


// Prototype functions
/////////////////////////////////////////////////////////////////////////////////////////////////////
void intersection_SM(enum states *current_State);
//void display_output(struct Intersection_Light_Outputs *Light_Output);
void state0_func(struct Intersection_Light_Outputs *Light_Output);
void state1_func(struct Intersection_Light_Output);
void state2_func(struct Intersection_Light_Output);
void state3_func(struct Intersection_Light_Output);
void state4_func(struct Intersection_Light_Output);
void state5_func(struct Intersection_Light_Output);
void state6_func(struct Intersection_Light_Output);
void state7_func(struct Intersection_Light_Output);
void state8_func(struct Intersection_Light_Output);
void state9_func(struct Intersection_Light_Output);
void state10_func(struct Intersection_Light_Output);
void state11_func(struct Intersection_Light_Output);
void state12_func(struct Intersection_Light_Output);
void state13_func(struct Intersection_Light_Output);
///////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void) {
	puts("Hello World!!!"); /* prints Hello World!!! */
	enum states current_state = State0;


	intersection_SM(&current_state);

//create thread --> send structure to thread
	puts("End of program");
	return EXIT_SUCCESS;
}


/* 	State List:

 	state 0 = initial state (all red).
	state 1 = N/S NLeft/SLeft green.
	state 2 = N/S Green. Nleft/SLeft Off. Peds E/W green
	state 3 = N/S Green. E/W Ped flash Red.
	State 4 = N/S Yellow. E/W Ped Hard Red.

	state 5 =
	state 6 =
	state 7 =
	state 8 =

	state 9 = All Red
	state 10 = E/W ELeft/WLeft green.
	state 11 = E/W Green. Eleft/WLeft Off. Peds N/S green
	state 12 = E/W Green. N/S Ped flash Red.
	state 13 = E/W Yellow. N/S Ped Hard Red.

	Emergency =
*/
void intersection_SM(enum states *current_State)
{

	struct Intersection_Light_Outputs Intersection2;

	switch(*current_State)
	{

		case State0:
			//Check if the boom gates are lowered


			state0_func(&Intersection2);
			*current_State = State1;
			break;

		case State1:

			*current_State = State2;
			break;

		case State2:

			*current_State = State3;
			break;

		case State3:

			*current_State = State4;
			break;

		case State4:

			*current_State = State8;
			break;

		case State5:

			*current_State = State6;
			break;

		case State6:

			*current_State = State7;
			break;

		case State7:

			*current_State = State8;
			break;

		case State8:

			*current_State = State9;
			break;

		case State9:

			*current_State = State10;
			break;

		case State10:

			*current_State = State11;
			break;

		case State11:

			*current_State = State12;
			break;
		case State12:

			*current_State = State13;
			break;

		case State13:

			*current_State = State0;
			break;
		case Emergency:

			break;
	}
	display_output(&Intersection2);

}

// Display all the traffic/pedestrian output lights to the console
void display_output(struct Intersection_Light_Outputs *Light_Output){

	printf("North state = %d \n", Light_Output->north_Light);
	printf("South State = %d \n", Light_Output->south_Light);
	printf("East State = %d \n", Light_Output->south_Light);
	printf("West State = %d \n", Light_Output->south_Light);

	printf("North Peds State = %d \n", Light_Output->south_Light);
	printf("South Peds State = %d \n", Light_Output->south_Light);
	printf("East Peds State = %d \n", Light_Output->south_Light);
	printf("West Peds State = %d \n", Light_Output->south_Light);


}
//set light outputs to the corresponding state
void state0_func(struct Intersection_Light_Outputs *Light_Output){
		Light_Output->north_Light = RED;
		Light_Output->south_Light = RED;
		Light_Output->east_Light = RED;
		Light_Output->west_Light = RED;

		Light_Output->north_Left_Light = RED;
		Light_Output->south_Left_Light = RED;
		Light_Output->east_Left_Light = RED;
		Light_Output->west_Left_Light = RED;

		Light_Output->north_Ped_Light = RED;
		Light_Output->south_Ped_Light = RED;
		Light_Output->east_Ped_Light = RED;
		Light_Output->west_Ped_Light = RED;
}
void state1_func(struct Intersection_Light_Outputs *Light_Output){
		Light_Output->north_Light = GREEN;
		Light_Output->south_Light = GREEN;
		Light_Output->east_Light = RED;
		Light_Output->west_Light = RED;

		Light_Output->north_Left_Light = GREEN;
		Light_Output->south_Left_Light = GREEN;
		Light_Output->east_Left_Light = RED;
		Light_Output->west_Left_Light = RED;

		Light_Output->north_Ped_Light = RED;
		Light_Output->south_Ped_Light = RED;
		Light_Output->east_Ped_Light = RED;
		Light_Output->west_Ped_Light = RED;
}

