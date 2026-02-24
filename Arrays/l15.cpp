// Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that:
// i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

#include <algorithm>
#include <cassert>
#include <cstring>
#include <vector>
#include <unordered_set>

using namespace std;

// x+y+z == 0
// x+y == -z
//
// two sum problem x+y == K
// find x: x == K-y

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());

        vector<vector<int>> res;
        for (int i = 0; i < nums.size()-1; i++)
        {
            if (i > 0 && nums[i] == nums[i-1]) continue;

            int l = i + 1, r = nums.size() - 1;
            while (l < r)
            {
                int s = nums[l] + nums[r] + nums[i];
                if (s == 0)
                {
                    res.push_back({nums[l], nums[r], nums[i]});
                    while (l < r && nums[l] == nums[l+1]) l++; // skip duplicates
                    while (l < r && nums[r] == nums[r-1]) r--;
                    l++; r--;
                }
                if (s < 0)
                    l++;
                if (s > 0)
                    r--;
            }
        }
        return res;
    }
};

// hash map solution doesn't pass freaking 0000000... test :(
// i bet it's easy to find a workaround, but anyway let's try
// classic 2 ptrs solution
/*
struct h
{
    std::size_t operator()(const vector<int> & p) const
    {
        return std::hash<int>{}(p[0]) ^ std::hash<int>{}(p[1]) ^ std::hash<int>{}(p[2]);
    }
};

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        unordered_map<int, int> m;
        for (int i = 0; i < nums.size(); i++)
            m[nums[i]]++;
        unordered_set<vector<int>, h> filtered;
        for (int i = 0; i < nums.size(); i++)
        {
            int target = -nums[i];
            m[nums[i]]--;
            for (int j = i+2; j < nums.size(); j++)
            {
                while (nums[j-1] == nums[j])
                    continue;
                auto p = m.find(target-nums[j]);
                if (p == m.end() || p->second <= 0 (target-nums[j] == nums[j] && p->second == 1))
                    continue;
                // trio: nums[i], nums[j] and p
                vector<int> s = {nums[i], nums[j], p->first};
                std::sort(s.begin(), s.end());
                auto p1 = filtered.find(s);
                if (p1 == filtered.end())
                    filtered.insert(s);
            }
        }
        vector<vector<int>> res;
        for (auto p : filtered)
            res.push_back(p);

        return res;
    }
};
*/

int main(int argc, char const *argv[])
{
    vector<int> t1 = { -1,0,1,2,-1,-4 };
    vector<int> t2 = { 0, 0, 0};

    vector<vector<int>> r1 = {{-1, -1, 2}, {-1, 0, 1}};

    Solution s;
    assert(s.threeSum(t1) == r1);
    assert(s.threeSum(t2) == vector<vector<int>>({{0,0,0}}));

    return 0;
}
