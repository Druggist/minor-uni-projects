def checkio():
    number = 7734 
    text = "molehill"
    print("The number: " + str(number) + " is the best one!") 
    print("Why?")
    print("Because " + "Do Glatem Live"[::-1] + " is creator of all!")
    print("\n\n Once We were numerous but we are no longer " + str(number))
    print("Last two united 34 and two became one " + str(3+4))
    print("\n\n111 they perished in flames")
    print(str(777 - 111))
    print("\n\nNow we burn in " + text[4] + text[3] + text[7] + text[7])
    return number

checkio()
if __name__ == '__main__':
    # These "asserts" using only for self-checking and not necessary for auto-testing
    assert isinstance(checkio(), (int, float, complex))
