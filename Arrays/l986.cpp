// You are given two lists of closed intervals, firstList and secondList, where firstList[i] = [starti, endi]
// and secondList[j] = [startj, endj]. Each list of intervals is pairwise disjoint and in sorted order.
// Return the intersection of these two interval lists.

#include <algorithm>
#include <cassert>
#include <vector>

#include <stdio.h>

using namespace std;

// the main key: intervals intersect iff max(x[0], y[0]) < min(x[1], y[1])
// there are basically two situations: [] [] and [[]]
// so [][] can be tell from [[]] if the last '[' is positioned before first ']'
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList, vector<vector<int>>& secondList) {
        vector<vector<int>> res;
        int i = 0, j = 0;
        while (i < firstList.size() && j < secondList.size())
        {
            int l = std::max(firstList[i][0], secondList[j][0]);
            int r = std::min(firstList[i][1], secondList[j][1]);

            if (l <= r)
                res.push_back({l, r});
            if (firstList[i][1] < secondList[j][1])
                i++;
            else
                j++;
        }

        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> t1 = {{0,2},{5,10},{13,23},{24,25}};
    vector<vector<int>> t2 = {{1,5},{8,12},{15,24},{25,26}};
    vector<vector<int>> r1 = {{1,2},{5,5},{8,10},{15,23},{24,24},{25,25}};


    vector<vector<int>> t3 = {{1,3},{5,9}};
    vector<vector<int>> t4;

    vector<vector<int>> t5 = {{3,10}};
    vector<vector<int>> t6 = {{5,10}};

    Solution s;
    assert(s.intervalIntersection(t1, t2) == r1);
    assert(s.intervalIntersection(t3, t4) == vector<vector<int>>({}));
    assert(s.intervalIntersection(t5, t6) == vector<vector<int>>({{5, 10}}));
    return 0;
}
