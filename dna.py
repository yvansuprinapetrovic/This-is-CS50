from sys import argv, exit
import csv
from pathlib import Path
import re

# Checking for the correct command line arg
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# Opening the database in a sequence of lists with reader method
# I chose this over DictReader because it allows me an easier (for me!) comparison between the dna sequences and databases later on
with open (argv[1], newline ="") as database:
    reader = list(csv.reader(database))

# Using pathlib to copy text file contents into a variable and close the file, in just one line!
sequence = Path(argv[2]).read_text()

# Declaring a list to store the STR counts
collection = []

# This loop goes through the first row of the csv file (now a list) starting from position 1 (the first STR)
for i in range(1, len(reader[0])):
    # Using regular expressions to search the dna sequence string. With findall and (?:"pattern") I can identify all the groups of one or more substring patterns
    STR = re.findall(f'(?:{reader[0][i]})+', sequence)

    # Once I have the groups I can use max() to find the longest consecutive streak based on len()
    # Dividing it by the specific STR len() I get the number of repeats
    # Conditional is for limit case where no STR is found
    if STR != []:
        consecutive = len(max(STR, key = len)) // len(reader[0][i])

        # Here I'm just adding the STR count to a list
        collection.append(consecutive)

# Turning my list of integers into a list of strings using map(), so that I can compare with database
collection = list(map(str, collection))

# Creating a new list so that I can safely remove the first item with pop method
database_new = list(reader)
database_new.pop(0)

# Using a for loop to go through the str counts in the database lists
for person in database_new:
    # if csv list, starting from position 1 (so not including name), is equal to STR count list
    if person[1:] == collection:
        # Print item at position 0 of list: name
        print(f"{person[0]}")
        break
    # Else if I've reached the end of the list (list[-1] identifies the very last item of list, using negative numbers you count right to left in list)
    elif person == database_new[-1]:
        print("No match")


# Lists, source: https://www.geeksforgeeks.org/print-lists-in-python-4-different-ways/
# Regular expresions, source: https://stackoverflow.com/questions/61131768/how-to-count-consecutive-substring-in-a-string-in-python-3
# Negative lists, source: https://stackoverflow.com/questions/11367902/negative-list-index#:~:text=Negative%20numbers%20mean%20that%20you,%2Dlast%2C%20and%20so%20on.&text=List%20indexes%20of%20%2Dx%20mean,item%20in%20the%20list%20n%20.
# Map function, source: https://www.geeksforgeeks.org/python-map-function/?ref=leftbar-rightbar
