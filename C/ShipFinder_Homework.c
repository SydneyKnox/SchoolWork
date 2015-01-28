//Programmer: Sydney Knox
//Program: Homework6.c
//Date: 4/17/14
//Purpose: Create a "ship finder" device. User enters the coordinates of a search
//		   ship and a missing ship, and the program randomly generates moves 
//		   to direct the search ship. Program reports if the missing ship is found,
//		   total distance traveled, and the final coordinates and heading of the 
//		   search ship.
/***********************************************************************************/


#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

//Function: heading
//Input: double x-coordinate, double y-coordinate
//Ouput: double heading in degrees
//Purpose: Find the heading in relation to +y axis
double heading(double x, double y)
{
	double radians=0;
	double degrees=0;

	radians = atan2(x,y);

	degrees = radians*(180/M_PI);

	return degrees;

}


int main(void)
{
	
//For Option 1:
	//Variable set to option chosen by user
	int menu_input=0;

	//Variables for randomly generated direction and distance numbers
	int direction;
	int distance;

	//Variable for number of movements entered by user
	int num_movements;

	//counter
	int i=0;

//For Option 2:
	
	//Variables to hold the starting coordinates of the search ship
	int xcoordinate_start=0;
	int ycoordinate_start=0;

//For Option 3:

	//Variables to hold the coordinates of the missing ship
	int xcoordinate_ship=0;
	int ycoordinate_ship=0;

//For Option 4:

	//Variable to hold the sum of distance traveled
	int totaldistance=0;

	//Variables to keep track of where the search ship is
	int finalx=0;
	int finaly=0;

	//Variables to hold the Distances read in from file
	int distance_r=1;
	int direction_r=1;

	//Variables to ensure options 2 and 3 are done before part 4
	int flagOption1 = 0;
	int flagOption2 = 0;

	//Variable for heading value
	double headingval=0;


//Initialize file
	FILE *filePtr;

//Seed random number generator
	srand(time(NULL));

//Open output.txt file
	if((filePtr = fopen("output.txt", "w"))==NULL)
	{
		printf("Necessary File output.txt could not be opened.\n");
	}

//While loop to ensure switch statement will loop until "Exit" is chosen
	while(menu_input!=5)
	{
		printf("\nPlease select an option:\n\n");
		printf("\n1) Generate and write moves to file (output.txt)\n2) Enter starting robot coordinates\n3) Enter missing vessel coordinates\n4) Read moves from file (output.txt) and search\n5) Exit\n\n");
		scanf("%d", &menu_input);

		//Blocking While loop that ensures valid input
		while(menu_input<1 || menu_input>5)
		{
			printf("\nInvalid input. Please enter 1-5.\n");
			scanf("%d", & menu_input);
		}

		//switch statement for main menu
		switch(menu_input)
		{
			case 1://User enters  many movements they want the ship to make
				   //random howdirections and distances are generated and written to file
				printf("\nHow many movements would you like?\n");
				scanf("%d", &num_movements);

				//blocking while loop to ensure valid input for num_movements
				while(num_movements<1)
				{
					printf("Invalid movement number.  Please enter a number>=1.\n");
					scanf("%d", &num_movements);
				}

				//generates random directions and distances in correct ranges
				for(i=0;i<num_movements;i++)
				{
					direction=rand()%4;
					distance=rand()%11;

					//prints random directions and distances to output.txt file
					fprintf(filePtr,"%d,%d\n\n", direction, distance);

				}

				printf("\nNow please use options 2 and 3 to enter coordinates.\n");
				fclose(filePtr);

				break;

			case 2://User enters the coordinates for the search robot

				printf("\nPlease enter an integer for the x-coordinate of the robot's starting point:\n");
				scanf("%d", &xcoordinate_start);
				printf("\nPlease enter an integer for the y-coordinate of the robot's starting point:\n");
				scanf("%d", &ycoordinate_start);

				//Sets finalx and finaly to chosen coordinates to begin keeping track of robot location
				finalx=xcoordinate_start;
				finaly=ycoordinate_start;

				//ensures that option 2 was selected
				flagOption1=1;

				break;

			case 3://User chooses coordinates for the missing ship

				printf("\nPlease enter an integer for the x-coordinate of the missing ship.\n");
				scanf("%d", &xcoordinate_ship);
				printf("\nPlease enter an integer for the y-coordinate of the missing ship.\n");
				scanf("%d", &ycoordinate_ship);

				//ensures option 3 has been chosen
				flagOption2=1;

				break;

			case 4://Program reads in directions and distances and sees if ship is found
				
				//Ensures that options 2 and 3 were completed
				if(flagOption1!=1 || flagOption2!= 1)
				{
					printf("\nPlease complete options 2 and 3 before moving on to 4.\n\n\n");
					break;
				}

				//opens file for reading
				if((filePtr = fopen("output.txt", "r"))==NULL)
				{
					printf("Necessary File output.txt could not be opened.\n");
				}

				//Loops to read in each set of directions and distances
				for(i=0;i<num_movements;i++)
				{
					fscanf(filePtr, "%d,%d\n\n", &direction_r, &distance_r);

					//uses read directions and distances to adjuct robot location and total distance
					if(direction_r==0)
					{
						finaly=finaly+distance_r;
					}
					if(direction_r==1)
					{
						finaly=finaly-distance_r;
					}
					if(direction_r==2)
					{
						finalx=finalx+distance_r;
					}
					if(direction_r==3)
					{
						finalx=finalx-distance_r;
					}

					totaldistance=totaldistance+distance_r;

					if(finalx>=0)
					{
						headingval= heading(finalx, finaly);
					}
					if(finalx<0 && finaly<0)
					{
						headingval= ((heading(finalx, finaly))*(-1) + 90);
					}
					if(finalx<0 && finaly>0)
					{
						headingval= (360 - (heading(finalx, finaly))*(-1));
					}

					//if ship is found
					if(finalx==xcoordinate_ship && finaly==ycoordinate_ship)
					{
						
						printf("\nFound Ship!\n\nFinal Coordinates: (%d, %d)\n\nTotal Distance: %d\n\nHeading: %lf", finalx, finaly, totaldistance, headingval);
						break;
					}

				}

				//if ship is not found
				printf("\n\nShip not found.\n\nTotal distance traveled: %d", totaldistance);
				printf("\nFinal coordinates of the robot= (%d,%d)\nHeading: %.2lf degrees\n\n", finalx, finaly, headingval);

				break;

			case 5://User chooses "Exit"
				break;
		}
	}

	//close file
	fclose(filePtr);

	return 0;
}
