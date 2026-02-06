#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

// another 2d dp: dp[i][j] - max uncrossed lines for nums1[0..i-1] and nums2[0..j-1]
// dp[i][j] = 1 + dp[i-1][j-1] if nums1[i-1] == nums2[j-1]
// dp[i][j] = max(dp[i-1][j], dp[i][j-1])
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));

        for (int i = 1; i < nums1.size() + 1; i++)
        {
            for (int j = 1; j < nums2.size() + 1; j++)
            {
                if (nums1[i-1] == nums2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }

        return dp.back().back();
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t11 = { 1, 4, 2 };
    vector<int> t12 = { 1, 2, 4 };
    vector<int> t21 = { 2, 5, 1, 2, 5 };
    vector<int> t22 = { 10, 5, 2, 1, 5, 2};
    vector<int> t31 = { 1, 3, 7, 1, 7, 5 };
    vector<int> t32 = { 1, 9, 2, 5, 1 };

    Solution s;
    assert(s.maxUncrossedLines(t11, t12) == 2);
    assert(s.maxUncrossedLines(t21, t22) == 3);
    assert(s.maxUncrossedLines(t31, t32) == 2);

    return 0;
}
