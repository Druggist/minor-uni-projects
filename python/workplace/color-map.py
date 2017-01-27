def get_neighbours(region, country):
	neighbours = []
	for i in range(len(region)):
		for j in range(len(region[i])):
			if region[i][j] == country:
				if i > 0 and region[i - 1][j] != country and region[i - 1][j] not in neighbours:
					neighbours.append(region[i - 1][j])
				if i < len(region) - 1 and region[i + 1][j] != country and region[i + 1][j] not in neighbours:
					neighbours.append(region[i + 1][j])
				if j > 0 and region[i][j - 1] != country and region[i][j - 1] not in neighbours:
					neighbours.append(region[i][j - 1])
				if j < len(region[i]) - 1 and region[i][j + 1] != country and region[i][j + 1] not in neighbours:
					neighbours.append(region[i][j + 1])
	return sorted(neighbours)

def color_map(region):
	N = max(map(max, region)) + 1
	color = []
	for i in range(N):
		color.append(0)
	for i in range(N):
		neighbours = get_neighbours(region, i)
		occupied_colors = []
		for neighbour in neighbours:
			if color[neighbour] != 0:
				occupied_colors.append(color[neighbour])
		for j in range(1, N + 1):
			if j not in occupied_colors:
				color[i] = j
				break

	return color

if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	NEIGHS = ((-1, 0), (1, 0), (0, 1), (0, -1))
	COLORS = (1, 2, 3, 4)
	ERROR_NOT_FOUND = "Didn't find a color for the country {}"
	ERROR_WRONG_COLOR = "I don't know about the color {}"

	def checker(func, region):
		user_result = func(region)
		if not isinstance(user_result, (tuple, list)):
			print("The result must be a tuple or a list")
			return False
		country_set = set()
		for i, row in enumerate(region):
			for j, cell in enumerate(row):
				country_set.add(cell)
				neighbours = []
				if j < len(row) - 1:
					neighbours.append(region[i][j + 1])
				if i < len(region) - 1:
					neighbours.append(region[i + 1][j])
				try:
					cell_color = user_result[cell]
				except IndexError:
					print(ERROR_NOT_FOUND.format(cell))
					return False
				if cell_color not in COLORS:
					print(ERROR_WRONG_COLOR.format(cell_color))
					return False
				for n in neighbours:
					try:
						n_color = user_result[n]
					except IndexError:
						print(ERROR_NOT_FOUND.format(n))
						return False
					if cell != n and cell_color == n_color:
						print("Same color neighbours.")
						return False
		if len(country_set) != len(user_result):
			print("Excess colors in the result")
			return False
		return True
	assert checker(color_map, (
		(0, 0, 0),
		(0, 1, 1),
		(0, 0, 2),
	)), "Small"
	assert checker(color_map, (
		(0, 0, 2, 3),
		(0, 1, 2, 3),
		(0, 1, 1, 3),
		(0, 0, 0, 0),
	)), "4X4"
	assert checker(color_map, (
		(1, 1, 1, 2, 1, 1),
		(1, 1, 1, 1, 1, 1),
		(1, 1, 0, 1, 1, 1),
		(1, 0, 0, 0, 1, 1),
		(1, 1, 0, 4, 3, 1),
		(1, 1, 1, 3, 3, 3),
		(1, 1, 1, 1, 3, 5),
	)), "6 pack"
