#include <stdio.h>
#include <cs50.h>

//These are among my very first lines of code. Seems little odd but everything good so far. 
// I've declared a variable called name and then using the get_string function I've told the terminal to retrieve a piece of string
//Then using the printf function along the %s placeholder I was able to retrieve the user's output and serve as input for my new string
//Which should print "Hello, yourname"

int main(void)
{
    string name = get_string("What's your name?/n");
    printf("Hello, %s/n", name);
}
