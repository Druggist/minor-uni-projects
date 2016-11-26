def checkio(data):
	result = ""
	multiplicator = 5000 
	roman = ["M", "D", "C", "L", "X", "V", "I"]
	for x in range(7):
		multiplicator //= 5*((x + 1)%2) + 2*(x%2)
		number = data // multiplicator
		data -= number * multiplicator
		for i in range(number):
			result += roman[x]

		if data >= 900 and data < 1000:
			result += "CM"
			data -= 900
		elif data >= 400 and data < 500:
			result += "CD"
			data -= 400
		elif data >= 90 and data < 100:
			result += "XC"
			data -= 90
		elif data >= 40 and data < 50:
			result += "XL"
			data -= 40
		elif data  == 9:
			result += "IX"
			data -= 9
		elif data == 4:
			result += "IV"
			data -= 4

	return result

if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert checkio(6) == 'VI', '6'
	assert checkio(76) == 'LXXVI', '76'
	assert checkio(499) == 'CDXCIX', '499'
	assert checkio(3888) == 'MMMDCCCLXXXVIII', '3888'