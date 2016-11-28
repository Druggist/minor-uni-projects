def next_state(state):
	return [state[-1]] + state[:-1]

def rotate(state, pipe_numbers):
	result = []
	for i in range(len(state)):
		wrong  = False
		for pipe in pipe_numbers:
			if state[pipe] == 0:
				wrong = True
				break
		if not wrong:
			result.append(i)
		state = next_state(state)
	return result


if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert rotate([1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1], [0, 1]) == [1, 8], "Example"
	assert rotate([1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1], [0, 1, 2]) == [], "Mission impossible"
	assert rotate([1, 0, 0, 0, 1, 1, 0, 1], [0, 4, 5]) == [0], "Don't touch it"
	assert rotate([1, 0, 0, 0, 1, 1, 0, 1], [5, 4, 5]) == [0, 5], "Two cannonballs in the same pipe"
