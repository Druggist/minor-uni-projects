def checkio(time_string):
	time_string = time_string.split(':')
	h = time_string[0] if len(time_string[0]) == 2 else "0" + time_string[0]
	m = time_string[1] if len(time_string[1]) == 2 else "0" + time_string[1]
	s = time_string[2] if len(time_string[2]) == 2 else "0" + time_string[2]
	time_string = h+m+s
	result = ''
	for i in range(len(time_string)):
		binary = str(bin(int(time_string[i])))[2:]
		if len(binary) < 2:
			binary = '0' + binary
		if len(binary) < 3 and i != 0:
			binary = '0' + binary
		if len(binary) < 4 and (i == 1 or i == 3 or i == 5):
			binary = '0' + binary
		for bit in binary:
			if bit == '0':
				result += '.'
			elif bit == '1':
				result += '-'
			
		if i < len(time_string) - 1:
			result += ' '
			if i%2 == 1:
				result += ': '
	return result
	
if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert checkio("10:37:49") == ".- .... : .-- .--- : -.. -..-", "First Test"
	assert checkio("21:34:56") == "-. ...- : .-- .-.. : -.- .--.", "Second Test"
	assert checkio("00:1:02") == ".. .... : ... ...- : ... ..-.", "Third Test"
	assert checkio("23:59:59") == "-. ..-- : -.- -..- : -.- -..-", "Fourth Test"

