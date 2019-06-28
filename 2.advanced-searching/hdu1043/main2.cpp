#include <iostream>
#include <cstring>
#include <set>
#include <queue>
#include <string>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::queue;
using std::set;
using std::string;
using std::swap;

const int direction[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const char direction_char[] = "durl";

class status
{
public:
    char g[5][5];
    int x_position[2];
    string way;
    status()
    {
        memset(g, '#', sizeof(g));
        x_position[0] = 0;
        x_position[1] = 0;
    }
};
std::ostream &operator<<(std::ostream &out, const status &a)
{
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            cout << a.g[i][j] << ' ';
        }
        cout << endl;
    }
    return out;
}

bool operator<(const status &a, const status &b)
{
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (a.g[i][j] < b.g[i][j])
            {
                return true;
            }
            else if (a.g[i][j] > b.g[i][j])
            {
                return false;
            }
        }
    }
    return false;
}
bool operator==(const status &a, const status &b)
{
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (a.g[i][j] != b.g[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

class solution
{
public:
    status init_status;
    static status final_status;
    static set<status> s;
    solution(string &st)
    {
        init(st);
        set<status>::iterator result_iterator = s.find(init_status);
        if (result_iterator == s.end())
        {
            cout << "unsolvable" << endl;
        }
        else
        {
            string result = result_iterator->way;
            std::reverse(result.begin(), result.end());
            cout << result << endl;
        }
    }
    void init(string &st)
    {
        int cursor = 0;
        for (int i = 1; i <= 3; i++)
        {
            for (int j = 1; j <= 3; j++)
            {
                while (st[cursor] == ' ')
                    cursor++;
                init_status.g[i][j] = st[cursor++];
                if (init_status.g[i][j] == 'x')
                {
                    init_status.x_position[0] = i;
                    init_status.x_position[1] = j;
                }
            }
        }
    }
    static void solve()
    {
        queue<status> q;
        q.push(final_status);
        s.insert(final_status);
        while (!q.empty())
        {
            status top = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                status temp = top;
                if (temp.x_position[0] + direction[i][0] > 3 || temp.x_position[0] + direction[i][0] < 1 || temp.x_position[1] + direction[i][1] > 3 || temp.x_position[1] + direction[i][1] < 1)
                {
                    continue;
                }
                swap(
                    temp.g[temp.x_position[0]][temp.x_position[1]],
                    temp.g[temp.x_position[0] + direction[i][0]][temp.x_position[1] + direction[i][1]]);
                temp.x_position[0] += direction[i][0];
                temp.x_position[1] += direction[i][1];

                if (!s.count(temp))
                {
                    temp.way += direction_char[i];
                    s.insert(temp);
                    q.push(temp);
                }
            }
        }
    }
};

set<status> solution::s;
status solution::final_status;

int main()
{
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            solution::final_status.g[i][j] = ((i - 1) * 3) + j + '0';
        }
    }
    solution::final_status.g[3][3] = 'x';
    solution::final_status.x_position[0] = 3;
    solution::final_status.x_position[1] = 3;

    solution::solve();

    string st;
    while (getline(cin, st))
    {
        solution a(st);
    }
}
