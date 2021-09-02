#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
#define SUDOKU_SIZE 9

void printGrid(char *grid)
{
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++)
			cout << grid[(y * 9) + x];
		cout << endl;
	}
}

bool isItPossible(int x, int y, char n, char *grid)
{
	for (int q = 0; q < SUDOKU_SIZE; q++)
		if (grid[(q * SUDOKU_SIZE) + x] == n)
			return false;
	
	for (int q = 0; q < SUDOKU_SIZE; q++)
		if (grid[(y * SUDOKU_SIZE) + q] == n)
			return false;
	
	int x0 = floor(x / 3) * 3;
	int y0 = floor(y / 3) * 3;

	for (int q = 0; q < 3; q++)
		for (int w = 0; w < 3; w++)
			if (grid[((y0 + q) * SUDOKU_SIZE) + (x0 + w)] == n)
				return false;

	return true;
}

bool sudokuSolve(char *grid)
{

	for (int y = 0; y < SUDOKU_SIZE; y++)
		for (int x = 0; x < SUDOKU_SIZE; x++)
			if (grid[(y * SUDOKU_SIZE) + x] == '0')
			{
				for (int p = 1; p < SUDOKU_SIZE+1; p++)
					if (isItPossible(x, y, p + '0', grid) == true)
					{	
						grid[(y * SUDOKU_SIZE) + x] = p + '0';

						if (sudokuSolve(grid) == true)
							return true;

						grid[(y * SUDOKU_SIZE) + x] = '0';
					}
				return false;	
			}
	
	return true;
}


int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	ifstream fd;
	fd.open(argv[1]);
	if (!fd)
	{
		cerr << "Error opening file:<<" << (argv[1]);
		return 1;
	}

	string str;
	char *buff = new char[SUDOKU_SIZE * SUDOKU_SIZE];

	int count = 0;
	while (getline(fd, str))
	{
		if (str.size() > 0)
		{
			for (const auto &x: str)
			{
				if (isdigit(x))
				{
					buff[count] = x;
					count++;
				} else if (x == '.')
				{
					buff[count] = '0';
					count++;
				}
			}
		}
	}
	fd.close();
	sudokuSolve(buff);
	printGrid(buff);

	delete[] buff;
	return 0;
}