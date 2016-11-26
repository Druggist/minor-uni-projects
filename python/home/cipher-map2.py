def rotate_cipher(cipher_grille):
	new_grille = list(cipher_grille)
	for i in range(len(new_grille)):
		new_grille[i] = new_grille[i].replace("X", ".")

	for i in range(len(cipher_grille)):
		for j in range(len(cipher_grille[0])):	
			if cipher_grille[i][j] == "X":
					temp = list(new_grille[j])
					temp[len(cipher_grille[0]) - 1 - i] = 'X' 
					new_grille[j] = ''.join(temp)

	return new_grille

def recall_password(cipher_grille, ciphered_password):
	password = ""
	for x in range(4):
		for i in range(len(cipher_grille)):
			for j in range(len(cipher_grille[0])):
				if cipher_grille[i][j] == "X":
					password += ciphered_password[i][j]
		cipher_grille = tuple(rotate_cipher(cipher_grille))
				
	return password

print(recall_password(
		('X...',
		 '..X.',
		 'X..X',
		 '....'),
		('itdf',
		 'gdce',
		 'aton',
		 'qrdi')))
if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert recall_password(
		('X...',
		 '..X.',
		 'X..X',
		 '....'),
		('itdf',
		 'gdce',
		 'aton',
		 'qrdi')) == 'icantforgetiddqd', 'First example'

	assert recall_password(
		('....',
		 'X..X',
		 '.X..',
		 '...X'),
		('xhwc',
		 'rsqx',
		 'xqzz',
		 'fyzr')) == 'rxqrwsfzxqxzhczy', 'Second example'
