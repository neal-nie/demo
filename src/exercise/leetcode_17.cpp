/* Leetcode 17 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<char, string> phoneMap = {
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"}};

class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        vector<string> res;

        if (digits.empty())
        {
            return res;
        }

        res.push_back("");

        for (char num : digits)
        {
            string letters = phoneMap.at(num);

            int len = res.size();
            for (int i = 0; i < len; i++)
            {
                string comb = res.front();
                res.erase(res.begin());
                for (char l : letters)
                {
                    comb.push_back(l);
                    res.push_back(comb);
                    comb.pop_back();
                }
            }
        }

        return res;
    }
};
