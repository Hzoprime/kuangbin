#include <iostream>
#include <string>
#include <set>
using namespace std;

int solve();

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << " " << solve() << endl;
    }
}

int solve()
{
    int length;
    cin >> length;
    string s1, s2, s12;
    cin >> s1 >> s2 >> s12;
    string s;
    s.resize(length * 2);
    int step = 0;
    set<string> us;
    while (1)
    {
        for (int i = 0; i < length; i++)
        {
            s[2 * i] = s2[i];
            s[2 * i + 1] = s1[i];
        }
        step++;
        if (s == s12)
        {
            return step;
        }
        if (us.count(s))
        {
            return -1;
        }
        us.insert(s);
        s1 = s.substr(0, length);
        s2 = s.substr(length, length);
    }
}
