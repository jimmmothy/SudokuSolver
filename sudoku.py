#!/usr/bin/python3

# Solve Sudoku from https://qqwing.com/generate.html
# This solution partly ripped from Computerphile

import sys
import numpy as np

def possible(y, x, n):
	global grid
	for i in range(0, 9):
		if grid[y][i] == n:
			return False

	for i in range(0, 9):
		if grid[i][x] == n:
			return False

	# Use floor here
	x0 = (x//3)*3
	y0 = (y//3)*3
	for i in range(0, 3):
		for j in range(0, 3):
			if grid[y0+i][x0+j] == n:
				return False
	return True

def solve():
	global grid
	for y in range(9):
		for x in range(9):
			if grid[y][x] == 0:
				for n in range(1,10):
					if possible(y,x,n):
						grid[y][x] = n
						if (solve() == True):
							return True
						grid[y][x] = 0
				return
	print(np.matrix(grid))
	return True

def main():
	global grid
	grid = []

	sinput = str(sys.argv[1])

	with open(sinput) as file:
		for line in file:
			tmp_line = []
			for char in line:
				if char == '.':
					tmp_line.append(0)
				elif char.isdigit():
					tmp_line.append(int(char))
			
			if (len(tmp_line) > 0):
				grid.append(tmp_line)

	solve()


if __name__ == '__main__':
	main()