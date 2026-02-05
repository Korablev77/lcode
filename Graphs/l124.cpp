#include <algorithm>
#include <cassert>
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
    int maxPathSum(TreeNode* root) {        
        vector<TreeNode *> s1;
        vector<TreeNode *> s2;

        s1.push_back(root);
        while (!s1.empty())
        {
            TreeNode * node = s1.back();
            s1.pop_back();
            s2.push_back(node);

            if (node->left != nullptr)
                s1.push_back(node->left);
            if (node->right != nullptr)
                s1.push_back(node->right);
        }

        int max = -1000000;
        while (!s2.empty())
        {
            TreeNode * node = s2.back();
            s2.pop_back();
            max = std::max(max, node->val);
            if (node->left == nullptr && node->right == nullptr)
                continue;

            int left = 0, right = 0;
            if (node->left != nullptr)
                left = std::max(left, node->left->val);
            if (node->right != nullptr)
                right = std::max(right, node->right->val);

            max = std::max(max, node->val + left + right);
            node->val = node->val + std::max(left, right); // for further paths only one branch can be chosen
        }

        return max;
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
    assert(s.maxPathSum(&root) == 42);
    assert(s.maxPathSum(&rr) == 3);
    return 0;
}
