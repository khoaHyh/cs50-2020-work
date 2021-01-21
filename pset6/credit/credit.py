from cs50 import get_int


def main():
    count = 0
    sum1 = 0
    sum2 = 0

    # Prompt user for credit card number
    while True:
        card_num = get_int("What is your credit card number? ")
        if card_num > 0:
            break

    # Loop over each digit of the credit card and perform the calculations for Luhns
    card_num2 = card_num

    while card_num2 > 0:
        # Get last digit
        digit = card_num2 % 10

        # Distinguish sums from the last digit and second last digit
        if count % 2 == 0:
            sum1 += digit
        else:
            multiplied = digit * 2
            sum2 += (multiplied % 10) + (multiplied // 10)

        card_num2 //= 10
        count += 1

    # Calculate the first digit and first two digits
    divisor = 10
    for i in range(count - 2):
        divisor *= 10

    first_digit = card_num // divisor
    first_two = card_num // (divisor // 10)

    # Check type of card and validity
    luhns = (sum1 + sum2) % 10
    if luhns == 0:
        if first_digit == 4 and (count == 13 or count == 16):
            print("VISA")
        elif (first_two == 34 or first_two == 37) and count == 15:
            print("AMEX")
        elif first_two >= 51 and first_two <= 55 and count == 16:
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()