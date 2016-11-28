VOWELS = "aeiouy"

def translate(phrase):
	translation = ''
	while len(phrase) > 0:
		translation += phrase[0]
		if phrase[0] == ' ':
			phrase = phrase[1:]
		elif len(phrase) == 2:
			phrase = ''
		elif phrase[0] not in VOWELS:
			phrase = phrase[2:]
		elif len(phrase) == 3:
			phrase = ''
		elif phrase[0] in VOWELS:
			phrase = phrase[3:]
	return translation

if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert translate("hieeelalaooo") == "hello", "Hi!"
	assert translate("hoooowe yyyooouuu duoooiiine") == "how you doin", "Joey?"
	assert translate("aaa bo cy da eee fe") == "a b c d e f", "Alphabet"
	assert translate("sooooso aaaaaaaaa") == "sos aaa", "Mayday, mayday"
