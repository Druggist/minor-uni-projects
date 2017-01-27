import math

def is_fibonacci(n):
	phi = 0.5 + 0.5 * math.sqrt(5.0)
	a = phi * n
	return n == 0 or abs(round(a) - a) < 1.0 / n

def checkio(opacity):
	current_opacity = 10000
	age = 0
	while opacity != current_opacity:
		age += 1
		if is_fibonacci(age):
			current_opacity -= age
		else:
			current_opacity += 1
	return age

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
	assert checkio(10000) == 0, "Newborn"
	assert checkio(9999) == 1, "1 year"
	assert checkio(9997) == 2, "2 years"
	assert checkio(9994) == 3, "3 years"
	assert checkio(9995) == 4, "4 years"
	assert checkio(9990) == 5, "5 years"