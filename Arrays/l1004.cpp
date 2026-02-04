#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
        int longestOnes(vector<int>& nums, int k) {
            int i = 0, j = 0;
            int ones = 0, flips = k, max = 0;
            for (; i < nums.size() && j < nums.size();)
            {
                if (nums[j] == 0 && flips > 0)
                {
                    ones++, flips--, j++;
                    max = std::max(max, ones);
                    continue;
                }
                if (nums[j] == 0 && flips == 0)
                {
                    if (nums[i] == 0)
                        flips++;
                    ones--;
                    i++;
                    continue;
                }
                if (nums[j] == 1)
                {
                    ones++, j++;
                    max = std::max(max, ones);
                }

            }
        return max;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = {
        1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
    };
    vector<int> t2 = {
        0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1
    };

    Solution s;
    assert(s.longestOnes(t1, 2) == 6);
    assert(s.longestOnes(t2, 3) == 10);
    return 0;
}
