// Given two integer arrays nums1 and nums2, return an array of their intersection.
// Each element in the result must appear as many times as it shows in both arrays.

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> m1, m2;
        for (auto x : nums1)
            m1[x]++;
        vector<int> res;
        for (auto y : nums2)
        {
            if (m1[y] > 0)
            {
                m1[y]--;
                res.push_back(y);
            }
        }
        return res;
    }
};
