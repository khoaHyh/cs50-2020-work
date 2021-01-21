//added libraries
#include <cs50.h>
#include <stdio.h>

int get_positive_int(void);

int main(void)
{
    int n = get_positive_int();
    for (int i = 0; i < n; i++)
    {
        // print spaces
        for (int j = n - 1; j > i; j--)
        {
            printf(" ");
        }
        // print left hashes
        for (int k = -1; k < i; k++)
        {
            printf("#");
        }
        // print gap
        for (int l = 0; l < 2; l++)
        {
            printf(" ");
        }
        // print right hashes
        for (int m = -1; m < i; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// Get input for Height as postive integer
// between 1 and 8
int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}