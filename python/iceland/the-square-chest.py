def contains(small, big):
	for el in small:
		if el not in big:
			return False
	return True

def checkio(lines_list):
	result = 0
	temp = []
	for line in lines_list:
		temp.append(sorted(line))
	lines_list = temp
	#big
	square = []
	for i in range(1,4):
		square.append([i, i+1]) 
		square.append([i*4, (i+1) * 4]) 
		square.append([1 + (i-1) * 4, 1 + i * 4]) 
		square.append([12 + i, 13 + i]) 
	if contains(square, lines_list):
		result += 1

	#medium    
	for h in range(2):
		for i in range(2):
			square = []
			for j in range(1,3):
				square.append([i+j + 4*h, i+j+1 + 4*h]) 
				square.append([8 + i+j + 4*h, 9 + i+j + 4*h]) 
				square.append([(1 + i + (j-1) * 4) + 4*h, (1 + i + j*4) + 4*h]) 
				square.append([(3 + i + (j-1) * 4) + 4*h, (3 + i + j*4) + 4*h]) 
			if contains(square, lines_list):
				result += 1

	#small
	for i in range(1, 12):
		square = []
		if i%4 == 0:
			continue
		square.append([i, i+1]) 
		square.append([i + 4, i + 5]) 
		square.append([i, i + 4]) 
		square.append([i + 1, i + 5]) 
		if contains(square, lines_list):
			result += 1

	return result

if __name__ == '__main__':
	assert (checkio([[1, 2], [3, 4], [1, 5], [2, 6], [4, 8], [5, 6], [6, 7],
					 [7, 8], [6, 10], [7, 11], [8, 12], [10, 11],
					 [10, 14], [12, 16], [14, 15], [15, 16]]) == 3), "First, from description"
	assert (checkio([[1, 2], [2, 3], [3, 4], [1, 5], [4, 8],
					 [6, 7], [5, 9], [6, 10], [7, 11], [8, 12],
					 [9, 13], [10, 11], [12, 16], [13, 14], [14, 15], [15, 16]]) == 2), "Second, from description"
	assert (checkio([[1, 2], [1, 5], [2, 6], [5, 6]]) == 1), "Third, one small square"
	assert (checkio([[1, 2], [1, 5], [2, 6], [5, 9], [6, 10], [9, 10]]) == 0), "Fourth, it's not square"
	assert (checkio([[16, 15], [16, 12], [15, 11], [11, 10],
					 [10, 14], [14, 13], [13, 9]]) == 0), "Fifth, snake"