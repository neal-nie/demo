/* Leetcode 60 */

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution
{
public:
    string getPermutation(int n, int k)
    {
        vector<int> factorial(n);
        factorial[0] = 1;
        for (size_t i = 1; i < n; i++)
        {
            factorial[i] = factorial[i - 1] * i;
        }
        k--;
        string ans;
        vector<int> valid(n + 1, 1);

        for (size_t i = 1; i <= n; i++)
        {
            int order = k / factorial[n - i] + 1;
            for (size_t j = 1; j <= n; j++)
            {
                order -= valid[j];
                if (!order)
                {
                    ans += (j + '0');
                    valid[j] = 0;
                    break;
                }
            }
            k %= factorial[n - 1];
        }
        return ans;
    }
};

int main()
{
    int n, k;
    Solution s;
    cout << "set n:";
    cin >> n;
    cout << endl;
    cout << "set k:";
    cin >> k;
    cout << endl;
    cout << s.getPermutation(n, k) << endl;

    return 0;
}