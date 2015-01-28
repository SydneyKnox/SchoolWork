/**------------------------------------------------------------------------------
 * Programmer: Sydney Knox
 * Name: hw3.c
 * Description: Program that allows a user to specify a study room that they would like to "send"
                a small item to, and instructs the "robot" (the '*') to go there and back. Use of
                linked lists and C structures.  The robot navigates the maze using
                "fast paths" if it recognizes a faster route.
 -------------------------------------------------------------------------------**/
#include <stdio.h>
#include <stdlib.h>
#include "useCurses.h"

#include "robotModel.h"
#include "maze.h"

/*Struct time fastTracks to store information on an unknown amount of fast tracks*/
struct fastTracks{
    int numSrs;/*number of study rooms passed by fast track*/
    struct fastTracks *next_fastTrack;/*pointer to the next fast track*/
};



/* function prototype for initializing maze and robot from command line arguments */
int initMazeAndRobotFromCLArgs(int argc, char *argv[], Maze *maze, RobotModel *robot);
/* function prototype for checking for black lines around the robot */
int robotLocationStatus(Maze maze, RobotModel robot);
/* function prototype for reversing robot direction*/
void reverseRobot(RobotModel robot);

int main( int argc, char *argv[] )
{

typedef struct fastTracks FastTracks;/*new name for fastTracks variables*/
typedef struct fastTracks *PtrFT;/*new name for the pointer to a fastTracks struct*/

    /* define variables used in program */
    Maze maze;              /* structure to store track/maze */
    RobotModel robot;       /* structure to model robot (current position + direction) */
    char input;             /* variable to read user input for starting program */
    int user_choice=1;      /* variable to hold user's choice of study room*/
    char choices[300];      /* array to store turns/choices (S,L,R, U)*/
    int choice_num = 0;     /* variable to keep track of the choice number*/
    int i=0;                /* counter variable*/
    int srs_passed=0;       /* variable to count the number of study rooms passed by the robot*/
    PtrFT startPtr=NULL;     /* pointer to point to the beginning of the fast tracks linked list*/
    PtrFT currentPtr=NULL;   /* pointer to use in linked list*/
    int totalStudyRooms=0;     /*variable to hold total number of study rooms*/

    /* initialize curses mode */
    initscr();

    /* print welcome message */
    printw("Welcome to the robot-delivery system.\n");

    /* have user make sure to resize screen first */
    printw("\nResize the screen first (if needed).\n");
    printw("Then press s to start. \n");
    do//keep scanning for input until they enter an 'S'
    {
        scanw("%c", &input);
    }
    while (input != 's');


    /* make sure have successfully have initialized robot and maze
       before doing anything else */
    if (initMazeAndRobotFromCLArgs(argc, argv, &maze, &robot))/*if the initializing was successful*/
    {

        /*point startPtr to a dynamically created memory piece of type FastTracks*/
        /*this will be the first fast track "node"*/
        startPtr = (PtrFT) malloc(sizeof(FastTracks));
        /*set currentPtr to the first fastTrack "node", same as startPtr*/
        currentPtr = startPtr;
        /*set the first fastTrack "node"'s number of study rooms to 0*/
        currentPtr->numSrs=0;


        /*move robot straight one so it isn't on the start position so that it will enter while loop below*/
        moveStraight(&robot);

        /*while the robot is not at the start position (until it makes a full circuit of the map*/
        while(robotLocationStatus(maze, robot) != 123)
        {
            if(robotLocationStatus(maze, robot)== 2)/*if the robot can only go straight*/
            {
                moveStraight(&robot);
            }
            else if(robotLocationStatus(maze, robot)==1)/*if robot can only go left*/
            {
                turnLeft(&robot);
            }
            else if(robotLocationStatus(maze, robot)==3)/*if robot can only go right*/
            {
                turnRight(&robot);
            }
            else if(robotLocationStatus(maze, robot)==12)/*if robot can go left or straight (study room)*/
            {
                moveStraight(&robot);/*while learning the fast tracks, we do not want to enter any study rooms*/
                totalStudyRooms++;
            }
            else if(robotLocationStatus(maze, robot)== 23)/*if robot hits fast track*/
            {
                moveStraight(&robot);/*move robot off of fast track entrance in order to enter while loop*/
                /*while the robot is not at the end of the fast track*/
                while(robotLocationStatus(maze, robot)!=23)
                {
                    if(robotLocationStatus(maze, robot)==2)/*go straight if only option*/
                    {
                        moveStraight(&robot);
                    }
                    else if(robotLocationStatus(maze, robot)==1)/*turn left if only option*/
                    {
                        turnLeft(&robot);
                    }
                    else if(robotLocationStatus(maze, robot)==3)/*turn right if only option*/
                    {
                        turnRight(&robot);
                    }
                    else if(robotLocationStatus(maze, robot)==12)/*if robot is passing a study room*/
                    {
                        /*passing a study room*/
                        (currentPtr->numSrs)++;/*++ count of study rooms for this fast track "node"*/
                        moveStraight(&robot);
                        totalStudyRooms++;
                    }
                }
                /*once robot reaches the fast tracks's exit, move past it one*/
                moveStraight(&robot);

                /*set the fast tracks pointer to a new fast track "node"*/
                currentPtr->next_fastTrack= (PtrFT) malloc(sizeof(FastTracks));
                /*move current pointer to the next fast track node*/
                currentPtr=currentPtr->next_fastTrack;
                /*set new fast track node's pointer to null (in case it is the last fast track)*/
                currentPtr->next_fastTrack=NULL;
                /*set new fast track node's room count to 0*/
                currentPtr->numSrs=0;
            }/*exit fast track option*/
        }/*robot has made a full circuit*/

        printw("Which Study Room would you like to visit? (Press a negative number to exit)\n");/*ask for user's choice of study rooms*/
        scanw("%d", &user_choice);

        while(user_choice==0 || user_choice >totalStudyRooms)
        {
            printw("\nInvalid choice. Choose a number between 1 and %d\n", totalStudyRooms);
            refresh();
            scanw("%d", &user_choice);
        }

        while(user_choice>0)/*if the user's choice is not the exit choice*//*it is set to 1 initially*//*will repeat until user wants to exit*/
        {

             /*initalize choices array*/
            for(i=0;i<300;i++)
                {
                    choices[i]=0;
                }
            /*set the number of study rooms passed to 0-we are at beginning of traversing maze*/
            srs_passed=0;
            /*set the number of choices to 0-none have been made yet*/
            choice_num=0;
            /*set currentPtr = to startPtr- back at the beginning of the study rooms*/
            currentPtr=startPtr;

            while(robotLocationStatus(maze, robot) != 0)/*while the robot is not at a dead end*/
            {
                if(robotLocationStatus(maze, robot)==123)/*if robot is at start position*/
                {
                    moveStraight(&robot);/*move straight*/

                    clear();/*clear screen*/

                    /* print maze + current robot in its current position, wait for user to press a key */
                    printMazePlusCurrentPos(maze, robot);
                    printw("\nPress any button to continue.\n");
                    getch();

                    choices[choice_num]='S';/*record move*/
                    choice_num++;/*increase to next choice number in array*/
                }
                else if(robotLocationStatus(maze, robot)==2)/*if robot can only move straight*/
                {
                    moveStraight(&robot);/*move straight 1*/

                    clear();
                    /* print maze + current robot in its current position, wait for user to press a key */
                    printMazePlusCurrentPos(maze, robot);
                    printw("\nPress any button to continue.\n");
                    getch();

                    choices[choice_num]='S';/*record move*/
                    choice_num++;/*increase to next choice number in array*/
                }
                else if(robotLocationStatus(maze, robot)==12)/*if robot can go left or straight (study room track?)*/
                {
                    srs_passed++;//increase # of study rooms passed to account for one on left

                    if(srs_passed == user_choice)//if the number of study rooms passed is equal to the user's choice of rooms
                    {
                        turnLeft(&robot);//...then turn robot left

                        clear();
                        /* print maze + current robot in its current position, wait for user to press a key */
                        printMazePlusCurrentPos(maze, robot);
                        printw("\nPress any button to continue.\n");
                        getch();

                        choices[choice_num]= 'L';/*store choice in array*/
                        choice_num++;/*increase choice number*/
                    }
                    else
                    {
                        moveStraight(&robot);//pass study room

                        clear();
                        /* print maze + current robot in its current position, wait for user to press a key */
                        printMazePlusCurrentPos(maze, robot);
                        printw("\nPress any button to continue.\n");
                        getch();

                        choices[choice_num]='S';
                        choice_num++;
                    }
                }
                else if(robotLocationStatus(maze, robot)==1)/*if robot can only go left*/
                {
                    turnLeft(&robot);/*turn robot left*/

                    clear();

                    /* print maze + current robot in its current position, wait for user to press a key */
                    printMazePlusCurrentPos(maze, robot);
                    printw("\nPress any button to continue.\n");
                    getch();

                    choices[choice_num]='L';/*record move*/
                    choice_num++;/*increase to next choice number slot in array*/
                }
                else if(robotLocationStatus(maze, robot)==13)/*if robot can go left or right but not straight*/
                {
                    /*when robot is at end of fast track, turn right on way to sr*/
                    turnRight(&robot);/*turn right*/

                    clear();

                    /* print maze + current robot in its current position, wait for user to press a key */
                    printMazePlusCurrentPos(maze, robot);
                    printw("\nPress any button to continue.\n");
                    getch();

                    choices[choice_num]='R';/*record choice*/
                    choice_num++;/*increase choice num*/
                }
                else if(robotLocationStatus(maze, robot)==3)/*if robot can only go right*/
                {
                    turnRight(&robot);/*turn robot right*/

                    clear();
                    /* print maze + current robot in its current position, wait for user to press a key */
                    printMazePlusCurrentPos(maze, robot);
                    printw("\nPress any button to continue.\n");
                    getch();

                    choices[choice_num]='R';/*record move*/
                    choice_num++;/*increase to next choice number slot in array*/
                }
                else if(robotLocationStatus(maze, robot)==23)/*if robot can go right or straight (fast track option)*/
                {

                    if(((currentPtr->numSrs)+srs_passed)<user_choice)/*if the robot is two or less study rooms away from the user_choice, don't take the fast track*/
                    {
                        turnRight(&robot);
                        srs_passed=srs_passed+(currentPtr->numSrs);
                        currentPtr=currentPtr->next_fastTrack;

                        clear();

                        /* print maze + current robot in its current position, wait for user to press a key */
                        printMazePlusCurrentPos(maze, robot);
                        printw("\nPress any button to continue.\n");
                        getch();

                        choices[choice_num]='R';
                        choice_num++;
                    }
                    else/*if the robot is more than 2 study rooms away from the user_choice, take fast track*/
                    {
                        moveStraight(&robot);
                        choices[choice_num]='S';
                        choice_num++;
                        clear();

                        /* print maze + current robot in its current position, wait for user to press a key */
                        printMazePlusCurrentPos(maze, robot);
                        printw("\nPress any button to continue.\n");
                        getch();


                    }

                }
            }

            /*robot has reached a dead end*/

            /*print out choices*/
            refresh();

            clear();
            printMazePlusCurrentPos(maze, robot);

            /*print the choices it took to get to the selected study room*/
            printw("\n\nChoices to get to Study Room %d:", user_choice);
            for(i=0;i<choice_num;i++)
            {
                if((i%20)==0)/*go to a new line every 20 charachters*/
                {
                    printw("\n\t");
                }
                printw("%c ", choices[i]);
            }
            printw("\n\n");

            /*have robot make a u-turn to go back to beginning*/
            uTurn(&robot);

            /*Reverse through previous choices*/
            for(i=(choice_num-1);i>0;i--)
            {
                if(choices[i]=='S')/*if choice to get to study room was 'S', also go straight on the way back*/
                {
                    moveStraight(&robot);
                    printMazePlusCurrentPos(maze, robot);
                    printw("\nPress any button to continue.");
                    getch();
                }
                if(choices[i]=='L')/*if choice to get to study room was 'L', go right on way back*/
                {
                    turnRight(&robot);
                    printMazePlusCurrentPos(maze, robot);
                    printw("\nPress any button to continue.");
                    getch();
                }
                else if(choices[i]=='R')/*if choice to get to study room was 'R', go left on way back*/
                {
                    turnLeft(&robot);
                    printMazePlusCurrentPos(maze, robot);
                    printw("\nPress any button to continue.");
                    getch();
                }
            }

            /*to get back to beginning after going one beyond*/
            uTurn(&robot);
            reverse(&robot);

            refresh();

            /*reprint the choices it took to get to the study room*/
            printw("\n\nChoices to get to Study Room %d:", user_choice);
            for(i=0;i<choice_num;i++)
            {
                if((i%20)==0)
                {
                    printw("\n\t");
                }
                printw("%c ", choices[i]);

            }

            /*print the choices it took to get back from the study room*/
            printw("\n\nChoices to get back from Study Room %d: ", user_choice);
            /*print choice list*/
            for(i=(choice_num-1);i>=0;i--)
            {
                if((i%20)==0)
                {
                    printw("\n\t");
                }
                if(choices[i]=='S')
                {
                    printw(" S");
                }
                else if(choices[i]=='R')
                {
                    printw(" L");
                }
                else if(choices[i]=='L')
                {
                    printw(" R");
                }
            }

            /*give user choice to run program again*/
            printw("\nWhich Study Room would you like to visit? (Press a negative number to exit)\n");/*ask for user's choice of study rooms*/
            scanw("%d", &user_choice);

            while(user_choice==0 || user_choice >totalStudyRooms)
            {
                printw("\nInvalid choice. Choose a number between 1 and %d\n", totalStudyRooms);
                refresh();
                scanw("%d", &user_choice);
            }

        }
        clearMaze(&maze);//clear maze memory

        /*free fast track memory here???????*/

    }
    else
    {
        printw("\nError initializing maze and robot...\n");
        printw("(Check to make sure you are correctly specifying the maze.txt argument.)\n");
    }


    /* print exit message */
    printw("\nThank you for using the robot-delivery system.\n");
    getch();
    endwin();

    return 0;

}

