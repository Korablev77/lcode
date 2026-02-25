#include <cassert>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        bool minus = x < 0;
        unsigned int y;
        if (x < 0)
        {
            y = static_cast<unsigned int>(x);
            y = UINT32_MAX - y + 1;
        }
        else
            y = x;
        unsigned int res = 0;
        assert(sizeof(res) == 4);
        const unsigned int limit = INT32_MAX / 8;
        while (y > 0)
        {
            unsigned int bump = res;

            // x10 mul can lead to overflow
            if (res >= limit)
            {
                for (int i = 0; i < 10; i++)
                {
                    bump += res;
                    if (bump <= res)
                        return 0;
                }

            } else {
                bump *= 10U;
            }

            bump += (y % 10);
            y /= 10;
            if (bump < res)
                return 0;
            res = bump;
        }
        if (res > (unsigned int)INT32_MAX)
            return 0;
        return minus ? -res : res;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    assert(s.reverse(123) == 321);
    assert(s.reverse(-123) == -321);
    return 0;
}
