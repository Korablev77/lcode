// Given an integer array nums and an integer k, return true if nums has a good subarray.
// A good subarray is a subarray where:
// its length is at least two;
// the sum of the elements of the subarray is a multiple of k.

#include <algorithm>
#include <cassert>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (nums.size() <= 1)
            return false;
        if (nums.size() <= 2)
            return ((nums[0] + nums[1]) % k) == 0;

        int sum = nums[0] % k;
        std::unordered_set<int> m; // remainders
        int prev = nums[0] % k;
        for (int i = 1; i < nums.size(); i++)
        {
            sum += nums[i];
            sum %= k;
            if (sum == 0 || m.find(sum) != m.end())
                return true;
            m.insert(prev);
            prev = sum;
        }
        return false;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = { 23,2,4,6,7 };
    vector<int> t2 = { 23,2,6,4,7 };
    vector<int> t3 = { 23,2,6,4,7 };
    vector<int> t4 = { 23,0,0 };

    Solution s;
    assert(s.checkSubarraySum(t1, 6) == true);
    assert(s.checkSubarraySum(t2, 6) == true);
    assert(s.checkSubarraySum(t3, 13) == false);
    assert(s.checkSubarraySum(t4, 6) == true);
    return 0;
}
