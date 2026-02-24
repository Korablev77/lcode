// Given an m x n grid of characters board and a string word, return true if word exists in the grid.

#include <cassert>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    void print(const vector<vector<char>> & board)
    {
        for (int i = 0; i < board.size(); ++i)
        {
            printf("\n");
            for (int j = 0; j < board[i].size(); ++j)
                printf("%c ", board[i][j]);
        }
    }
    // board is small, copy is ok
    bool dfs(vector<vector<char>> & board, string & word, int i, int x, int y)
    {
        if (x < 0 || x >= board.size())
            return false;
        if (y < 0 || y >= board[0].size())
            return false;
        //print(board);
        if (board[x][y] != word[i])
            return false;
        if (i == word.size()-1)
            return true;
        char was = board[x][y];
        board[x][y] = '+'; // mark as already visited
        bool rc = dfs(board, word, i+1, x+1, y)
            || dfs(board, word, i+1, x-1, y)
            || dfs(board, word, i+1, x, y+1)
            || dfs(board, word, i+1, x, y-1);
        board[x][y] = was;
        return rc;
    }

    bool exist(vector<vector<char>>& board, string word) {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
                if (dfs(board, word, 0, i, j))
                    return true;
        }
        return false;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<char>> t1 = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    vector<vector<char>> t2 = {
        {'A','B','C','E'},
        {'S','F','E','S'},
        {'A','D','E','E'}
    };

    Solution s;
    assert(s.exist(t1, "ABCCED") == true);
    assert(s.exist(t1, "SEE") == true);
    assert(s.exist(t2, "ABCESEEEFS") == true);

    return 0;
}
