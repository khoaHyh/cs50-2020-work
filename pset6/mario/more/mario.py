from cs50 import get_int


def main():
    height = get_height()

    for i in range(height):
        # print spaces
        print(" " * ((height - 1) - i), end="")
        # print left half-pyramid
        print("#" * (i + 1), end="")
        # print gap
        print(" " * (2), end="")
        # print right half-pyramid
        print("#" * (i + 1), end="")
        print()


# Function to get a positive integer between 1 and 8 inclusively from user
def get_height():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n

if __name__ == "__main__":
    main()