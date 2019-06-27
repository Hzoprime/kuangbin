#include<iostream>

using namespace std;

char* matrix = 0;
int n = 0;
int number = 0;


bool check(const int& row, const int& column)
{
	for (int i = 0; i < row; i++)
	{
		if (*(matrix + row * n + i) == '*')
		{
			return 0;
		}
		if (*(matrix + i * n + column) == '*')
		{
			return 0;
		}
	}
	return 1;
}

// # empty . not available  * used

void search(int current_row, int current_number, int& total)
{
	if (current_number == number)
	{
		total++;
		return;
	}
	if (current_row == n)
	{
		return;
	}
	for (int i = 0; i < n; i++)
	{
		if (*(matrix + current_row * n + i) == '#')
		{
			// check availability

			if (!check(current_row, i))
			{
				continue;
			}

			*(matrix + current_row * n + i) = '*';
			search(current_row + 1, current_number + 1, total);
			*(matrix + current_row * n + i) = '#';
		}
	}
	search(current_row + 1, current_number, total);
}



int main()
{
	int total = 0;
	while (true)
	{
		cin >> n >> number;
		if (n == -1 || number == -1)
		{
			break;
		}

		matrix = new char[n * n];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> *(matrix + i * n + j);
			}
		}

		search(0, 0, total);
		cout << total << endl;
		total = 0;
		delete[] matrix;
	}
	return 0;
}