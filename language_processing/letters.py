import numpy as np

def markov(n, length, dir):
	file = open(dir)
	text = file.read(100000)
	generated = ""

	letters = {}
	for letter in text:
		if letter not in letters:
			letters.update({letter:0})
		letters[letter] += 1;

	pos = np.random.randint(len(text) - n)
	generated += text[pos:pos+n]

	while len(generated) < length:
		pos = np.random.randint(len(text))
		for x in range(0, len(text)):
			if text[pos:pos+n] == generated[-n:]:
				generated += text[pos+n]
				break
			pos = pos + 1 % (len(text) - n)
	return generated

markov(5, 200, "data/norm_wiki_sample.txt")