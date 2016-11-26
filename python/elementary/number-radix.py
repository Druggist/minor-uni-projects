def char_to_int(char):
	return ord(char) - 55

def checkio(str_number, radix):
	number = 0
	for i in range(len(str_number), 0, -1):
		if str_number[len(str_number) - i].isdigit():
			if int(str_number[len(str_number) - i]) >= radix:
				return -1
			number += radix**(i-1) * int(str_number[len(str_number) - i])
		else:
			if char_to_int(str_number[len(str_number) - i]) >= radix:
				return -1
			number += radix**(i-1) * char_to_int(str_number[len(str_number) - i]) 
	return number


#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
	assert checkio("AF", 16) == 175, "Hex"
	assert checkio("101", 2) == 5, "Bin"
	assert checkio("101", 5) == 26, "5 base"
	assert checkio("Z", 36) == 35, "Z base"
	assert checkio("AB", 10) == -1, "B > A > 10"
