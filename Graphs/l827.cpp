#include <algorithm>
#include <cassert>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

class Solution {
public:
    unordered_map<int, int> sizes;

    int merge_islands(const vector<vector<int>> & grid, int i, int j, vector<int> & visited)
    {
        assert(grid[i][j] != 0);
        for (auto c : visited)
            if (grid[i][j] == c)
                return 0;
        visited.push_back(grid[i][j]);
        return sizes[grid[i][j]];
    }

    int largestIsland(vector<vector<int>>& grid) {
        assert(grid.size() == grid[0].size()); // NxN matrix

        sizes.clear();

        vector<pair<int, int>> to_visit;
        to_visit.reserve(10000);
        vector<pair<int, int>> vacant;
        vacant.reserve(10000);

        int cur_size = 0;
        int max_size = 0;

        for (int i = 0; i < grid.size(); i++)
             for (int j = 0; j < grid[0].size(); j++)
                 if (grid[i][j] == 1)
                     vacant.push_back({i, j});

        int j = 0;
        to_visit.push_back({0, 0});
        while (!to_visit.empty())
        {
            int x = to_visit.back().first;
            int y = to_visit.back().second;
            to_visit.pop_back();

            if (grid[x][y] == 1)
            {
                cur_size++;
                grid[x][y] = sizes.size() + 2;

		// now visit cell's neighbours (unexplored only!)
                if (x + 1 < grid.size() && grid[x+1][y] == 1)
                    to_visit.push_back({x+1, y});
                if (y + 1 < grid.size() && grid[x][y+1] == 1)
                    to_visit.push_back({x, y+1});
                if (x - 1 >= 0 && grid[x-1][y] == 1)
                    to_visit.push_back({x-1, y});
                if (y - 1 >= 0 && grid[x][y-1] == 1)
                    to_visit.push_back({x, y-1});
            }


            if (to_visit.empty())
            {
                sizes[sizes.size() + 2] = cur_size;
                max_size = std::max(cur_size, max_size);
                cur_size = 0;

                while (to_visit.empty() && j < vacant.size())
                {
                    int x = vacant[j].first;
                    int y = vacant[j++].second;
                    if (grid[x][y] == 1)
                        to_visit.push_back({x, y});
                }
            }
        }

        // iterate over all cells in between islands and check if we can merge smth
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 0)
                {
                    int merged_size = 0;
                    vector<int> visited;
                    if (i - 1 >= 0 && grid[i-1][j] != 0)
                        merged_size += merge_islands(grid, i-1, j, visited);
                    if (i + 1 < grid.size() && grid[i+1][j] != 0)
                        merged_size += merge_islands(grid, i+1, j, visited);
                    if (j - 1 >= 0 && grid[i][j-1] != 0)
                        merged_size += merge_islands(grid, i, j-1, visited);
                    if (j + 1 < grid.size() && grid[i][j+1] != 0)
                        merged_size += merge_islands(grid, i, j+1, visited);

                    max_size = std::max(max_size, merged_size);
                }
            }
        }

        int total_size = grid.size() * grid.size();
        return std::min(max_size + 1, total_size);
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> t1 = {
        {1, 0},
        {0, 1}
    };
    vector<vector<int>> t2 = {
        {1, 1},
        {0, 1}
    };
    vector<vector<int>> t3 = {
        {1, 1},
        {1, 1}
    };
    vector<vector<int>> t4 = {
        {1, 0, 1},
        {0, 0, 0},
        {0, 1, 1}
    };
    vector<vector<int>> t5 = {
        {1,0,0,1,1},
        {1,0,0,1,0},
        {1,1,1,1,1},
        {1,1,1,0,1},
        {0,0,0,1,0}
    };

    Solution s;

    assert(s.largestIsland(t1) == 3);
    assert(s.largestIsland(t2) == 4);
    assert(s.largestIsland(t3) == 4);
    assert(s.largestIsland(t4) == 4);
    assert(s.largestIsland(t5) == 16);

    return 0;
}
