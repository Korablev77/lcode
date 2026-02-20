// Given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.
// You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.

#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

// in the perfect case all numbers must be:
// 1 2 3 4 ... n (x=value)
// 0 1 2 3 ... n-1 (i=index)
// so value x must reside at the index x-1, so just swap values until that't true
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++)
        {
            int x = nums[i];
            while (x >= 1 && x <= (int)nums.size() && x != nums[x-1])
            {
                swap(nums[i], nums[x-1]);
                x = nums[i];
            }
        }

        for (int i = 0; i < nums.size(); i++)
            if (nums[i] != i+1)
                return i+1;
        return nums.size() + 1;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = {3,4,-1,1};
    vector<int> t2 = {1,2,0};
    vector<int> t3 = {7,8,9,11,12};

    Solution s;
    assert(s.firstMissingPositive(t1) == 2);
    assert(s.firstMissingPositive(t2) == 3);
    assert(s.firstMissingPositive(t3) == 1);

    return 0;
}
