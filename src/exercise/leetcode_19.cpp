/**
Definition for singly-linked list.
*/
#include <iostream>
#include <cstddef>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* ptr1;
        ListNode * ptr2;
        ListNode*pre = new ListNode(0, head);
        ptr1 = head;
        ptr2 = pre;
        int i = 0;
        while(ptr1) {
            ptr1 = ptr1->next;
            i ++;
            if (i > n) {
                ptr2 = ptr2->next;
            }
        }
        ListNode *toDelte = ptr2->next;
        ptr2->next = toDelte->next;
        return pre->next;
    }
};