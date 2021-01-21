// Prints out the number of steps in the Collatz conjecture
#include <stdio.h>
#include <cs50.h>

int collatz(int n);

int main(void)
{
    int number = get_int("Enter a number: ");
    printf("collatz(n) = %i\n", collatz(number));
}

// Recursive function to produce number of steps in Collatz conjecture
// Use debug50 with a break point here to understand the output
int collatz(int n)
{
    // base case
    if (n == 1)
        return 0;
    // even numbers
    else if ((n % 2) == 0)
        return 1 + collatz(n / 2);
    // odd numbers
    else
        return 1 + collatz(3 * n + 1);
}