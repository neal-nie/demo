/* leetcode 1 
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
 * 你可以按任意顺序返回答案。
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/two-sum
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums.size() - 1;
        while (left != right)
        {
            if (nums[left] + nums[right] > target)
            {
                right--;
            }
            else if (nums[left] + nums[right] < target)
            {
                left++;
            }
            else
            {
                return {left, right};
            }
        }
        return {};
    }
};

int main() {
    vector<int> input = {3, 2, 4};
    Solution s;
    (void)s.twoSum(input, 6);
}