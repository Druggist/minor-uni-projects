def verify_anagrams(first_word, second_word):
	first_word = first_word.lower()
	first_word = first_word.replace(' ','')
	first_word = sorted(first_word)
	second_word = second_word.lower()
	second_word = second_word.replace(' ','')
	second_word = sorted(second_word)
	return first_word == second_word

if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert isinstance(verify_anagrams("a", 'z'), bool), "Boolean!"
	assert verify_anagrams("Programming", "Gram Ring Mop") == True, "Gram of code"
	assert verify_anagrams("Hello", "Ole Oh") == False, "Hello! Ole Oh!"
	assert verify_anagrams("Kyoto", "Tokyo") == True, "The global warming crisis of 3002"

