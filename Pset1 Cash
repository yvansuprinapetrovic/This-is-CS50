#include <stdio.h>
#include <cs50.h>
#include <math.h>

int pennies = 1;
int nickles = 5;
int dimes = 10;
int quarters = 25;

int main(void)
{
    // Declaring my variable
    float change;

    // using a do while loop to get a positive float from user
    do
    {
        change = get_float("How much change is owed?\n");
    }
    while (change <= 0);

    // Cents are going to be equal to change * 100 rounded to nearest int
    int cents = round(change * 100);

    // Declaring variable to keep count
    int counter = 0;

    // Using while loops to calculate change
    while (cents >= quarters)
    {
        cents = cents - quarters;
        counter++;
    }
    while (cents >= dimes)
    {
        cents = cents - dimes;
        counter++;
    }
    while (cents >= nickles)
    {
        cents = cents - nickles;
        counter++;
    }
    while (cents >= pennies)
    {
        cents = cents - pennies;
        counter++;
    }

    printf("%i\n", counter);

}
