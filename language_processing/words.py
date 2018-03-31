import numpy as np
import operator

def wordsFrequency(mostPopular, dir):
	file = open(dir)
	text = file.read()
	words_tmp = text.split(" ")
	words = {}
	count = 0
	for word in words_tmp:
		if word not in words:
			words.update({word:0})
		words[word] += 1;
		count += 1;
	words_sorted = sorted(words.items(), key=operator.itemgetter(1))[::-1]

	return sum(map(operator.itemgetter(1),words_sorted[:mostPopular])) / count

def sentenceGenerator(length, dir):
	file = open(dir)
	text = file.read()
	words_tmp = text.split(" ")
	words = {}
	count = 0
	for word in words_tmp:
		if word not in words:
			words.update({word:0})
		words[word] += 1;
		count += 1;

	probability = [v / count for k,v in  words.items()]
	words = [k for k,v in  words.items()]
	return np.random.choice(words, length, p=probability)

def buildChain(dir,  n, chain = {}):
	file = open(dir);
	text = file.read();
	words = text.split(" ")

	index = n
	for word in words[index:]:
		key = " ".join(words[index - n:index])
		if key in chain:
			chain[key].append(word)
		else:
			chain[key] = [word]
		index += 1
	return chain

def generateText(path, n, length, word = ""):
	chain = buildChain(path, n)
	word1 = np.random.choice(list(chain.keys())) if word == "" else word
	generated = word1.capitalize()

	while len(generated) < length:
		word2 = np.random.choice(chain[word1])
		word1 = " ".join(word1.split(" ")[-(n - 1):]) + " " + word2 if n > 1 else word2
		generated += ' ' + word2
	return generated

print(generateText("data/norm_wiki_sample.txt", 1, 1000, "probability"))
print("\n----------------\n")
print(generateText("data/norm_wiki_sample.txt", 2, 1000, "probability"))