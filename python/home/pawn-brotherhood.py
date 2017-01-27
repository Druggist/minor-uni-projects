def safe_pawns(pawns):
	safe = 0
	for pawn in pawns:
		col = ord(pawn[0]) - ord('a') 
		row = int(pawn[1])
		if row == 1:
			continue
		if col > 0:
			pos = chr(col - 1 + ord('a')) + str(row - 1)
			if pos in pawns:
				safe += 1
				continue
		if col < 7:
			pos = chr(col + 1 + ord('a')) + str(row - 1)
			if pos in pawns:
				safe += 1

	return safe

if __name__ == '__main__':
	#These "asserts" using only for self-checking and not necessary for auto-testing
	assert safe_pawns({"b4", "d4", "f4", "c3", "e3", "g5", "d2"}) == 6
	assert safe_pawns({"b4", "c4", "d4", "e4", "f4", "g4", "e5"}) == 1
