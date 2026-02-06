#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));

        for (int i = 1; i < text1.size() + 1; i++)
        {
            for (int j = 1; j < text2.size() + 1; j++)
            {
                if (text1[i-1] == text2[j-1])
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
    Solution s;
    assert(s.longestCommonSubsequence("abcde", "ace") == 3);
    assert(s.longestCommonSubsequence("abc", "abc") == 3);
    assert(s.longestCommonSubsequence("abc", "def") == 0);

    return 0;
}
