#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

static bool cmp(const vector<int> & a, const vector<int> & b)
{
    return a[1] < b[1];
}

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        std::sort(points.begin(), points.end(), cmp);

        int res = 1;
        int shot = points[0][1];
        for (int i = 1; i < points.size(); i++)
        {
            if (points[i][0] > shot)
            {
                shot = points[i][1];
                res++;
            }
        }
        printf("res=%d \n", res);
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> t1 = {
        {10,16},{2,8},{1,6},{7,12}};
    // [1,6] [2, 8], [7, 12], [10, 16]

    vector<vector<int>> t2 = {
        {1,2},{3,4},{5,6},{7,8}
    };

    vector<vector<int>> t3 = {
        {1,2},{2,3},{3,4},{4,5}};

    vector<vector<int>> t4 = {
        {9,12},{1,10},{4,11},{8,12},{3,9},{6,9},{6,7}};

    Solution s;
    //assert(s.findMinArrowShots(t1) == 2);
    //assert(s.findMinArrowShots(t2) == 4);
    assert(s.findMinArrowShots(t3) == 2);
    assert(s.findMinArrowShots(t4) == 2);

    return 0;
}
