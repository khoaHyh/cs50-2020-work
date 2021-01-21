// checks validity of card number and outputs the type of card if it is valid
#include <stdio.h>
#include <cs50.h>

// test inputs
// Amex: 371449635398431
// Mastercard: 5555555555554444
// Visa: 4222222222222

long get_card_num(void);
int luhns_algorithm(long cn);

int main(void)
{
    // Prompt user for credit card number
    long card_num;
    do
    {
        card_num = get_long("What is your credit card number? ");
    }
    while (card_num < 0);
    // Luhn's algorithm to calculate checksum and check validity
    long sum = 0;
    long sum_2 = 0;
    int count = 0;
    int digit = 0;
    long card_num2 = card_num;

    while (card_num2 > 0)
    {
        digit = card_num2 % 10;

        if (count % 2 == 0)
        {
            // sums up digits that weren't multiplied from last digit
            sum += digit;
        }
        else
        {
            // sums up digits that were multiplied from second last digit
            long x2_digit = digit * 2;
            sum_2 += (x2_digit % 10) + (x2_digit / 10);
        }
        card_num2 /= 10;
        count++;
    }
    int luhns = (sum + sum_2) % 10;
    // Check type of card and validity
    long divisor = 10;
    for (int i = 0; i < count - 2; i++)
    {
        divisor *= 10;
    }

    int first_digit = card_num / divisor;
    int first_two = card_num / (divisor / 10);

    if (luhns == 0)
    {
        if (first_digit == 4 && (count == 13 || count == 16))
        {
            printf("VISA\n");
        }
        else if ((first_two == 34 || first_two == 37) && count == 15)
        {
            printf("AMEX\n");
        }
        else if ((first_two > 50 && first_two < 56) && count == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}