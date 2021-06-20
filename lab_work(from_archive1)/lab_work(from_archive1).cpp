#include <iostream>
#include <vector>
#include "/PDCurses-3.8/curses.h"



using namespace std;



int** CreateArray(const int& cols, const int rows)
{
	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[rows];
	}
	return arr;
}
void FillArray(int** arr, const int& cols, const int& rows)
{
	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			arr[i][j] = rand() % 30;
		}
	}
}
void DeleteArray(int** arr, const int& cols, const int& rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[]arr[i];
	}
	delete[] arr;
}



int main()
{

	srand(time(NULL));

	/* Size of matrix */
	const int COLS = 5;
	const int ROWS = 5;

	/* Variables to shift windows */
	int m = 0;
	int n = 0;

	int sum = 0;
	
	int** arr = CreateArray(COLS, ROWS);
	FillArray(arr, COLS, ROWS);

	initscr();

	start_color();

	init_pair(5, COLOR_BLACK, COLOR_WHITE); init_pair(4, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(2, COLOR_BLACK, COLOR_YELLOW); cbreak();

	refresh();


	/* Creating the matrix of windows beforehand */
	vector< vector<WINDOW*> >windows(COLS * ROWS, vector<WINDOW*>(ROWS));
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			windows[i][j] = newwin(3, 5, 1, 1);
		}
	}


	/* Painting red upper secondary diagonal and even numbers in it are painted green*/
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{

			// Upper secondary diagonal
			if ((i + j + 1) == (COLS - 1))
			{
				// painted red
				wbkgd(windows[i][j], COLOR_PAIR(4));

				if (arr[i][j] % 2 == 0)
				{
					// even numbers painted green 
					wbkgd(windows[i][j], COLOR_PAIR(3));
					sum += arr[i][j];
				}

			}
		}
	}


	/* Painting yellow 4th row (and replace all values by sum of all even numbers in secondary diagonal) */
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			arr[3][j] = sum;
			wbkgd(windows[3][j], COLOR_PAIR(2));
		}
	}


	/* Windows output */
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			box(windows[i][j], 0, 0);

			mvwprintw(windows[i][j], 0, 1, "");
			mvwin(windows[i][j], 1 + n, 3 + m); move(2 + n, 5 + m);

			printw("%d", arr[i][j]);
			wrefresh(windows[i][j]);

			m += 8;
		}

		m = 0; // set to zero every loop to keep matrix view
		n += 4; // moving down 4 pixels

	}


	getch();
	endwin();


	 /* Clearing all allocated memory */
	DeleteArray(arr, COLS, ROWS);


	return 0;
}

