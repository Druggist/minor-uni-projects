
def solve(t, n, trees):
	"""
	Add code solving the problem here...

	:param n:  Number of wells
	:param r: Radii of wells
	:param width: Size of the map
	:param height: Size of the map
	:param quality: Water quality
	:return:
	"""
	x, y = 0, 0
	time = 0
	while time + 1 < t and x + 1 < n and y + 1 < n:
		up = right = 0
		for _x in range(x+1, n):
			if (_x, y) in trees:
				right = _x - x
				break
		for _y in range(y+1, n):
			if (x, _y) in trees:
				up = _y - y
				break
		if right == 0:
			y += 1
			time += 1
			print("move up")
		elif up == 0:
			x += 1
			time += 1
			print("move right")
		elif right < up:
			x += 1
			time += 1
			print("move right")
		else: 
			y += 1
			time += 1
			print("move up")
		

		if (x, y) in trees and time + trees[x, y]['value'] < t:
			left = down = 0
			for _x in range(1,trees[x, y]['height']+1):
				if x - _x < 0:
					break
				if (x - _x, y) in trees:
					if trees[x - _x, y]['weight'] * trees[x - _x, y]['height'] * trees[x - _x, y]['thickness'] < trees[x, y]['weight'] * trees[x, y]['height'] * trees[x, y ]['thickness']:
						left = trees[x - _x, y]['value'] * trees[x - _x, y]['height'] * trees[x - _x, y]['thickness']
					break
			for _y in range(1,trees[x, y]['height']+1):
				if y - _y < 0:
					break
				if (x, y - _y) in trees:
					if trees[x, y - _y]['weight'] * trees[x, y - _y]['height'] * trees[x, y - _y]['thickness']  < trees[x, y]['weight'] * trees[x, y]['height'] * trees[x, y ]['thickness']:
						down = trees[x, y - _y]['value'] * trees[x, y - _y]['height'] * trees[x, y - _y]['thickness'] 
					break

			time += trees[x, y]['thickness']
			_h = trees[x,y]['height']
			to_pop = [y]
			iter = 1
			
			if down >= left:
				print("cut down")
				while iter <= _h:
					if y - iter < 0:
						break
					if (x, y-iter) in trees:
						if trees[x, y - iter]['weight'] * trees[x, y - iter]['height'] * trees[x, y - iter]['thickness'] < trees[x, y]['weight'] * trees[x, y]['height'] * trees[x, y ]['thickness']:
							_h += trees[x, y-iter]['height']
							to_pop.append(y-iter)
						else:
							break 
					iter += 1
				for _y in range(0, len(to_pop)):
					trees.pop(x, to_pop[_y])
			else:
				print("cut left")
				while iter <= _h:
					if x - iter < 0:
						break
					if (x - iter, y) in trees:
						if trees[x- iter, y]['weight'] * trees[x- iter, y]['height'] * trees[x- iter, y]['thickness'] < trees[x, y]['weight'] * trees[x, y]['height'] * trees[x, y ]['thickness']:
							_h += trees[x- iter, y]['height']
							to_pop.append(x-iter)
						else:
							break 
					iter += 1	
				for _x in range(0, len(to_pop)):
					trees.pop(to_pop[_x], y)
				
			


def read_data():
	t, n, k = (int(x) for x in input().split())
	trees = {}
	for i in range(k):
		x, y, h, d, c, p = (int(x) for x in input().split())
		trees[x, y] = {'height' : h, 'thickness' : d, 'weight' : c, 'value' : p}
	return t, n, trees


def main():
	solve(*read_data())


if __name__ == "__main__":
	main()
