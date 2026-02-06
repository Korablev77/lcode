#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

// classic 2d dynamic task:
// d[i][j] - number of operations to convert s1[0..i-1] to s2[0..j-1]
//
// d[i][0] == i
// d[0][j] == j
//
// d[i][j] =          d[i-1][j-1] if s1[i] == s2[j]
//               {1 + d[i][j-1]   (if op is insert into s1)
// d[i][j] = MIN {1 + d[i-1][j]   (if op is delete from s1)
//               {1 + d[i-1][j-1] (if op is replace: just turn s1[i] into s2[j] or vice versa)
//
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.size();
        int len2 = word2.size();

        vector<vector<int>> d(len1 + 1, vector<int>(len2 + 1));
        for (int i = 0; i <= len1; i++)
            d[i][0] = i;
        for (int j = 0; j <= len2; j++)
            d[0][j] = j;

        for (int i = 1; i <= len1; i++)
        {
            for (int j = 1; j <= len2; j++)
            {
                if (word1[i-1] == word2[j-1])
                {
                    d[i][j] = d[i-1][j-1];
                    continue;
                }
                d[i][j] = 1 + std::min({d[i][j-1], d[i-1][j], d[i-1][j-1]});
            }
        }
        return d.back().back();
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    assert(s.minDistance("horse", "ros") == 3);
    assert(s.minDistance("intention", "execution") == 5);
    return 0;
}
