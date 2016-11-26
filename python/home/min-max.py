def min(*args, **kwargs):
	key = kwargs.get("key", lambda x: x)
	min = None
	if len(args) >= 2:
		min = args[0]
		for i in range(1, len(args)):
			min  = args[i] if(key(args[i]) < key(min)) else min
	else:
		arguments = list(args[0]) 
		min = arguments[0]
		for i in range(1, len(arguments)):
			min  = arguments[i] if(key(arguments[i]) < key(min)) else min
	return min


def max(*args, **kwargs):
	key = kwargs.get("key", lambda x: x)
	max = None
	if len(args) >= 2:
		max = args[0]
		for i in range(1, len(args)):
			max  = args[i] if(key(args[i]) > key(max)) else max
	else:
		arguments = list(args[0])
		max = arguments[0]
		for i in range(1, len(arguments)):
			max  = arguments[i] if(key(arguments[i]) > key(max)) else max
	return max

if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert max(3, 2) == 3, "Simple case max"
	assert min(3, 2) == 2, "Simple case min"
	assert max([1, 2, 0, 3, 4]) == 4, "From a list"
	assert min("hello") == "e", "From string"
	assert max(2.2, 5.6, 5.9, key=int) == 5.6, "Two maximal items"
	assert min([[1, 2], [3, 4], [9, 0]], key=lambda x: x[1]) == [9, 0], "lambda key"
