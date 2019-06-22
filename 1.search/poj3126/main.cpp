#include <iostream>
#include <cstring>
#include <queue>
using std::cin;
using std::cout;
using std::endl;
using std::queue;
const int maxn = 10000;

const int base[] = {
    1,
    10,
    100,
    1000,
};

int prime[maxn + 1];
bool not_prime[maxn + 1];

void get_prime()
{
    memset(not_prime, 0, sizeof(not_prime));
    memset(prime, 0, sizeof(prime));
    for (int i = 2; i <= (maxn + 1) / 2; i++)
    {
        // cout << " i = " << i << endl;
        if (!not_prime[i])
        {
            prime[++prime[0]] = i; //纪录素数， 这个prime[0] 相当于 cnt，用来计数
        }
        for (int j = 1; j <= prime[0] && i * prime[j] <= maxn; j++)
        {
            not_prime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
            {
                break;
            }
        }
    }
}

int solve(const int &start, const int &end)
{
    queue<int> q;
    int step[maxn + 1];
    memset(step, -1, sizeof(step));
    q.push(start);
    step[start] = 0;
    while (!q.empty())
    {
        int current_top = q.front();
        if (current_top == end)
        {
            break;
        }
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int temp_base = current_top - ((current_top / base[i]) % 10) * base[i];
            for (int j = 0; j < 10; j++)
            {
                int temp = temp_base + base[i] * j;
                if (temp <= maxn && temp >= 1000 && step[temp] == -1 && !not_prime[temp])
                {
                    q.push(temp);
                    step[temp] = step[current_top] + 1;
                }
            }
        }
    }
    while (!q.empty())
    {
        q.pop();
    }
    return step[end];
}

int main()
{
    get_prime();
    int n;
    cin >> n;
    int start, end;
    for (int i = 0; i < n; i++)
    {
        cin >> start >> end;
        cout << solve(start, end) << endl;
    }
}