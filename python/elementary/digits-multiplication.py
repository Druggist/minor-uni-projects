def checkio(number):
	sum = 1
	for digit in str(number):
		if digit != '0':
			sum *= int(digit)

    return sum

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio(123405) == 120
    assert checkio(999) == 729
    assert checkio(1000) == 1
    assert checkio(1111) == 1
