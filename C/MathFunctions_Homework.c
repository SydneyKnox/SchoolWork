//********************************************************
//Programmer: Sydney Knox
//Program Name: homework4.c
//Purpose: To create math functions
//Date:3/17/2014-3/26/2014
//*******************************************************/

#include <stdio.h>
#include <math.h>

//Function: factorial
//Purpose: to find the factorial of an entered number
//input: integer/# to factorial
//output: double/ factorialed #
double factorial(int factorial_input)
{

    int i;
    double factorial_output=1;

    for(i=factorial_input;i>=1;i--)
    {
        factorial_output=factorial_output*i;
    }

    return factorial_output;

}

//Function: power
//Purpose: to find a base to a power
//Input: double-base && int-exponent
//output: double- base to the exponent (answer)
double power(double base, int exponent)
{

    int i;
    double power_output=1;

    for(i=0;i<exponent;i++)
    {
            power_output=power_output*base;
    }
    //special case: exponent is 0
    if(exponent==0)
    {
        power_output=1;
    }
    //special case: negative exponents
    if(exponent<0)
    {
        exponent=exponent*-1;

        for(i=0;i<exponent;i++)
        {
            power_output=power_output*base;
        }

        power_output=1.0/power_output;
    }

    return power_output;
}

//Function: cosine_function
//purpose: to find the cosine of an entered angle
//input: double-degrees (the angle in degrees)
//output: double-cosine (the cosine of degrees)
double cosine_function(double degrees)
{

    double radians;
    double cosine=1;
    int negative_factor=-1;
    int i;
    double term_i;

    radians=degrees*(M_PI/180);

    for(i=2;i<=102;i+=2)
    {
        term_i=(power(radians,i)/factorial(i))*negative_factor;
        negative_factor=negative_factor*-1;
        cosine=cosine+term_i;
    }

    return cosine;
}

//Function: sine_function
//purpose: to find the sine of an entered angle
//input: double-degrees (angle in degrees)
//output: double-sine (sine of angle)
double sine_function(double degrees)
{
    double radians;
    double sine=0;
    int negative_factor=1;
    int i;
    double term_i;

    radians=degrees*(M_PI/180);

    for(i=1;i<=101;i+=2)
    {
        term_i=(power(radians,i)/factorial(i))*negative_factor;
        negative_factor=negative_factor*-1;
        sine=sine+term_i;
    }

    return sine;
}

//Function: tangent_function
//Purpose: to find the tangent of an entered angle
//input: double-degrees
//output: double-tangent
double tangent_function(double degrees)
{
    double tangent;

    tangent= sine_function(degrees)/cosine_function(degrees);

    return tangent;
}

int main(void){

    int input=1;
    int fact_input;
    double power_base;
    int power_exponent;
    double degrees;
    double radians;

    while(input!=6)
    {

        printf("\nEnter the number of the function you would like to use:\n");
        printf("\n1. Factorial\n2. power (y=base^exponent)\n3. cosine (y=cosine(x))\n4. sine (y=sine(x))\n5. tangent (y=tangent(x))\n6. Exit\n");
        scanf("%d", &input);

//Protects against invalid input///////////////////////////////////////////
        while(input<1 || input>6)
        {
        printf("\nInvalid Input.  Please enter 1-6:\n");
        scanf("%d", &input);
        }
///////////////////////////////////////////////////////////////////////////
        switch(input)
        {
        case 1://chose factorial

            printf("\nEnter the number you would like to factorial:\n");
            scanf("%d", &fact_input);

            //Protects against invalid input
            while(fact_input<0)
            {
                printf("\nInvalid input.  Please enter a positive number:");
                scanf("%d", &fact_input);
            }
            //if input =0
            if(fact_input==0)
            {
                printf("\nThe factorial of 0 is 0");
            }
            //for normal factorial
            if(fact_input>0)
            {
                printf("\n%d!=%.2lf", fact_input, factorial(fact_input));
            }
            break;

        case 2://chose power
            printf("\nPlease enter the base and the exponent:\n");
            scanf("%lf%d", &power_base, &power_exponent);
            printf("%.2lf^%d=%.6lf", power_base,power_exponent, power(power_base,power_exponent));
            break;

        case 3://chose cosine
            printf("\nPlease enter the angle in degrees:\n");
            scanf("%lf", &degrees);

            radians=degrees*(M_PI/180);

            printf("\nThe cosine of %.2lf degrees according to my cosine function is: %lf", degrees, cosine_function(degrees));
            printf("\nThe cosine of %.2lf degrees according to math.h is: %lf", degrees, cos(radians));
            printf("\nThe difference between the two results is %lf", (cosine_function(degrees))-(cos(radians)));
            break;

        case 4://chose sine
            printf("\nPlease enter the angle in degrees:\n");
            scanf("%lf", &degrees);

            radians=degrees*(M_PI/180);

            printf("\nThe sine of %.2lf degrees according to my sine function is: %lf", degrees, sine_function(degrees));
            printf("\nThe sine of %.2lf degrees according to math.h is: %lf", degrees, sin(radians));
            printf("\nThe difference between the two results is %lf", (sine_function(degrees))-(sin(radians)));
            break;

        case 5://Chose tangent
            printf("\nPlease enter the angle in degrees:\n");
            scanf("%lf", &degrees);

            radians=degrees*(M_PI/180);

            //protects against the times when there is a 0 in the denominator
            if(cos(radians)==0)
            {
                printf("The tangent will go to infinity.\n");
            }

            if(cos(radians)!=0)
            {
                printf("\nThe tangent of %.2lf degrees according to my tangent function is %lf", degrees, tangent_function(degrees));
                printf("\nThe tangent of %.2lf degrees according to math.h is %lf", degrees, tan(radians));
                printf("\nThe difference between the two results is %lf", (tangent_function(degrees))-(tan(radians)));
            }
            break;
        }
    }
    return 0;
}
