// You are given two non-empty linked lists representing two non-negative integers.
// The digits are stored in reverse order, and each of their nodes contains a single digit.
// Add the two numbers and return the sum as a linked list.

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode * head = nullptr, *p = nullptr;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr)
        {
            int x1 = 0;
            int x2 = 0;
            if (l1 != nullptr)
            {
                x1 = l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr)
            {
                x2 = l2->val;
                l2 = l2->next;
            }
            int res = x1 + x2 + carry;
            carry = res >= 10 ? 1 : 0;
            res = res % 10;

            ListNode * prev = p;
            p = new ListNode(res);
            if (head == nullptr)
                head = p;
            if (prev != nullptr)
                prev->next = p;
        }
        if (carry > 0)
        {
            ListNode * prev = p;
            p = new ListNode(1);
            prev->next = p;
        }

        return head;
    }
};

// class Solution {
// public:
//     ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//         vector<int> s1, s2;
//         ListToVec(l1, s1);
//         ListToVec(l2, s2);

//         ListNode * head = nullptr, *p = nullptr;
//         int carry = 0;
//         while (!s1.empty() || !s2.empty())
//         {
//             int x1 = 0;
//             int x2 = 0;
//             if (!s1.empty())
//             {
//                 x1 = s1.back();
//                 s1.pop_back();
//             }
//             if (!s2.empty())
//             {
//                 x2 = s2.back();
//                 s2.pop_back();
//             }
//             int res = x1 + x2 + carry;
//             carry = res >= 10 ? 1 : 0;
//             res = res % 10;

//             ListNode * prev = p;
//             p = new ListNode(res);
//             if (head == nullptr)
//                 head = p;
//             if (prev != nullptr)
//                 prev->next = p;
//         }
//         if (carry > 0)
//         {
//             ListNode * prev = p;
//             p = new ListNode(1);
//             prev->next = p;
//         }

//         return head;
//     }
// };

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
    while (l1 != nullptr && l2 != nullptr)
    {
        if (l1->val != l2->val)
            return false;
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1 == l2;
}

int main(int argc, char const *argv[])
{
    vector<int> t11 = {2,4,3};
    vector<int> t12 = {5,6,4};
    vector<int> t13 = {7,0,8};

    ListNode * l11 = VecToList(t11);
    ListNode * l12 = VecToList(t12);
    ListNode * l13 = VecToList(t13);

    vector<int> t21 = {9,9,9,9,9,9,9};
    vector<int> t22 = {9,9,9,9};
    vector<int> t23 = {8,9,9,9,0,0,0,1};

    ListNode * l21 = VecToList(t21);
    ListNode * l22 = VecToList(t22);
    ListNode * l23 = VecToList(t23);

    Solution s;
    auto r1 = s.addTwoNumbers(l11, l12);
    assert(ListCmp(r1, l13) == true);
    ListFree(l11);
    ListFree(l12);
    ListFree(l13);
    ListFree(r1);

    auto r2 = s.addTwoNumbers(l21, l22);
    assert(ListCmp(r2, l23) == true);
    ListFree(l21);
    ListFree(l22);
    ListFree(l23);
    ListFree(r2);
    return 0;
}
