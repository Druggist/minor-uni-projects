import numpy as np
from matplotlib import pyplot as plt
from os import listdir

# sample 1, 3 are correct languages

def get_prob_dict(data, n=1, separator=''):
	entries = len(data) - n + 1
	occurs = {}
	for i in range(entries):
		key = separator.join(data[i:i + n])
		if key not in occurs:
			occurs[key] = 0
		occurs[key] += 1
	probs = {}
	for k, v in occurs.items():
		probs[k] = v / entries
	return probs


def get_char_entropy(data, n):
	chars = list(data)
	probs1 = get_prob_dict(chars, n + 1)
	probs0 = get_prob_dict(chars, n)
	ent = 0
	for k, v in probs1.items():
		key = k[:len(k) - 1]
		d = probs0[key]
		ent += v * np.log2(d / v)
	return ent


def get_word_entropy(data, n):
	words = data.split()
	probs1 = get_prob_dict(words, n + 1, separator=' ')
	probs0 = get_prob_dict(words, n, separator=' ')
	ent = 0
	for k, v in probs1.items():
		chain = k.split()
		key = ' '.join(chain[:len(chain) - 1])
		d = probs0[key]
		ent += v * np.log2(d / v)
	return ent


files = listdir("data/entropy")
fig, axarr = plt.subplots(2, 2, sharey='row')
for f in files:
	print("Processing file " + f)
	file = open("data/entropy/" + f)
	data = file.read()
	word_entarr = []
	char_entarr = []
	for i in range(0, 4):
		word_entarr.append(get_word_entropy(data, i))
		char_entarr.append(get_char_entropy(data, i))
		print("*" + str(i) + ": word=" + str(word_entarr[-1]) + " char=" + str(char_entarr[-1]))

	if f.startswith("norm"):
		axarr[0, 0].plot(range(0, 4), word_entarr, label=f)
		axarr[1, 0].plot(range(0, 4), char_entarr, label=f)
	else:
		axarr[0, 1].plot(range(0, 4), word_entarr, label=f)
		axarr[1, 1].plot(range(0, 4), char_entarr, label=f)

axarr[0, 0].set_title("norm word entropy")
axarr[0, 0].legend()
axarr[0, 1].set_title("sample word entropy")
axarr[0, 1].legend()
axarr[1, 0].set_title("norm char entropy")
axarr[1, 0].legend()
axarr[1, 1].set_title("sample char entropy")
axarr[1, 1].legend()
plt.show()