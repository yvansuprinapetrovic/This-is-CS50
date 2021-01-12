from cs50 import get_string

# Getting the text to analyze
text = get_string("Insert text here: ")

# Declaring the variables I will be keeping track of
letters = 0
spaces = 0
sentences = 0

# Using a list to look for sentences
punctuation = ['!', '?', '.']

# For loop using the len function to iterate through the text
for i in range (len(text)):
    # Looking for lower case letters
    if text[i] >= 'a' and text[i] <= 'z':
        letters += 1

    # Looking for upper case letters
    if text[i] >= 'A' and text[i] <= 'Z':
        letters += 1

    # Looking for spaces
    if text[i] == ' ':
        spaces += 1

    # Looking for punctuation
    if text[i] in punctuation:
        sentences += 1

    # Words are simply the number of spaces + 1
    words = spaces + 1

# Calculating the variables of the equation and index itself
L = (letters / words) * 100
S = (sentences / words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

# Spitting out the results based on the index calculation
if index >= 16:
    print("Grade 16+")

elif index < 1:
    print("Before Grade 1")

else:
    print(f"Grade {index}")
