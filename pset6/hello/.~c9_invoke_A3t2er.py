# Import function from cs50 library that takes string inputs


from cs50 import get_string

# Function that gets user's name and prints a message with their input
def get_name():
    n = get_string("What is your name? ")
    print(f"Hello, {n}")


get_name()
