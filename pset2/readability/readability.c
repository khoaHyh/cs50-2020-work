//Computes the Coleman-Liau index of text input
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string input);
int count_words(string input);
int count_sentences(string input);
double round(double x);
double per_hundred(int total_value, int total_words);

int main(void)
{
    // gets input from user in the form of a string
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // average number of letters per 100 words
    double L = per_hundred(letters, words);
    // average number of sentences per 100 words
    double S = per_hundred(sentences, words);
    // Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Grade level
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Count number of letters from input
int count_letters(string input)
{
    int count = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
        {
            count++;
        }
    }
    return count;
}

// Count number of words from input
int count_words(string input)
{
    int count_words = 1;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (input[i] == ' ')
        {
            count_words++;
        }
    }
    return count_words;
}

// Count number of sentences from input
int count_sentences(string input)
{
    int count_sentences = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            count_sentences++;
        }
    }
    return count_sentences;
}

// calculate per 100 word average
double per_hundred(int total_value, int total_words)
{
    double to_hundred = (double) total_words / 100;
    double per_hundred_avg = (double) total_value / to_hundred;
    return per_hundred_avg;
}