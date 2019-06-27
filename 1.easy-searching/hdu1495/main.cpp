#include <iostream>
#include <cstring>
#include <queue>
using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::queue;
const int max_size = 101;

int matrix[max_size][max_size][max_size];
int max_content[3];

class status
{
public:
    int content[3];
    status(int s, int n, int m)
    {
        content[0] = s;
        content[1] = n;
        content[2] = m;
    }
};

bool operator==(const status &a, const status &b)
{
    for (int i = 0; i < 3; i++)
    {
        if (a.content[i] != b.content[i])
        {
            return 0;
        }
    }
    return 1;
}
void pour(status &current, const int &from, const int &to)
{
    int delta = max_content[to] - current.content[to];
    if (current.content[from] >= delta)
    {
        current.content[from] -= delta;
        current.content[to] = max_content[to];
    }
    else
    {
        current.content[to] += current.content[from];
        current.content[from] = 0;
    }
}

int solve(const int &s, const int &n, const int &m)
{
    max_content[0] = s;
    max_content[1] = n;
    max_content[2] = m;
    memset(matrix, -1, sizeof(matrix));
    queue<status> q;
    q.push(status(s, 0, 0));
    matrix[s][0][0] = 0;
    while (!q.empty())
    {
        status top = q.front();
        q.pop();
        if ((top.content[0] == 0 && top.content[1] == top.content[2] && top.content[1] != 0) || (top.content[1] == 0 && top.content[0] == top.content[2] && top.content[0] != 0) || (top.content[2] == 0 && top.content[1] == top.content[0] && top.content[1] != 0))
        {
            while (!q.empty())
            {
                q.pop();
            }
            return matrix[top.content[0]][top.content[1]][top.content[2]];
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (i == j)
                {
                    continue;
                }
                status temp(top);
                pour(temp, i, j);
                if (matrix[temp.content[0]][temp.content[1]][temp.content[2]] == -1)
                {
                    matrix[temp.content[0]][temp.content[1]][temp.content[2]] = matrix[top.content[0]][top.content[1]][top.content[2]] + 1;
                    q.push(temp);
                }
            }
        }
    }
    while (!q.empty())
    {
        q.pop();
    }
    return -1;
}

int main()
{
    int s, n, m;
    while (1)
    {
        cin >> s >> n >> m;
        if (s == 0)
        {
            break;
        }
        int result = solve(s, n, m);
        if (result != -1)
        {
            cout << result << endl;
        }
        else
        {
            cout << "NO" << endl;
        }
    }
}