/*-----------------------------------------------------------------------------
 * Function name: initMazeAndRobotFromCLArgs
 * Description: This function uses the specified command-line arguments to
 *              initialize the given Maze and RobotModel variables. If the
 *              incorrect number of command-line arguments is passed, an
 *              error message is displayed (and 0 is returned).
 * Inputs: argc = int = number of command-line arguments
 *         argv = array of strings = command-line arguments, with argv[1]
 *                                   being the input file name
 *         m = Maze * = pointer to Maze structure that should be initialized
 *                      in this function (passed by simulated reference)
 *         robot = RobotModel * = pointer to RobotModel that should be
 *                                initialized in this function (passed by
 *                                simulated reference)
 * Outputs: m = Maze * = pointer to initialized Maze
 *          robot = RobotModel * = pointer to initialized RobotModel
 *          int = 1 if initialization successful
 *                0 if error encountered
 ----------------------------------------------------------------------------*/
int initMazeAndRobotFromCLArgs(int argc, char *argv[], Maze *maze, RobotModel *robot)
{
    int success = 1;
    char *inputFileName;    /* input file name containing maze */
    /* obtain input filename from command line */
    if (argc >= 2) /* require at least two command-line arguments */
    {
        inputFileName = argv[1];
    }
    else
    {
        /* when incorrect number of command-line arguments are passed,
           print message indicating proper usage of program  */
        printf("Usage: %s inputFileName.txt\n", argv[0]);
        success = 0;
    }

    if (success)
    {
        success = readMaze(inputFileName, maze, robot);
    }

    return success;
}

