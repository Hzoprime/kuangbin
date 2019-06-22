#include <iostream>
#include <string>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::reverse;
using std::string;

const int max_length = 102;
int mod[max_length];

void init(const int &x)
{
    mod[0] = 1;
    mod[1] = 10 % x;
    mod[2] = 100 % x;
    mod[3] = 1000 % x;
    for (int i = 4; i < max_length; i++)
    {
        mod[i] = (mod[i - 1] * 10) % x;
    }
}

void solve(int x)
{
    init(x);
    int n = 0;
    string result;
    while (++n)
    {
        int current_mod = 0;
        for (int i = 0; i < max_length; i++)
        {
            if ((n >> i) == 0)
            {
                break;
            }
            current_mod += ((n >> i) % 2) * mod[i];
        }
        if ((current_mod % x) == 0)
        {
            for (int i = 0; i < max_length; i++)
            {
                if ((n >> i) == 0)
                {
                    break;
                }
                result += ((n >> i) % 2) ? "1" : "0";
            }
            std::reverse(result.begin(), result.end());
            cout << result << endl;
            break;
        }
    }
}

int main()
{
    int n;
    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }
        solve(n);
    }
}
