#include <cassert>
#include <vector>
#include <utility>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {

        vector<pair<int, int>> to_visit;
        to_visit.reserve(10000);
        vector<pair<int, int>> vacant;
        vacant.reserve(10000);

        for (int i = 0; i < grid.size(); i++)
             for (int j = 0; j < grid[0].size(); j++)
                 if (grid[i][j] == '1')
                     vacant.push_back({i, j});

        int j = 0, islands = 0;
        to_visit.push_back({0, 0});
        bool visited = false;
        while (!to_visit.empty())
        {
            int x = to_visit.back().first;
            int y = to_visit.back().second;
            to_visit.pop_back();

            if (grid[x][y] == '1')
            {
                visited = true;
                grid[x][y] = 'X';

                // now visit cell's neighbours (unexplored only!)
                if (x + 1 < grid.size() && grid[x+1][y] == '1')
                    to_visit.push_back({x+1, y});
                if (y + 1 < grid[0].size() && grid[x][y+1] == '1')
                    to_visit.push_back({x, y+1});
                if (x - 1 >= 0 && grid[x-1][y] == '1')
                    to_visit.push_back({x-1, y});
                if (y - 1 >= 0 && grid[x][y-1] == '1')
                    to_visit.push_back({x, y-1});
            }

            if (to_visit.empty())
            {
                if (visited)
                    islands++;
                visited = false;
                while (to_visit.empty() && j < vacant.size())
                {
                    int x = vacant[j].first;
                    int y = vacant[j++].second;
                    if (grid[x][y] == '1')
                        to_visit.push_back({x, y});
                }
            }
        }
        return islands;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<char>> t1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    vector<vector<char>> t2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    Solution s;
    assert(s.numIslands(t1) == 1);
    assert(s.numIslands(t2) == 3);

    return 0;
}
