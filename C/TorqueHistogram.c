//////////////////////////////////////////////////////////////////
//  Programmer: Sydney Knox                                     //
//  Program Name: homework3.1.c                                 //
//  Program Purpose: Generates random force values, uses them   //
//                   to find torque values, finds the frequency //
//                   of these values and prints a histogram.    //
//                   finds the probability of failure.          //
//  Date:3/2/2014                                               //
//////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////
// Function Purpose: to print out a number of X's depending on input   //
// input: an integer, in this program the frequency of a torque value  //
// Output: none                                                        //
//                                                                     //
// This function takes an input value that represents the frequency    //
// of a torque value and prints out a corresponding row of X's.        //
/////////////////////////////////////////////////////////////////////////

void histogram_printer(int i)
{
    int j;

    if(i<10)
    {//This is to ensure the histogram is still in line if the frequency is two-digits
        printf(" ");
    }

    printf("|");//creates histogram baseline

    for(j=0;j<i;j++)
    {
        printf("X");
    }
    printf("\n");
}



int main(void){

    //used to hold a random number to be put into an array
    int number;

    //arrays used
    double force[100];
    double torque[100];
    int frequency[200];
    //counters used
    int i;
    int pass;
    int j=0;
    int counter=0;
    //used in bubble sort to hold values
    double hold=0;
    //The probability of failure
    float probability_of_failure;

    //initialization of arrays
    for(i=0;i<100;i++)
    {
        force[i]=0;
    }
    for(i=0;i<100;i++)
    {
        torque[i]=0;
    }
    for(i=0;i<200;i++)
    {
        frequency[i]=0;
    }

//PART 1&2: Generating random force values
    srand(time(NULL));

    for(i=0;i<100;i++)
    {
        number = rand()%21 +50;
        force[i]=number;
        /*printf("%.2lf lbs.\n", force[i]);*/
    }

//PART 3: Fill in the torque array
    for(i=0;i<100;i++)
    {
        torque[i]=force[i]*2.6;
    }

    /*for(i=0;i<100;i++){
        printf("%.2lf lb*ft\n", torque[i]);
    }*/


//PART 4: Bubble sort the torque array from smallest to largest
    for(pass=0;pass<99;pass++)
    {
        for(i=0;i<99;i++)
        {
            if(torque[i]>torque[i+1])
            {
                hold=torque[i];
                torque[i]=torque[i+1];
                torque[i+1]=hold;
            }
        }
    }

    printf("\n\n\n");

    /*for(i=0;i<100;i++){
        printf("%.2lf lb*ft\n", torque[i]);
    }*/

//PART 5: Create a Histogram of the Torque values and their frequencies

    //This for loop counts the frequency of each torque value and stores it in a frequency array
    for(i=132;i<=180;i++)
    {
        for(j=0;j<100;j++)
        {
            if(torque[j]==i || (torque[j]>i && torque[j]<(i+1)))
            {
                frequency[i]=frequency[i]+1;
            }
        }
    }

   /* for(i=132;i<181;i++){
        printf("%d\n", frequency[i]);
    }*/

    printf("\nTorque (lb*ft)   Frequency   Histogram\n\n");//prints headers

    //prints the values, frequencies, and X's
    for(i=132;i<181;i++)
    {
        printf("%d              %d          ",i,frequency[i]);
        histogram_printer(frequency[i]);//calls function to print X's
    }

//PART 6: Calculate and print the probability of failure

    //counts how many times the torque values are above 175
    for(i=0;i<100;i++)
    {
        if(torque[i]>175)
        {
            counter=counter+1;
        }
    }

    /*printf("\ncounter=%d\n", counter);*/

    //Calculates probability of failure
    probability_of_failure=counter/100.00;

    printf("\nThe probability of failure = %.3f", probability_of_failure);





    return 0;
}
