#Your optional code here
#You can import some modules or create additional functions


def checkio(data):
	unique = set(data)
	if len(data) > len(unique):
		for element in unique:
			if data.count(element) == 1:
				data.remove(element)
		return data
	return []

#Some hints
#You can use list.count(element) method for counting.
#Create new list with non-unique elements
#Loop over original list


if __name__ == "__main__":
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert isinstance(checkio([1]), list), "The result must be a list"
	assert checkio([1, 2, 3, 1, 3]) == [1, 3, 1, 3], "1st example"
	assert checkio([1, 2, 3, 4, 5]) == [], "2nd example"
	assert checkio([5, 5, 5, 5, 5]) == [5, 5, 5, 5, 5], "3rd example"
	assert checkio([10, 9, 10, 10, 9, 8]) == [10, 9, 10, 10, 9], "4th example"
