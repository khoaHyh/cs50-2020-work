# Prints a list of students for a given house in alphabetical order
from cs50 import SQL
from sys import argv

db = SQL("sqlite:///students.db")


def main(argv):
    # Check command-line arguments
    if len(argv) != 2:
        print("Usage: python roster.py House")
        exit(1)

    # Query database for all students in house
    query = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first", str(argv[1]))

    # Return list of dicts
    for row in range(len(query)):
        first_name = query[row]['first']
        middle_name = query[row]['middle']
        last_name = query[row]['last']
        birth_year = query[row]['birth']

        # Check for middle name
        if middle_name == None:
            print(f"{first_name} {last_name}, born {birth_year}")
        else:
            print(f"{first_name} {middle_name} {last_name}, born {birth_year}")


if __name__ == "__main__":
    main(argv)