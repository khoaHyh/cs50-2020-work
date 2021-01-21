# Imports data from CSV spreadsheet
from cs50 import SQL
from sys import argv, exit
from csv import DictReader

db = SQL("sqlite:///students.db")


def main(argv):
    # Check for CSV file as command-line argument
    if len(argv) != 2:
        print("Usage: python dna.py filename.csv")
        exit(1)

    # Open CSV file and read file contents into memory
    with open(argv[1], "r") as csvFile:
        reader = DictReader(csvFile)

        # Get column names
        column_names = reader.fieldnames

        # Parse through each name and separate into first, middle, last names
        for row in reader:
            name_split = row['name'].split()
            count_names = len(name_split)

            # Assign first, middle, last names
            first_name = name_split[0]
            middle_name = None
            last_name = name_split[1]

            if count_names == 3:
                middle_name = name_split[1]
                last_name = name_split[2]

            # Create student id
            student_id = (reader.line_num - 1)

            # Insert student into students table in the database
            db.execute("INSERT INTO students (id, first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?, ?)",
                       student_id, first_name, middle_name, last_name, row['house'], row['birth'])


if __name__ == "__main__":
    main(argv)