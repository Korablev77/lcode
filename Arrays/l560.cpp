#include <cassert>
#include <vector>
#include <map>
#include <utility>

using namespace std;

// Given an array of integers nums and an integer k,
// return the total number of subarrays whose sum equals to k.

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {        
        map<int, int> sums;
        sums.insert({0, 1}); // stub to process 1 element as subarray sum

        int res = 0, sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            auto it = sums.find(sum-k);
            if (it != sums.end())
                res += it->second;
            sums[sum]++;
        }

        return res;
    }
};

// This solution won't pass one special case due to the time limit:
// [0, 0, 0, 0, ...], k = 0;

/*
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {        
        multimap<int, int> m;
        vector<int> prefixes;
        prefixes.reserve(100000);
        m.insert({0, -1});
        int sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum += nums[i];
            prefixes.push_back(sum);
            m.insert({sum, i});
        }

        int res = 0;
        for (int i = prefixes.size() - 1; i >= 0; i--)
        {
            int x = prefixes[i];
            auto it = m.find(x-k);
            while (it != m.end() && it->first == x-k)
            {
                if (it->second < i)
                    res++;
                it++;
            }
        }

        return res;
    }
};
*/

int main(int argc, char const *argv[])
{
    vector<int> t1 = { 1, 1, 1 };
    vector<int> t2 = { 1, 2, 3 };
    vector<int> t3 = { 1, -1, 0 };

    Solution s;
    assert(s.subarraySum(t1, 2) == 2);
    assert(s.subarraySum(t2, 3) == 2);
    assert(s.subarraySum(t3, 0) == 3);

	return 0;
}