#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
const int inf = 0x3f3f3f3f;
const int max_size = 20;
class Solution
{
public:
    int a[max_size][max_size];        // save the input
    int b[max_size][max_size];        // temp status matrix
    int temp_res[max_size][max_size]; //temp solution
    int res[max_size][max_size];      // save the solution
    int n;
    int m;
    int temp_count;
    int step_count;
    Solution()
    {
        step_count = inf;
        memset(a, 0, sizeof(int) * max_size * max_size);
        memset(res, 0, sizeof(int) * max_size * max_size);
    }
    void input()
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> a[i][j];
            }
        }
    }
    void run()
    {
        input();
        int total_count = (1 << m);
        for (int s = 0; s < total_count; s++)
        {
            solve(s);
        }
        if (step_count == inf)
        {
            cout << "IMPOSSIBLE" << endl;
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    cout << res[i][j] << " ";
                }
                cout << endl;
            }
        }
    }

    void trans(int r, int c)
    {
        b[r - 1][c] = 1 - b[r - 1][c];
        b[r + 1][c] = 1 - b[r + 1][c];
        b[r][c - 1] = 1 - b[r][c - 1];
        b[r][c + 1] = 1 - b[r][c + 1];
        b[r][c] = 1 - b[r][c];
        temp_res[r][c] += 1;
        temp_count++;
    }

    int solve(int s)
    {
        memset(b, 0, sizeof(int) * max_size * max_size);
        memset(temp_res, 0, sizeof(int) * max_size * max_size);
        memcpy(b, a, sizeof(int) * max_size * max_size);
        temp_count = 0;
        for (int j = 1; j <= m; j++)
        {
            if ((s >> (m - j)) & 1)
            {
                trans(1, j);
            }
        }
        for (int i = 2; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (b[i - 1][j])
                {
                    trans(i, j);
                }
            }
        }
        for (int j = 1; j <= m; j++)
        {
            if (b[n][j])
            {
                return 0;
            }
        }
        if (temp_count < step_count)
        {
            step_count = temp_count;
            memcpy(res, temp_res, sizeof(int) * max_size * max_size);
        }
        return 1;
    }
};

int main()
{
    Solution().run();
}
