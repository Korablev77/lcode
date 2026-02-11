#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = 0;
        int j = 0;
        int zero_cnt = 0;
        for (; i < nums.size(); ++i) {
            if (nums[i] != 0)
                nums[j++] = nums[i];
        }
        std::fill(nums.begin() + j, nums.end(), 0);
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    return 0;
}
