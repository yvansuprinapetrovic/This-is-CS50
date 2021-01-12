from cs50 import get_int


def main():
    # Using a while loop to get a positive integer
    # Loop will break only when input will be an int between 0 and 8
    while True:
        height = get_int("Give me a number bro, I'll make a pyramid! Input height: ")
        width = height
        if height >= 0 and height <= 8:
            break

    # In range function, 1 is the start point and height + 1 is the end point
    for i in range(1, height + 1):

        # Hashes to print are equal to the row number
        hashes = i
        # In each row the sum of hashes and spaces is equal to the user's input
        spaces = width - hashes

        # Printing spaces without new line
        print(" " * spaces, end="")
        # Printing hashes without new line
        print("#" * hashes, end="")

        # Printing two spaces
        print("  ", end="")

        # Printing the other half of the pyramid which doesn't require spaces
        print("#" * hashes)


if __name__ == "__main__":
    main()
