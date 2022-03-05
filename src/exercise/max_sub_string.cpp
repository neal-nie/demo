/* Leetcode: 521 */
#include <string>
#include <iostream>

using namespace std;

class Solution
{
public:
    int findLUSlength(string a, string b)
    {
        return a != b ? max(a.length(), b.length()) : -1;
    }
};

int main()
{
    Solution s;
    string s1 = "teststrn";
    string s2 = "abcd";
    cin >> s1;
    cout << s1 << endl;
    cout << "result is :" << s.findLUSlength(s1, s2) << endl;
    return 0;
}
