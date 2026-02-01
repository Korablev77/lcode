#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int max = 0;
        int prev_arr = 0, curr_arr = 0;
        bool null_removed = false;
        for (int i = 0; i < nums.size(); i++)
        {
        	if (nums[i] == 1)
        		curr_arr++;
        	if (nums[i] == 0)
        	{
        		null_removed = true;
        		max = std::max(max, curr_arr + prev_arr);
        		prev_arr = curr_arr;
        		curr_arr = 0;
        	}
        }
        if (!null_removed)
        	curr_arr--;
        return std::max(max, curr_arr + prev_arr);
    }
};

int main(int argc, char const *argv[])
{
	vector<int> t1 = { 1, 1, 0, 1 };
	vector<int> t2 = { 0, 1, 1, 1, 0, 1, 1, 0, 1 };
	vector<int> t3 = { 1, 1, 1 };
	vector<int> t4 = { 0, 0, 1, 1 };
	
	Solution s;
	assert(s.longestSubarray(t1) == 3);
	assert(s.longestSubarray(t2) == 5);
	assert(s.longestSubarray(t3) == 2);
	assert(s.longestSubarray(t4) == 2);

	return 0;
}