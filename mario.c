#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //declaring my height variable which I want to retrieve from the user with the get_int functio
    int height;

    //using a do-while loop so that I can prompt the user again and again the same question until I get an integer that meets my condition
    do
        {
        height = get_int("How tall should be the pyramid? Give me a number from 1 to 8.\n");
         }
    //this is my condition
    while (height > 8 || height < 1);

    //declaring three variable because the pyramid is built with spaces, hashtags and going to next row
    int i;
    int j;
    int k;

    //Using three nested for loops
    //This loop prints out a new line. The numbers of lines printed out must be equal to the height of the pyramid
    //Hence my condition is linked to the height input 
    for (i = 0; i < height; i++)
    {
    
    //This loop prints the spaces. The number of spaces I need to print per row depends on the height of the pyramid
    //Hence the variable that initializes the loop is set to be equal to the height - 1
    for (k = height - 1 ; k > i ; k--)
        {
            printf(" ");
        }
    
    //This loop is printing #. The number of # I have to print per row is equal to the row number
    //So I'm tying this loop condition to the variable that initializes the for loop printing out new lines
    for (j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
