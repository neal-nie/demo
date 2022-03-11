#include <iostream>
#include <vector>

using namespace std;

#define INVALID_VALUE 255

class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        size_t rowNum = grid.size();
        size_t colNum = grid.at(0).size();
        size_t i, j;
        for (i = 0; i < rowNum; i++)
        {
            // scan each row
            for (j = 0; j < colNum; j++)
            {
                // scan each column
                if (i == 0 && j == 0)
                {
                    continue;
                }

                int up = i == 0 ? INVALID_VALUE : grid.at(i - 1).at(j);
                int left = j == 0 ? INVALID_VALUE : grid.at(i).at(j - 1);

                grid.at(i).at(j) += min(up, left);
            }
        }
        return grid.at(i - 1).at(j - 1);
    }
};