// Program that implements a substitution cipher
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int validate(string key);

int main(int argc, string argv[])
{
    // If a key is provided
    if (argc == 2)
    {
        // Runs the validate function which checks the the validity of the key
        if (validate(argv[1]) == 1)
        {
            return 1;
        }
        else
        {
            // Prompt user for input
            string plain_text = get_string("plaintext: ");

            // Encipher plaintext
            string difference = argv[1];
            for (int i = 'A'; i <= 'Z'; i++)
            {
                // ex. If first letter of key is 'Q', what this does is ('Q' - 'A') and the result is the difference
                difference[i - 'A'] = toupper(difference[i - 'A']) - i;
            }
            printf("ciphertext: ");
            for (int i = 0, n = strlen(plain_text); i < n; i++)
            {
                // If the plaintext is apart of the alphabet it will encipher, otherwise the character is left alone
                if (isalpha(plain_text[i]))
                {
                    // using
                    plain_text[i] = plain_text[i] + difference[plain_text[i] - (isupper(plain_text[i]) ? 'A' : 'a')];
                }
                printf("%c", plain_text[i]);
            }
            printf("\n");
        }
    }
    // If the arguments provided is more than 1
    else if (argc > 2)
    {
        printf("Too many arguments.\n");
        return 1;
    }
    // If no key is provided
    else
    {
        printf("Usage: ./substitution keygoeshere\n");
        return 1;
    }
    return 0;
}

// Function to validate the key
int validate(string key)
{
    int alphabet = 0;
    // Checks if the key contains 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Loop to detect duplicates and check for non alphabetic characters
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        int count = 1;
        // Compares the selected char with the rest of the chars in the string
        for (int j = i + 1; j < strlen(key); j++)
        {
            // If they match, increment counter by 1 and mark duplicates as selected
            if (tolower(key[i]) == tolower(key[j]) && key[i] != ' ')
            {
                count++;
                key[j] = '0';
            }
        }

        // If count > 1, then there are duplicates in the key
        if (count > 1 && key[i] != '0')
        {
            printf("The key provided contains duplicates.\n");
            return 1;
        }
        // Checks if the character in the key is apart of the alphabet
        else if (isalpha(key[i]) == 0)
        {
            printf("Contains a non-alphabetic character.\n");
            return 1;
        }
    }
    return 0;
}