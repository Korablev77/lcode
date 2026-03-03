#include <algorithm>
#include <cassert>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
    void queueSpoiled(vector<vector<int>>& grid, vector<pair<int, int>> & to_spoil, int i, int j)
    {
        if (i > 0 && grid[i-1][j] == 1)
        {
            to_spoil.push_back({i-1, j});
            grid[i-1][j] = 3;
        }
        if (j > 0 && grid[i][j-1] == 1)
        {
            to_spoil.push_back({i, j-1});
            grid[i][j-1] = 3;
        }
        if (i < grid.size()-1 && grid[i+1][j] == 1)
        {
            to_spoil.push_back({i+1, j});
            grid[i+1][j] = 3;
        }
        if (j < grid[0].size()-1 && grid[i][j+1] == 1)
        {
            to_spoil.push_back({i, j+1});
            grid[i][j+1] = 3;
        }
    }

    int orangesRotting(vector<vector<int>>& grid) {
        vector<pair<int, int>> to_spoil;
        int healthy = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1 || grid[i][j] == 3)
                    healthy++;
                if (grid[i][j] == 2)
                    queueSpoiled(grid, to_spoil, i, j);
            }
        }

        int time = 0;
        vector<pair<int, int>> next;
        while (!to_spoil.empty())
        {
            auto p = to_spoil.back();
            to_spoil.pop_back();
            int x = p.first;
            int y = p.second;
            if (grid[x][y] != 3)
                continue;
            grid[x][y] = 2;
            healthy--;
            queueSpoiled(grid, next, x, y);

            if (to_spoil.empty())
            {
                swap(to_spoil, next);
                time++;
            }
        }
        return healthy == 0 ? time : -1;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> t = {
        {2,1,1},
        {1,1,0},
        {0,1,1},
    };

    Solution s;
    assert(s.orangesRotting(t) == 4);

    return 0;
}
