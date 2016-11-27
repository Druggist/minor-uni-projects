def is_palindrom(text):
	for i in range(len(text) // 2):
		if text[i] != text[len(text)-i - 1]:
			return False
	return True

def longest_palindromic(text):
	for i in range(len(text)):
		for j in range(i + 1):
			if is_palindrom(text[j:len(text) + j - i]):
				return text[j:len(text) + j - i]
	return ''

if __name__ == '__main__':
	assert longest_palindromic("artrartrt") == "rtrartr", "The Longest"
	assert longest_palindromic("abacada") == "aba", "The First"
	assert longest_palindromic("aaaa") == "aaaa", "The A"
