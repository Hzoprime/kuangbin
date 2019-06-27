#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <stack>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::stack;
using std::string;
const int max_size = 101;

class status
{
public:
    int x[3];
    status()
    {
        x[0] = -1;
        x[1] = -1;
        x[2] = -1;
    }
    status(int _x, int _y)
    {
        x[0] = -1;
        x[1] = _x;
        x[2] = _y;
    }
    int &operator[](int index)
    {
        return x[index];
    }
};

bool operator==(status &a, status &b)
{
    return a[0] == b[0] && a[1] && b[1];
}

status last[max_size][max_size];
string to_here_operation[max_size][max_size];

int max_l[3];
int target;
void fill(status &a, int index)
{
    a[index] = max_l[index];
}

void drop(status &a, int index)
{
    a[index] = 0;
}

void pour(status &a, int from, int to)
{
    int delta = max_l[to] - a[to];
    if (a[from] >= delta)
    {
        a[to] = max_l[to];
        a[from] -= delta;
    }
    else
    {
        a[to] += a[from];
        a[from] = 0;
    }
}

status solve()
{
    queue<status> q;
    q.push(status(0, 0));
    last[0][0] = status(0, 0);
    while (!q.empty())
    {
        status top = q.front();
        if (top[1] == target || top[2] == target)
        {
            return top;
        }
        q.pop();
        for (int i = 1; i < 3; i++)
        {
            status temp = top;
            fill(temp, i);
            if (last[temp[1]][temp[2]][1] == -1)
            {
                q.push(temp);
                last[temp[1]][temp[2]] = top;
                char str[20];
                sprintf(str, "FILL(%d)", i);
                to_here_operation[temp[1]][temp[2]] = str;
            }
        }
        for (int i = 1; i < 3; i++)
        {
            status temp = top;
            drop(temp, i);
            if (last[temp[1]][temp[2]][1] == -1)
            {
                q.push(temp);
                last[temp[1]][temp[2]] = top;
                char str[20];
                sprintf(str, "DROP(%d)", i);
                to_here_operation[temp[1]][temp[2]] = str;
            }
        }
        for (int i = 1; i < 3; i++)
        {
            status temp = top;
            pour(temp, i, 3 - i);
            if (last[temp[1]][temp[2]][1] == -1)
            {
                q.push(temp);
                last[temp[1]][temp[2]] = top;
                char str[20];
                sprintf(str, "POUR(%d,%d)", i, 3 - i);
                to_here_operation[temp[1]][temp[2]] = str;
            }
        }
    }
    return status();
}

int main()
{
    int a, b, c;
    cin >> max_l[1] >> max_l[2] >> target;
    status result = solve();
    if (result[1] == -1)
    {
        cout << "impossible" << endl;
        return 0;
    }
    stack<string> s;
    while (result[1] != 0 || result[2] != 0)
    {
        s.push(to_here_operation[result[1]][result[2]]);
        result = last[result[1]][result[2]];
    }
    cout << s.size()<<endl;
    while (!s.empty())
    {
        cout << s.top() << endl;
        s.pop();
    }
    
}