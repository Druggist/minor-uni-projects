import math

def friendly_number(number, base=1000, decimals=0, suffix='',
					powers=['', 'k', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y']):
	result = ""
	for i in range(len(powers)):
		if math.fabs(number) / base < 1 or i + 1 == len(powers):
			number = int(number) if decimals == 0 else round(number, decimals)
			format = "{0:."+ str(decimals)+"f}"
			result = str(number) if decimals == 0 else format.format(number)
			result += powers[i] + suffix
			break
		number = (math.fabs(number) // base) * (number // math.fabs(number)) if decimals == 0 else number / base
	return result
print(friendly_number(10**32))

#These "asserts" using only for self-checking and not necessary for auto-testing
if __name__ == '__main__':
	assert friendly_number(102) == '102', '102'
	assert friendly_number(10240) == '10k', '10k'
	assert friendly_number(12341234, decimals=1) == '12.3M', '12.3M'
	assert friendly_number(12461, decimals=1) == '12.5k', '12.5k'
	assert friendly_number(1024000000, base=1024, suffix='iB') == '976MiB', '976MiB'

