// Given an array of intervals where intervals[i] = [starti, endi],
// merge all overlapping intervals, and return an array of the
// non-overlapping intervals that cover all the intervals in the input.

#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    static bool cmp (const vector<int> & a, const vector<int> & b)
    {
        if (a[0] < b[0])
            return true;
        if (a[0] == b[0])
            return a[0] < b[0];
        return false;
    }

    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        std::sort(intervals.begin(), intervals.end(), cmp);

        vector<vector<int>> res;
        int i = 0, j = 1;
        while (i < intervals.size())
        {
            vector<int> merged(2, 0);
            merged = intervals[i];
            while (j < intervals.size() && merged[1] >= intervals[j][0])
            {
                merged[1] = std::max(merged[1], intervals[j][1]);
                j++;
            }
            res.push_back(merged);
            i = j;
        }

        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> t1 = {
        {1,3}, {2,6}, {8,10}, {15,18}
    };
    vector<vector<int>> t2 = {
        {1,4}, {4,5}
    };
    vector<vector<int>> t3 = {
        {4, 7}, {1,4}
    };
    Solution s;
    assert(s.merge(t1) == vector<vector<int>>({{1, 6}, {8, 10}, {15, 18 }}));
    assert(s.merge(t2) == vector<vector<int>>({{1, 5}}));
    assert(s.merge(t3) == vector<vector<int>>({{1, 7}}));

    return 0;
}

