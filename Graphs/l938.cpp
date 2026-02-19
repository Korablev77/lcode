// Given the root node of a binary search tree and two integers low and high,
// return the sum of values of all nodes with a value in the inclusive range [low, high].

#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        int res = 0;
        vector<TreeNode *> stack;
        stack.push_back(root);
        while (!stack.empty())
        {
            auto p = stack.back();
            stack.pop_back();
            if (p->left != nullptr)
                stack.push_back(p->left);
            if (p->right != nullptr)
                stack.push_back(p->right);
            if (p->val >= low && p->val <= high)
                res += p->val;
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    TreeNode l1(9);
    TreeNode r21(15);
    TreeNode r22(7);
    TreeNode r1(20, &r21, &r22);
    TreeNode root(-10, &l1, &r1);

    Solution s;
    assert(s.rangeSumBST(&root, 7, 15) == 31);
    return 0;
}
