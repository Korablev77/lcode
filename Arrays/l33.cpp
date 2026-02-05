#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;

        // key is pretty much simple: one half of the array is always sorted;
        // we can easily check if target in sorted: more than min (left) and less than max (right)
        // if target is not in sorted part, than search in unsorted, that's it
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            bool left_sorted = nums[left] <= nums[mid];
            bool right_sorted = nums[right] >= nums[mid];

            if (nums[mid] == target)
                return mid;

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
        return -1;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = { 4,5,6,7,0,1,2 };
    vector<int> t2 = { 4,5,6,7,0,1,2 };
    vector<int> t3 = { 1 };
    vector<int> t4 = { 7, 8, 1, 2, 3, 4, 5, 6 };
    vector<int> t5 = { 3, 4, 5, 6, 1, 2 };
    Solution s;
    assert(s.search(t1, 0) == 4);
    assert(s.search(t2, 3) == -1);
    assert(s.search(t3, 0) == -1);
    assert(s.search(t4, 2) == 3);
    assert(s.search(t5, 2) == 5);

    return 0;
}
