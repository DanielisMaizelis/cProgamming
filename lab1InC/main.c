#include <stdio.h>
#include <stdlib.h>


void task1(void);
void task2(void);
void task2_calculate(int *counter, float *prev, float *e, int x);
void task3(void);



int main()
{
    task3();
    return 0;
}


void task1(void)
{
    unsigned int size;
    printf("Enter size of the table:\n");
    scanf("%d",&size);

    printf(" x| ");
    for (int i = 1; i<=size; i++)
        printf("%-5d",i);
    printf("\n");

    for (int i = 0; i < size*5+2; ++i)
        printf("-");
    printf("\n");

    for (int i = 1; i <= size; ++i)
    {
        printf("%-2d| ",i);
        for(int j = 1; j <= size; ++j)
            printf("%-5d", j*i);
        printf("\n");
    }
}

void task2(void)
{
    float e       = 0;
    int   counter = 0;
    float prev;
    int   x;

    // Inputs the index of e
    printf("Enter the value of x: \n");
    scanf("%d",&x);

    // Prints the heading
    printf("%-10s %-10s\n","terms","value");

    // Case if index is 0
    if(x == 0) printf("%-10d %-10d\n",1,1);
    // Case if index is bigger or less than 0
    else
    {
        do task2_calculate(&counter, &prev, &e, x);
        while(e-prev > 0.0000001 || e-prev < 0);
    }
}

// Gets one value of e and adds it to the total e value
void task2_calculate(int *counter, float *prev, float *e, int x)
{
    float valNum = 1;
    float valDen = 1;

    *counter+=1;
    *prev = *e;

    if      (*counter == 1) *e += (float)*counter;
    else if (*counter == 2) *e += (float)x;
    // Case if the counter reaches 3, that way the value is calculated differently
    else
    {
        for (int i = 1; i < *counter; ++i)
        {
            valNum *= (float)x; // Numerator value
            valDen *= (float)i; // Denominator value
        }
        *e += valNum/valDen; // Value is added from -> (numerator value)/(denominator value)
    }
    printf("%-10d %-10f\n", *counter, *e);
}



void task3(void)
{
    long int value;
    char     binaryString[9]; // 8 bits string plus the null terminator
    int  mask2 = 1<<4;
    int  mask3 = 1<<5|1<<2;
    int  mask4 = 1<<0|1<<1;

    // Ask for input
    printf("Enter a binary number: \n");
    scanf("%8s", binaryString); // Limit input to 8 characters to prevent overflow

    // Convert the binary string to a long int
    value          = strtol(binaryString, NULL, 2);

    // Print the conditions
    value            == 0     ? printf("All working\n") : value;
    (value&mask2)    == mask2 ? printf("Fuel level too low\n") : value;
    (value&mask3)    == mask3 ? printf("Snowing outside and the engine is too hot\n") : value;
    ((value&mask4)^mask4) > 0 &&  ((value&mask4)^mask4) < mask4 ?
    printf("Brake fluid is too low or, the brake pads are bad\n") : value;

    // Value
    //0000 0001


    //Mask
    //0000 0011

    //0000 0001
    //0000 0011
    //0000 0010 > 0 and < 0000 0011
    //0000 0011

}
