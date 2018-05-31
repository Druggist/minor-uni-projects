from bitarray import bitarray

#Najkrocej na 6 bitach
#Stopien kompresji 25%

def create():
	return

def encode(data, char_map):
	encoded = bitarray()
	for char in data:
		encoded.extend(char_map[char])
	return encoded

def decode(data, bit_map):
	data_bin = data.to01()
	data_bin = data_bin[:(len(data_bin) - len(data_bin)%6)]
	decoded = ""
	for index in range(0, len(data_bin), 6):
		decoded += bit_map[data_bin[index:index + 6]] 
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
	alphabet="abcdefghijklmnopqrstuvwxyz 1234567890"
	char_map = {}
	bit_map = {}
	for index, char in enumerate(alphabet):
		char_map[char] = '{0:06b}'.format(index)

	for char, bits in char_map.items():
		bit_map[bits] = char

	file = open("data/norm_wiki_sample.txt")
	data = file.read()
	file.close()

	encoded = encode(data, char_map)
	save("data.bin", encoded)
	encoded = load("data.bin")
	decoded = decode(encoded, bit_map)

	# print(encoded)
	print(decoded)
	print(data == decoded)

if __name__ == '__main__':
	main()