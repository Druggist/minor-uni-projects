import re

def checkio(expression):
	expression = re.sub("([0-9\*\+\-\/])+","",expression)
	i = 1
	if len(expression)%2 == 1:
		return False

	while len(expression) > 0:
		if expression[0] == ")" or expression[0] == "]" or expression[0] == "}":
			return False
		if expression[i] == ")":
			if expression[i-1] != "(":
				return False
			else:
				expression = expression[:i-1] + expression[i+1:]
				i = 0
		elif expression[i] == "]":
			if expression[i-1] != "[":
				return False
			else:
				expression = expression[:i-1] + expression[i+1:]
				i = 0
		elif expression[i] == "}":
			if expression[i-1] != "{":
				return False
			else:
				expression = expression[:i-1] + expression[i+1:]
				i = 0
		i += 1
	return True
	
#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
	assert checkio("((5+3)*2+1)") == True, "Simple"
	assert checkio("{[(3+1)+2]+}") == True, "Different types"
	assert checkio("(3+{1-1)}") == False, ") is alone inside {}"
	assert checkio("[1+1]+(2*2)-{3/3}") == True, "Different operators"
	assert checkio("(({[(((1)-2)+3)-3]/3}-3)") == False, "One is redundant"
	assert checkio("2+3") == True, "No brackets, no problem"
