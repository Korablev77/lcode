// Given an array of integers heights representing the histogram's bar height
// where the width of each bar is 1, return the area of the largest rectangle in the histogram.

#include <algorithm>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int area = 0;
        vector<int> s;
        for (int i = 0; i < heights.size(); i++)
        {
            while (s.size() > 0 && heights[s.back()] > heights[i])
            {
                int pos = s.back();
                s.pop_back();

                int height = heights[pos];
                int width = s.empty() ? i : i - s.back() - 1;
                area = max(area, height * width);
            }
            s.push_back(i);
        }

        while (s.size() > 0)
        {
            int pos = s.back();
            s.pop_back();
            int height = heights[pos];
            int width = s.empty() ? heights.size() : heights.size() - s.back() - 1;
            area = max(area, height * width);
        }
        return area;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = { 2,1,5,6,2,3 };
    vector<int> t2 = { 2,4 };
    vector<int> t3 = { 0,2,0 };
    vector<int> t4 = { 2,1,2 };
    vector<int> t5 = { 5,4,1,2 };
    vector<int> t6 = { 4,2,0,3,2,5 };

    Solution s;
    assert(s.largestRectangleArea(t1) == 10);
    assert(s.largestRectangleArea(t2) == 4);
    assert(s.largestRectangleArea(t3) == 2);
    assert(s.largestRectangleArea(t4) == 3);
    assert(s.largestRectangleArea(t5) == 8);
    assert(s.largestRectangleArea(t6) == 6);

    return 0;
}

