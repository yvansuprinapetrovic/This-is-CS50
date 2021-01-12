#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    // condition to remprompt if user inputs more than one argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // checking for characters in user argument
    int char_count = 0;
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] > 'a' && argv[1][i] < 'z')
        {
            char_count++;
        }
    }
    
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] > 'A' && argv[1][i] < 'Z')
        {
            char_count++;
        }
    }
    
    // condition to reprompt if user unputs a character in argument 
    if (char_count > 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // code to run if user enters a valid key
    else
    {
        // prompting user to give a message to encipher
        string k = get_string("plaintext: ");
        printf("ciphertext: ");
    
        // for loop going through each character of the plaintext
        for (int i = 0, n = strlen(k); i < n; i++)
        {
            // enciphering uppercases
            if (isalpha(k[i]) && isupper(k[i]))
            {
                // indexing ASCII, result will  be 0
                int index = k[i] - 65;
                // using formula 
                index = (index + atoi(argv[1])) % 26;
                // converting back to ASCII
                index = index + 65;
                printf("%c", (char) index);
            }
            // enciphering lowercases
            else if (isalpha(k[i]) && islower(k[i]))
            {
                // indexing ASCII, result will  be 0
                int index = k[i] - 97;
                // using formula 
                index = (index + atoi(argv[1])) % 26;
                // converting back to ASCII
                index = index + 97;
                printf("%c", (char) index);
            }
            // condition that let's me print spaces as spaces and punctuation as punctuation
            else 
            {
                printf("%c", k[i]);
            }
        }
    }
    printf("\n");
}
