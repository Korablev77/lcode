#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        // the same as l33, but here can be duplicates
        // when left == mid == right, we can't determine which half is sorted
        // so let's shrink both ends by one
        // btw it makes worst case time complexity O(n).
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target)
                return true;

            if (nums[left] == nums[mid] && nums[right] == nums[mid])
            {
                left++;
                right--;
                continue;
            }

            bool left_sorted = nums[left] <= nums[mid];
            bool right_sorted = nums[right] >= nums[mid];
            if (left_sorted)
            {
                if (target <= nums[mid] && target >= nums[left])
                    right = mid - 1;
                else
                    left = mid + 1;
                continue;
            }
            if (right_sorted)
            {
                if (target >= nums[mid] && target <= nums[right])
                    left = mid + 1;
                else
                    right = mid - 1;
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = { 2,5,6,0,0,1,2 };
    vector<int> t2 = { 2,5,6,0,0,1,2 };

    Solution s;
    assert(s.search(t1, 0));
    assert(!s.search(t2, 3));
    return 0;
}
