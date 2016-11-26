def checkio(words):
	words = words.split(' ')
	if len(words) < 3:
		return False

	for i in range(1,len(words) - 1):
		if not words[i-1].isdigit() and not words[i].isdigit() and not words[i+1].isdigit():
			return True
	return False

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
	assert checkio("Hello World hello") == True, "Hello"
	assert checkio("He is 123 man") == False, "123 man"
	assert checkio("1 2 3 4") == False, "Digits"
	assert checkio("bla bla bla bla") == True, "Bla Bla"
	assert checkio("Hi") == False, "Hi"
