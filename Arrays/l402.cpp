// Given string num representing a non-negative integer num,
// and an integer k, return the smallest possible integer after
// removing k digits from num.

#include <cassert>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string removeKdigits(string num, int k) {
        string s;
        for (int i = 0; i < num.size(); i++)
        {
            while (s.size() > 0 && (int)s.back() > num[i] && k > 0)
            {
                s.pop_back();
                k--;
            }
            s.push_back(num[i]);
        }
        while (k-- > 0 && s.size() > 0)
            s.pop_back();
        while (s.size() > 0 && s.front() == '0')
            s.erase(0, 1);

        return s.empty() ? "0" : s;
    }
};

// 123456789
//  23456789
//  12345678
// 1234
// 234
// 123
// 134
int main(int argc, char const *argv[])
{
    Solution s;
    assert(s.removeKdigits("1432219", 3) == "1219");
    assert(s.removeKdigits("10200", 1) == "200");
    assert(s.removeKdigits("10", 2) == "0");
    assert(s.removeKdigits("33526221184202197273", 19) == "0");

    return 0;
}
