from cs50 import get_string


def main():
    # Variables to be used in Coleman-Liau formula
    letters = 0
    words = 1
    sentences = 0

    # Prompt user for text
    text = get_string("Text: ")

    # Loops over text
    for i in range(len(text)):
        # Counts number of letters from input
        if (text[i] >= 'a' and text[i] <= 'z') or (text[i] >= 'A' and text[i] <= 'Z'):
            letters += 1
        # Counts number of words from input
        if text[i] == " ":
            words += 1
        # Counts number of sentences from input
        if text[i] == "." or text[i] == "!" or text[i] == "?":
            sentences += 1

    # Average number of letters per 100 words
    L = per_hundred(letters, words)
    # Average number of sentences per 100 words
    S = per_hundred(sentences, words)
    # Coleman-Liau index
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Grade level
    if index >= 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


# Calculate per 100 word average
def per_hundred(total_value, total_words):
    to_hundred = total_words / 100
    per_hundred_avg = total_value / to_hundred
    return per_hundred_avg


if __name__ == "__main__":
    main()