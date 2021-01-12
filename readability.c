#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>



int main(void)
{
    string text = get_string("Text: \n");
    
    // defining varriables I need to count for the index calculation
    int letters = 0;
    int spaces = 0;
    int sentences = 0;
    
    char punctuation [] = {'!', '.', '?'};
   
    // using a for loop to count letters, spaces and punctuation
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        
        // counting letters
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            letters++;
        }
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            letters++;
        }
      
        // counting spaces
        if (text[i] == ' ')
        {
            spaces++;
        }
        
        // counting sentences
        if (text[i] == punctuation[0] || text[i] == punctuation[1] || text[i] == punctuation[2])
        {
            sentences++;
        }
    }
    // words are simply the sum of spaces plus one 
    int words = spaces + 1;
   
    // using floats as the average can present decimals we don't want to overlook 
    float L = ((float) letters / (float) words) * 100;
    float S = ((float) sentences / (float) words) * 100;
   
    // double or float here is the same 
    double cl_index = round(0.0588 * L - 0.296 * S - 15.8);
   
    // using if and else if to takcle three possible outcomes 
    if (cl_index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (cl_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) cl_index);
    }
}
