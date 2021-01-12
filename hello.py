# Importing the get_string function from cs50 package (python for library)
from cs50 import get_string

# Asking the user to type in his/her name
hello = get_string("What's your name?\n")

# Printing a greeting message interpolating the user's input
print(f"Hello,",hello)
