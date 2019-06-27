#include<iostream>
#include<string.h>
#include<queue>

using std::queue;
using std::cout;
using std::cin;
using std::endl;

class point
{
public:
	point(int _level = -1, int _row = -1, int _column = -1) :level(_level), row(_row), column(_column) {}
	point(const point& _input) :level(_input.level), row(_input.row), column(_input.column) {}
	int level;
	int row;
	int column;
	bool operator==(const point& p)
	{
		return (this->level == p.level) && (this->row == p.row) && (this->column == p.column);
	}
};

const int direction[6][3] = {
	{-1, 0, 0}, {1, 0, 0},
	{0, -1, 0}, {0, 1, 0},
	{0, 0, -1}, {0, 0, 1},
};
const int max_size = 32;

point start, end;

int level, row, column;

char maze[max_size][max_size][max_size];
int steps[max_size][max_size][max_size];

int search()
{
	queue<point> q;
	q.push(start);

	while (!q.empty())
	{
		point current = q.front();
		q.pop();
		int current_step = steps[current.level][current.row][current.column];
		for (int i = 0; i < 6; i++)
		{
			point next = current;
			next.level += direction[i][0];
			next.row += direction[i][1];
			next.column += direction[i][2];
			if (maze[next.level][next.row][next.column] != '#' && steps[next.level][next.row][next.column] == 0)
			{
				steps[next.level][next.row][next.column] = current_step + 1;
				q.push(next);
				if (next == end)
				{
					while (!q.empty())
					{
						q.pop();
					}
					return steps[next.level][next.row][next.column];
				}
			}
		}
	}
	return -1;
}


int main()
{
	while (true)
	{
		cin >> level >> row >> column;

		memset(maze, '#', max_size * max_size * max_size);
		memset(steps, 0, max_size * max_size * max_size);

		if (!(level + row + column))
		{
			return 0;
		}

		for (int i = 1; i < level + 1; i++)
		{
			for (int j = 1; j < row + 1; j++)
			{
				for (int k = 1; k < column + 1; k++)
				{
					cin >> maze[i][j][k];
					if (maze[i][j][k] == 'S')
					{
						start.level = i;
						start.row = j;
						start.column = k;
					}
					if (maze[i][j][k] == 'E')
					{
						end.level = i;
						end.row = j;
						end.column = k;
						maze[i][j][k] = '.';
					}
				}
			}
		}

		if (search() == -1)
		{
			printf("Trapped!\n");
		}
		else
		{
			printf("Escaped in %d minute(s).\n", steps[end.level][end.row][end.column]);
		}
	}
}
