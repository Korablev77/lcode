#include <cassert>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1)
            return s;
        vector<string> rows(numRows);
        int cur_row = 0;
        bool down = true; // traversal direction
        for (int i = 0; i < s.size(); i++)
        {
            rows[cur_row] += s[i];
            if (down && cur_row < numRows - 1)
            {
                cur_row++;
                continue;
            }
            if (down)
            {
                down = false;
                cur_row--;
                continue;
            }
            if (!down && cur_row > 0)
            {
                cur_row--;
                continue;
            }
            assert(!down);
            down = true;
            cur_row++;
        }
        string res;
        for (int i = 0; i < numRows; i++)
            res += rows[i];
        return res;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    assert(s.convert("PAYPALISHIRING", 3) == "PAHNAPLSIIGYIR");
    assert(s.convert("PAYPALISHIRING", 4) == "PINALSIGYAHRPI");
    return 0;
}
