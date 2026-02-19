// Given an array nums containing n distinct numbers in the range [0, n],
// return the only number in the range that is missing from the array.

#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int missing = nums.size();
        for (int i = 0; i < nums.size(); i++)
            missing = missing ^ nums[i] ^ i;
        return missing;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = {3,0,1};
    vector<int> t2 = {9,6,4,2,3,5,7,0,1};
    Solution s;
    assert(s.missingNumber(t1) == 2);
    assert(s.missingNumber(t2) == 8);


    return 0;
}

