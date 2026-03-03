#include <cassert>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        if (s[0] == '0')
            return 0;
        vector<int> dp(s.size() + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i < s.size() + 1; i++)
        {
            int d1 = s[i-2] - '0';
            int d2 = s[i-1] - '0';
            int dd = d2 + d1 * 10;

            if (d2 >= 1)
                dp[i] += dp[i-1];
            if (dd >= 10 && dd <= 26)
                dp[i] += dp[i-2];
        }
        return dp[s.size()];
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    assert(s.numDecodings("226") == 3);
    assert(s.numDecodings("12") == 2);

    return 0;
}
