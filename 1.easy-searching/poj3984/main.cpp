#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;
class coordinate
{
public:
    int x[2];
    coordinate() {}
    coordinate(int _x, int _y)
    {
        x[0] = _x;
        x[1] = _y;
    }
    int &operator[](int index)
    {
        return x[index];
    }
};

int maze[5][5];
int step[5][5];
coordinate father[5][5];

int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

int main()
{
    memset(maze, -1, sizeof(maze));
    memset(step, -1, sizeof(step));
    memset(father, -1, sizeof(father));
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 5; c++)
        {
            cin >> maze[r][c];
        }
    }
    queue<coordinate> q;
    q.push(coordinate(0, 0));
    step[0][0] = 0;
    father[0][0] = coordinate(-1, -1);
    while (!q.empty())
    {
        coordinate current_front = q.front();
        q.pop();
        if (current_front[0] == 4 && current_front[1] == 4)
        {
            while (!q.empty())
            {
                q.pop();
            }
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            coordinate temp = current_front;
            for (int j = 0; j < 2; j++)
            {
                temp[j] += direction[i][j];
            }
            if (temp[0] >= 5 || temp[0] < 0 || temp[1] >= 5 || temp[1] < 0)
            {
                continue;
            }
            if (step[temp[0]][temp[1]] == -1 && !maze[temp[0]][temp[1]])
            {
                step[temp[0]][temp[1]] = step[current_front[0]][current_front[1]] + 1;
                father[temp[0]][temp[1]] = current_front;
                q.push(temp);
            }
        }
    }
    stack<coordinate> s;
    s.push(coordinate(4, 4));
    while (father[(s.top())[0]][(s.top())[1]][0] != -1)
    {
        s.push(father[(s.top())[0]][(s.top())[1]]);
    }
    while (!s.empty())
    {
        cout << "(" << s.top()[0] << ", " << s.top()[1] << ")" << endl;
        s.pop();
    }
}