//Function: robotLocationStatus
//Inputs: Maze maze, RobotModel robot
//Ootputs: an integer that represents whether there is black on the left (1), front (2), or right (3) or a combination of these
//         (123), (12), (13), (23).
//Purpose: To return information on the status of black lines in front of, to the right of, or to the left of the robot

int robotLocationStatus(Maze maze, RobotModel robot)
{
    int countr=0;
    /*if there are black lines to the left and right and front of the robot*/
    if(blackToLeft(maze, robot)==1 && blackInFront(maze, robot)==1 && blackToRight(maze, robot)==1)
    {
        countr = 123;
    }
    /*if there are black lines to the left and front of the robot*/
    else if(blackToLeft(maze, robot)==1 && blackInFront(maze, robot)==1 && blackToRight(maze, robot)==0)
    {
        countr = 12;
    }
    /*if there are black lines only to the left of the robot*/
    else if(blackToLeft(maze, robot)==1 && blackInFront(maze, robot)==0 && blackToRight(maze, robot)==0)
    {
        countr = 1;
    }
    /*if there are black lines to the left and right of the robot*/
    else if(blackToLeft(maze, robot)==1 && blackInFront(maze, robot)==0 && blackToRight(maze, robot)==1)
    {
        countr = 13;
    }
    /*if there are black lines to the right only */
    else if(blackToLeft(maze, robot)==0 && blackInFront(maze, robot)==0 && blackToRight(maze, robot)==1)
    {
        countr = 3;
    }
    /*if there are black lines to the front only*/
    else if(blackToLeft(maze, robot)==0 && blackInFront(maze, robot)==1 && blackToRight(maze, robot)==0)
    {
        countr = 2;
    }
    /*if there are black liens to the front and right*/
    else if(blackToLeft(maze, robot)==0 && blackInFront(maze, robot)==1 && blackToRight(maze, robot)==1)
    {
        countr = 23;
    }
    else if(blackToLeft(maze, robot)==0 && blackInFront(maze,robot)==0 && blackToRight(maze,robot)==0)
    {
        countr=0;
    }



    return countr; /*return the areas where the black lines are*/
}

/*********************************************************************
//Function: reverseRobot
//Input: robot, type RobotModel
//Output: void
//Purpose: to reverse the direction of the robot
*********************************************************************/

void reverseRobot(RobotModel robot)
{
    RobotModel *ptr=&robot;

    if(robot.dir==0)
    {
        ptr->dir=2;

    }
    else if(robot.dir==1)
    {
        ptr->dir=3;

    }
    else if(robot.dir==2)
    {
        ptr->dir=0;

    }
    else if(robot.dir==3)
    {
        ptr->dir=1;

    }

}

