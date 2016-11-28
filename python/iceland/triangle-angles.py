import math

def checkio(a, b, c):
	result = [0, 0, 0]
	if a + b <= c or a + c <= b or b + c <= a:
	    return result
	result[2] = round(math.degrees(math.acos((a*a + b*b - c*c) / (2.0 * a * b))))
	result[1] = round(math.degrees(math.acos((c*c + a*a - b*b) / (2.0 * c * a))))
	result[0] = round(math.degrees(math.acos((b*b + c*c - a*a) / (2.0 * b * c))))

	return sorted(result)

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
    assert checkio(4, 4, 4) == [60, 60, 60], "All sides are equal"
    assert checkio(3, 4, 5) == [37, 53, 90], "Egyptian triangle"
    assert checkio(2, 2, 5) == [0, 0, 0], "It's can not be a triangle"
