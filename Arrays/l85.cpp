// Given a rows x cols binary matrix filled with 0's and 1's,
// find the largest rectangle containing only 1's and return its area.

#include <algorithm>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

// Hint: just solve for each row l84 (max rectangle in histogram)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        vector<int> heights(matrix[0].size(), 0);
        for (int i = 0; i < matrix[0].size(); i++)
            heights[i] = matrix[0][i] - '0';

        int max = 0;
        max = std::max(max, largestRectangleArea(heights));
        for (int i = 1; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[i].size(); j++)
                heights[j] = matrix[i][j] == '0' ? 0 : heights[j] + 1;

            max = std::max(max, largestRectangleArea(heights));
        }

        return max;
    }

private:
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
    vector<vector<char>> t1 = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    vector<vector<char>> t2 = {{ '1' }};
    vector<vector<char>> t3 = {{'0','1'},{'0','1'}};
    vector<vector<char>> t4 = {{'0','1'},{'1','0'}};
    Solution s;
    assert(s.maximalRectangle(t1) == 6);
    assert(s.maximalRectangle(t2) == 1);
    assert(s.maximalRectangle(t3) == 2);
    assert(s.maximalRectangle(t4) == 1);

    return 0;
}

