// Given the head of a linked list, remove the nth node from the end of the list and return its head.

#include <cassert>
#include <vector>
#include <string>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

static void ListToVec(ListNode * l, vector<int> & v)
{
    while (l != nullptr)
    {
        v.push_back(l->val);
        l = l->next;
    }
}

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode * last = head;
        ListNode * first = head;

        // one node no luck
        if (head->next == nullptr)
            return nullptr;

        while (n > 0 && first->next != nullptr)
        {
            first = first->next;
            n--;
        }

        // now looking for the end
        while (first->next != nullptr)
        {
            first = first->next;
            last = last->next;
        }
        if (last == head && n > 0)
            head = last->next;
        last->next = last->next->next;

        return head;
    }
};

static ListNode * VecToList(const vector<int> & v)
{
    ListNode * head = new ListNode(v[0]);
    ListNode * prev = head;
    for (int i = 1; i < v.size(); i++)
    {
        ListNode * p = new ListNode(v[i]);
        if (prev != nullptr)
            prev->next = p;
        prev = p;
    }
    return head;
}

static void ListFree(ListNode * head)
{
    ListNode * p = head;
    while (p != nullptr)
    {
        ListNode * next = p->next;
        delete p;
        p = next;
    }
}

static bool ListCmp(ListNode * l1, ListNode * l2)
{
    printf("l1=%p l2=%p \n", l1, l2);
    while (l1 != nullptr && l2 != nullptr)
    {
        printf("l1=%d l2=%d \n", l1->val, l2->val);
        if (l1->val != l2->val)
            return false;
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1 == l2;
}

int main(int argc, char const *argv[])
{
    vector<int> t11 = {1,2,3,4,5};
    vector<int> t12 = {1,2,3,5};

    ListNode * l11 = VecToList(t11);
    ListNode * l12 = VecToList(t12);

    vector<int> t21 = {1,2};
    vector<int> t22 = {2};

    ListNode * l21 = VecToList(t21);
    ListNode * l22 = VecToList(t22);

    Solution s;
    auto r1 = s.removeNthFromEnd(l11, 2);
    assert(ListCmp(r1, l12) == true);
    ListFree(l11);
    ListFree(l12);

    auto r2 = s.removeNthFromEnd(l21, 2);
    assert(ListCmp(r2, l22) == true);
    ListFree(l21);
    ListFree(l22);
    return 0;
}
