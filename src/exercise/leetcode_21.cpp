/* Leetcode 21 */

#include <cstddef>

/**
Definition for singly-linked list.
  */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        if (!list1 && !list2)
        {
            return nullptr;
        }
        if (!list1)
        {
            return list2;
        }
        if (!list2)
        {
            return list1;
        }

        ListNode *resPtr = new ListNode();
        ListNode *resHeader = resPtr;
        ListNode *ptr1 = list1;
        ListNode *ptr2 = list2;
        while (ptr1 && ptr2)
        {
            if (ptr1->val <= ptr2->val)
            {
                resPtr->next = ptr1;
                ptr1 = ptr1->next;
            }
            else
            {
                resPtr->next = ptr2;
                ptr2 = ptr2->next;
            }
            resPtr = resPtr->next;
        }

        if (ptr1)
        {
            resPtr->next = ptr1;
        }
        if (ptr2)
        {
            resPtr->next = ptr2;
        }
        return resHeader->next;
    }
};