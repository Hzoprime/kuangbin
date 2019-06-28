#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::queue;
using std::set;
using std::string;
using std::swap;
class status
{
public:
    char g[3][3];
    int x_position[2];
    string way;
};
std::ostream &operator<<(std::ostream &out, const status &a)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            out << a.g[i][j] << ' ';
        out << endl;
    }
    return out;
}
bool operator<(const status &a, const status &b)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a.g[i][j] < b.g[i][j])
            {
                return 1;
            }
            else if (a.g[i][j] > b.g[i][j])
            {

                return 0;
            }
        }
    }
    return 0;
}

bool operator==(const status &a, const status &b)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (a.g[i][j] != b.g[i][j])
                return 0;
    return 1;
}

const int directions[][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};
char direction_char[] = "urld";

class solution
{
public:
    static int count;
    status init_status;
    status final_status;

    static set<status> s[9];
    static status mapping_final_status[9];

    solution(string _init_status, string _final_status)
    {
        count++;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                init_status.g[i][j] = _init_status[i * 3 + j];
                final_status.g[i][j] = _final_status[i * 3 + j];
                if (init_status.g[i][j] == 'X')
                {
                    init_status.x_position[0] = i;
                    init_status.x_position[1] = j;
                }
                if (final_status.g[i][j] == 'X')
                {
                    final_status.x_position[0] = i;
                    final_status.x_position[1] = j;
                }
            }
        }
        int position = 0;
        for (position = 0; position < 9; position++)
        {
            if (final_status.x_position[0] == mapping_final_status[position].x_position[0] && final_status.x_position[1] == mapping_final_status[position].x_position[1])
            {
                break;
            }
        }
        memset(has_changed, 0, sizeof(has_changed));
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (final_status.g[i][j] == mapping_final_status[position].g[i][j])
                {
                    continue;
                }
                change(final_status.g[i][j], mapping_final_status[position].g[i][j]);
                final_status.g[i][j] = mapping_final_status[position].g[i][j];
            }
        }
        cout << s[position].size() << endl;
    }
    int has_changed[3][3];

    void change(char from, char to)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (init_status.g[i][j] == from && !has_changed[i][j])
                {
                    init_status.g[i][j] = to;
                    has_changed[i][j] = 1;
                    return;
                }
            }
        }
    }
    static void solve()
    {
        for (int i = 0; i < 9; i++)
        {
            if (i == 8)
            {
                i = 8;
            }
            queue<status> q;
            q.push(mapping_final_status[i]);
            s[i].insert(mapping_final_status[i]);
            while (!q.empty())
            {
                status top = q.front();
                q.pop();
                for (int i = 0; i < 4; i++)
                {
                    status temp = top;
                    if (temp.x_position[0] + directions[i][0] >= 3 || temp.x_position[0] + directions[i][0] < 0 || temp.x_position[1] + directions[i][1] >= 3 || temp.x_position[1] + directions[i][1] < 0)
                    {
                        continue;
                    }
                    swap(
                        temp.g[temp.x_position[0]][temp.x_position[1]],
                        temp.g[temp.x_position[0] + directions[i][0]][temp.x_position[1] + directions[i][1]]);
                    temp.x_position[0] += directions[i][0];
                    temp.x_position[1] += directions[i][1];
                    if (!s[i].count(temp))
                    {
                        temp.way += direction_char[i];
                        s[i].insert(temp);
                        q.push(temp);
                    }
                }
            }
        }
    }
};

int solution::count = 0;

status solution::mapping_final_status[9];
set<status> solution::s[9];
int main()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                solution::mapping_final_status[i].g[j][k] = j * 3 + k + 1 + '0';
            }
        }
        solution::mapping_final_status[i].g[2][2] = 'X';
        swap(solution::mapping_final_status[i].g[2][2], solution::mapping_final_status[i].g[i / 3][i % 3]);
        solution::mapping_final_status[i].x_position[0] = i / 3;
        solution::mapping_final_status[i].x_position[1] = i % 3;
        cout << solution::mapping_final_status[i] << endl;
    }

    solution::solve();
    for (int i = 0; i < 9; i++)
    {
        cout << solution::s[i].size() << endl;
    }

    int n;
    cin >> n;
    string init_status;
    string final_status;
    for (int i = 0; i < n; i++)
    {
        cin >> init_status >> final_status;
        solution(init_status, final_status);
    }
}
