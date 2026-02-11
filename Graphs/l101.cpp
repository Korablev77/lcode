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
    bool isSymmetric(TreeNode* root) {
        return isSymmetric(root->left, root->right);        
    }

private:
    bool isSymmetric(TreeNode * l, TreeNode * r)
    {
        if (l != nullptr && r == nullptr)
            return false;
        if (l == nullptr && r != nullptr)
            return false;
        if (l == nullptr)
            return true;
        return l->val == r->val && isSymmetric(l->left, r->right) && isSymmetric(l->right, r->left);
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
    assert(s.isSymmetric(&root) == false);
    return 0;
}
