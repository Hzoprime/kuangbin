#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

const int direction[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

class solution
{
public:
    int m;
    int n;
    char grid[102][102];
    bool visited[102][102];
    int count;
    solution(int _m, int _n) : m(_m), n(_n), count(0)
    {
        init();
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (grid[i][j] == '@' && !visited[i][j])
                {
                    visit(i, j);
                    count++;
                }
            }
        }
        cout << count << endl;
    }
    void visit(int row, int column)
    {
        visited[row][column] = 1;
        for (int i = 0; i < 8; i++)
        {
            if (grid[row + direction[i][0]][column + direction[i][1]] == '@' && !visited[row + direction[i][0]][column + direction[i][1]])
            {
                visit(row + direction[i][0], column + direction[i][1]);
            }
        }
    }
    void init()
    {
        memset(grid, '#', sizeof(grid));
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                cin >> grid[i][j];
            }
        }
    }
};

int main()
{
    int m, n;
    while (cin >> m >> n)
    {
        if (!m)
        {
            break;
        }
        solution(m, n);
    }
}