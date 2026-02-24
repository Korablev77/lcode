// Given the root of a binary tree, return the level order traversal of its nodes' values
// (i.e., from left to right, level by level).

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        vector<TreeNode *> next_lvl;
        vector<TreeNode *> curr_lvl;
        if (root != nullptr)
            curr_lvl.push_back(root);
        while (!curr_lvl.empty())
        {
            vector<int> r;
            for (auto p : curr_lvl)
            {
                if (p->left != nullptr)
                    next_lvl.push_back(p->left);
                if (p->right != nullptr)
                    next_lvl.push_back(p->right);
                r.push_back(p->val);
            }
            res.push_back(r);
            curr_lvl = next_lvl;
            next_lvl.resize(0);
        }
        return res;
    }
};
