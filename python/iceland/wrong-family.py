
def get_father(kid, tree):
	for connection in tree:
		if connection[1] == kid:
			return connection[0]
	return ''

def is_family(tree):
	family_head = ''
	for connection in tree:
		if [connection[1], connection[0]] in tree:
			return False
		father = get_father(connection[0], tree)
		if father == '':
			if family_head != connection[0] and family_head != '':
				return False
			family_head = connection[0]
		elif [father, connection[1]] in tree:
			return False		
	return True

if __name__ == "__main__":
		#These "asserts" using only for self-checking and not necessary for auto-testing
		assert is_family([
			['Logan', 'Mike']
		]) == True, 'One father, one son'
		assert is_family([
			['Logan', 'Mike'],
			['Logan', 'Jack']
		]) == True, 'Two sons'
		assert is_family([
			['Logan', 'Mike'],
			['Logan', 'Jack'],
			['Mike', 'Alexander']
		]) == True, 'Grandfather'
		assert is_family([
			['Logan', 'Mike'],
			['Logan', 'Jack'],
			['Mike', 'Logan']
		]) == False, 'Can you be a father for your father?'
		assert is_family([
			['Logan', 'Mike'],
			['Logan', 'Jack'],
			['Mike', 'Jack']
		]) == False, 'Can you be a father for your brather?'
		assert is_family([
			['Logan', 'William'],
			['Logan', 'Jack'],
			['Mike', 'Alexander']
		]) == False, 'Looks like Mike is stranger in Logan\'s family'
		print("Looks like you know everything. It is time for 'Check'!")
