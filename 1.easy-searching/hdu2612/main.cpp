/*
 * Some KFC may be not accessible.
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
int min42(const int &a, const int &b)
{
    return a < b ? a : b;
}
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;

class coordinate
{
public:
    int x[2];
    coordinate()
    {
        memset(x, 0, sizeof(x));
    }
    coordinate(int _x, int _y)
    {
        x[0] = _x;
        x[1] = _y;
    }
};

bool operator==(const coordinate &a, const coordinate &b)
{
    return a.x[0] == b.x[0] && a.x[1] == b.x[1];
}
bool operator<(const coordinate &a, const coordinate &b)
{
    return a.x[0] < b.x[0];
}

const int direction[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

class solution
{
public:
    char ningbo_map[202][202];
    unsigned int step2kfc[202][202];
    int n;
    int m;
    vector<coordinate> persons;
    solution(int _n, int _m) : n(_n), m(_m)
    {
        init();
        solve();
    }
    void solve()
    {
        for (int i = 0; i < persons.size(); i++)
        {
            solve_a_person(persons[i]);
        }
        int min_step = 0x3f3f3f3f;
        for (int i = 0; i < 202; i++)
        {
            for (int j = 0; j < 202; j++)
            {
                if(!step2kfc[i][j])
                {
                    continue;
                }
                min_step = min42(min_step, step2kfc[i][j]);
            }
        }
        cout << min_step * 11 << endl;
    }
    void solve_a_person(coordinate &person)
    {
        int step[202][202];
        memset(step, -1, sizeof(step));
        step[person.x[0]][person.x[1]] = 0;
        queue<coordinate> q;
        q.push(person);
        while (!q.empty())
        {
            coordinate top = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                coordinate temp = top;
                for (int j = 0; j < 2; j++)
                {
                    temp.x[j] += direction[i][j];
                }
                if (ningbo_map[temp.x[0]][temp.x[1]] != '#' && step[temp.x[0]][temp.x[1]] == -1)
                {
                    step[temp.x[0]][temp.x[1]] = step[top.x[0]][top.x[1]] + 1;
                    if (ningbo_map[temp.x[0]][temp.x[1]] == '@')
                    {
                        step2kfc[temp.x[0]][temp.x[1]] += step[temp.x[0]][temp.x[1]];
                    }
                    q.push(temp);
                }
            }
        }
    }
    void init()
    {
        memset(ningbo_map, '#', sizeof(ningbo_map));
        memset(step2kfc, 0, sizeof(step2kfc));

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> ningbo_map[i][j];
                if (ningbo_map[i][j] == 'Y' || ningbo_map[i][j] == 'M')
                {
                    persons.push_back(coordinate(i, j));
                }
            }
        }
    }
};
int main()
{
    int n, m;
    while (scanf("%d %d", &n, &m) != EOF)
    {
        solution(n, m);
    }
}
