#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] > target)
                right = mid - 1;
            if (nums[mid] < target)
                left = mid + 1;
            if (nums[mid] == target)
                return mid;
        }
        return -1;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = { -1,0,3,5,9,12 };
    vector<int> t2 = { -1,0,3,5,9,12 };
    vector<int> t3 = { 1 };
    Solution s;
    assert(s.search(t1, 9) == 4);
    assert(s.search(t2, 2) == -1);
    return 0;
}