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

    get_names()
    fill_dna_profile()
    compare_data()


# Function to get list of names from the database
def get_names():
    # Loop over the rows over the data base and add names to a list by order of insertion
    for i in range(len(mem_database)):
        global names
        names.append(mem_database[i]['name'])


# Fill dna_profile with the longest run of consecutive repeats for each STR
def fill_dna_profile():
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
            if STR[j] == dna_sequence[i:i + current_length]:
                # If there is a match, put that variable to be "on deck" to be matched
                on_deck = STR[j]
                # Iterate over dna_sequence from the next step over, step being the length of the STR
                for m in range(i, len(dna_sequence), current_length):
                    # Keep checking successive repeats
                    if on_deck == dna_sequence[m:m + current_length]:
                        count += 1
                    # If the STR repeats no longer
                    else:
                        # Check if count is bigger than the value for this STR in dna_profile
                        if count > dna_profile[on_deck]:
                            # Set the longest run for the appropriate STR
                            dna_profile[on_deck] = count
                        # Reset variables and break out of loop
                        count = 0
                        on_deck = ''
                        break


# Compares the STR count against each row in the database
def compare_data():
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
            # Increment by 1 if there is a match
            matches += 1
        # Checks if all the STR counts match
        if matches == len(STR):
            print(names[row])
            exit(1)
        # Resets variable
        matches = 0
    # If the STR counts do not match exactly, print this
    print("No match.")


if __name__ == "__main__":
    main(argv)