#include <iostream>
#include <queue>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
const int max_n = 100001;

int main()
{
    int n, k, step[max_n], vis[max_n];
    queue<int> *q;
    int current;
    int next;
    while (cin >> n >> k)
    {
        memset(step, 0, sizeof(int) * max_n);
        memset(vis, 0, sizeof(int) * max_n);
        if (n == k)
        {
            cout << 0 << endl;
            continue;
        }
        step[n] = 0;
        current = n;
        q = new queue<int>();
        q->push(n);
        while (!q->empty())
        {
            current = q->front();
            q->pop();
            for (int i = 0; i < 3; i++)
            {
                if (i == 0)
                    next = current + 1;
                else if (i == 1)
                    next = current - 1;
                else
                    next = current * 2;
                if (next < 0 || next > max_n)
                    continue;
                if (vis[next])
                    continue;
                vis[next] = 1;
                step[next] = step[current] + 1;
                q->push(next);
                if (next == k)
                {
                    cout << step[k] << endl;
                    while (!q->empty())
                    {
                        q->pop();
                    }
                    break;
                }
            }
        }
        delete q;
    }
}