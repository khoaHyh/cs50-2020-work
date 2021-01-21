# Implement at program that identifies a person based on their DNA
from csv import DictReader
from sys import argv, exit
import re

# Initialize list of dictionaries in memory to store STR counts for a list of individuals
mem_database = []
# Initialize list in memory to store a DNA sequence
dna_sequence = []
# Initialize list of names that correspond by indices to the database
names = []
# Initialize dictionary of STR counts that gives a DNA profile
dna_profile = {}
# List of all the keys(STRs) used in dna_profile. Used to track current match.
STR = []


def main(argv):
    # Check if there are 3 elements in the command-line input
    if len(argv) != 3:
        print("Usage: python dna.py filename.csv filename.txt")
        exit(1)

    # Open the CSV file and read its contents into memory
    with open(argv[1], "r") as database:

        # Get 'DictReader' object
        read_database = DictReader(database)
        # Get dictionary of STRs
        global dna_profile
        column_names = read_database.fieldnames
        for i in range(1, len(column_names)):
            dna_profile[column_names[i]] = 0
        # Get list of dictionarys from 'DictReader' object
        global mem_database
        mem_database = list(read_database)

    # Open the DNA sequence and read its contents into memory
    with open(argv[2], "r") as sequence:
        # Read text file(dna sequence) into memory
        global dna_sequence
        dna_sequence = sequence.read()

    # Loop over the rows over the data base and add names to a list by order of insertion
    for i in range(len(mem_database)):
        global names
        names.append(mem_database[i]['name'])

    # Set STR list
    global STR
    STR = list(dna_profile)
    # This variable counts the consecutive STR repeats
    count = 0
    # Variable that holds a base to check for repeat
    on_deck = ''

    # Iterate over entire dna sequence
    for i in range(len(dna_sequence)):

        # Iterate over all STRs
        for j in range(len(dna_profile)):

            # Variable to identify length of current STR being matched
            current_length = len(STR[j])

            # Check if any of the STRs exist at position "i"
            if STR[j] != dna_sequence[i:i + current_length]:
                # Adding this here alleviates the pyramid of indentations
                continue

            on_deck = STR[j]

            # Iterate over dna_sequence from the next step over, step being the length of the STR
            for m in range(i, len(dna_sequence), current_length):

                # Keep checking successive repeats
                if on_deck == dna_sequence[m:m + current_length]:
                    count += 1
                else:

                    # Check if count is bigger than the value for this STR in dna_profile
                    if count > dna_profile[on_deck]:
                        dna_profile[on_deck] = count

                    # Reset variables and break out of loop
                    count = 0
                    on_deck = ''
                    break

    # List of STR count values
    compare = list(dna_profile.values())
    # Counts number of matches
    matches = 0
    # Iterate over each row of the database
    for row in range(len(mem_database)):
        # Iterate over each STR of the database
        for column in range(len(dna_profile)):
            # Check for a matching STR count values
            if int(compare[column]) != int(mem_database[row][STR[column]]):
                break

            matches += 1
        # Checks if all the STR counts match
        if matches == len(STR):
            print(names[row])
            exit(1)

        matches = 0

    print("No match.")


if __name__ == "__main__":
    main(argv)