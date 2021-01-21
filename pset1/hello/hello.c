// added libraries
#include <stdio.h>
#include <cs50.h>

// takes in a string input, and uses that as an output with hello world
int main(void)
{
    string name = get_string("What's your name?\n");
    printf("hello, %s\n", name);
}