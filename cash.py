from cs50 import get_float

# Don't need the main function here, just wanted to get used with the syntax
def main():
    # Using a while loop to get a number bigger than 0
    while True:
        change = get_float("How much changed is owed?\n")
        # Calculating the change in cents
        cents = round(change*100)
        if change >= 0:
            break

    # Defining the coins just to remember their values
    pennies = 1
    nickles = 5
    dimes = 10
    quarters = 25
    counter = 0

    # Count the quarters
    while cents >= quarters:
        cents = cents - quarters
        counter += 1

    # Count the dimes
    while cents >= dimes:
        cents = cents - dimes
        counter += 1

    # Count the nickles
    while cents >= nickles:
        cents = cents - nickles
        counter += 1

    # Count the pennies
    while cents >= pennies:
        cents = cents - pennies
        counter += 1

    # Print the minimum number of coins needed
    print(f"{counter}")

# Don't need the main function here, just wanted to get used with the syntax
if __name__ == "__main__":
    main()
