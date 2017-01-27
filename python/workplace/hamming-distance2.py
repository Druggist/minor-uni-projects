def checkio(n, m):
	result = 0
	n = bin(n)[2:]
	m = bin(m)[2:]

	if len(n) > len(m):
		for i in range(len(m),len(n)):
			m = '0' + m
	else:
		for i in range(len(n),len(m)):
			n = '0' + n
	
	for i in range(len(n)):
		if n[i] != m[i]:
			result += 1

	return result

if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert checkio(117, 17) == 3, "First example"
	assert checkio(1, 2) == 2, "Second example"
	assert checkio(16, 15) == 5, "Third example"
