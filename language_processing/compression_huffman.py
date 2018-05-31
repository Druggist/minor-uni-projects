from bitarray import bitarray

def create(text):
	letters = {}
	for letter in text:
		if letter not in letters:
			letters.update({letter:0})
		letters[letter] += 1;

	lenght = len(text)

	for k,v in letters.items():
		letters[k] = v / lenght

	return letters

def huffman(p):
	# Base case of only two symbols, assign 0 or 1 arbitrarily
	if(len(p) == 2):
		return dict(zip(p.keys(), ['0', '1']))

	# Create a new distribution by merging lowest prob. pair
	p_prime = p.copy()
	a1, a2 = lowest_prob_pair(p)
	p1, p2 = p_prime.pop(a1), p_prime.pop(a2)
	p_prime[a1 + a2] = p1 + p2

	# Recurse and construct code on new distribution
	c = huffman(p_prime)
	ca1a2 = c.pop(a1 + a2)
	c[a1], c[a2] = ca1a2 + '0', ca1a2 + '1'
	return c


def lowest_prob_pair(p):
	assert(len(p) >= 2)
	sorted_p = sorted(p.items(), key=lambda i: i[1])
	return sorted_p[0][0], sorted_p[1][0]

def encode(data, char_map):
	encoded = bitarray()
	for char in data:
		encoded.extend(char_map[char])
	return encoded

def decode(data, bit_map):
	data_bin = data.to01()
	decoded = ""
	index = 0
	while index < len(data_bin):
		c = 1
		isChar = False
		while isChar != True:
			if index + c <= len(data_bin):
				if data_bin[index:index + c] in bit_map:
					decoded += bit_map[data_bin[index:index + c]] 
					isChar = True
					index += c
			else:
				index += c
				isChar = True
			c += 1
	return decoded

def save(path, data):
	file = open(path, 'wb')
	data.tofile(file)
	file.close()

def load(path):
	data = bitarray()
	file = open(path, 'rb')
	data.fromfile(file)
	file.close()
	return data

def main():
	file = open("data/norm_wiki_sample.txt")
	data = file.read()
	file.close()

	char_map = huffman(create(data))
	bit_map = {}

	for char, bits in char_map.items():
		bit_map[bits] = char

	encoded = encode(data, char_map)
	save("data.bin", encoded)
	encoded = load("data.bin")
	decoded = decode(encoded, bit_map)

	print(data == decoded)

if __name__ == '__main__':
	main()