/* test for vector */
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

template <typename T>
void show_vector(vector<T> list)
{
    for (T x : list)
    {
        cout << x << ", ";
    }
    cout << endl;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5};

    // traverse
    show_vector(nums);

    int *ptr = nums.data();
    for (size_t i = 0; i < nums.size(); i++)
    {
        cout << *ptr << ", ";
        ptr++;
    }
    cout << endl;

    // push
    nums.push_back(11);
    cout << "after push_back" << endl;
    show_vector(nums);

    // pop && deque
    int last = nums.back();
    nums.pop_back();
    cout << "after pop_back" << endl;
    show_vector(nums);
    cout << "last is: " << last << endl;

    // enque
    int front = 12;
    nums.insert(nums.begin(), front);
    cout << "after insert: " << endl;
    show_vector(nums);

    // delete
    nums.erase(nums.begin() + 2);
    cout << "after delete: " << endl;
    show_vector(nums);

    // reference
    int &x = nums[4];
    x = 11;
    cout << "change value:" << endl;
    show_vector(nums);

    // swap
    vector<int> dup_nums = {1, 2};
    cout << "swap content with other vector: " << endl;
    nums.swap(dup_nums);
    show_vector(nums);
    show_vector(dup_nums);

    // iterator(similar to index, same as pointer)
    cout << "first is :" << *dup_nums.begin() << endl;
    cout << "next two is :" << *next(dup_nums.begin(), 2) << endl;

    return 0;
}