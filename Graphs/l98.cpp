// Given the root of a binary tree, determine if it is a valid binary search tree (BST).

#include <cassert>
#include <cstdint>
#include <tuple>
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
    bool isValidBST(TreeNode* root) {
        vector<tuple<TreeNode *, long long int, long long int>> stack;
        stack.push_back({root, INT32_MIN - 1ll, INT32_MAX + 1ll});
        while (!stack.empty())
        {
            auto [node, min, max] = stack.back();
            stack.pop_back();
            if (node->val <= min || node->val >= max)
                return false;
            if (node->left != nullptr)
                stack.push_back({node->left, min, node->val});
            if (node->right != nullptr)
                stack.push_back({node->right, node->val, max});
        }
        return true;
    }
};

int main(int argc, char const *argv[])
{
    TreeNode l1(9);
    TreeNode r21(15);
    TreeNode r22(7);
    TreeNode r1(20, &r21, &r22);
    TreeNode root(-10, &l1, &r1);

    TreeNode child(2);
    TreeNode rr(1, &child, nullptr);

    Solution s;
    assert(s.isValidBST(&root) == false);
    assert(s.isValidBST(&rr) == false);
    return 0;
}
