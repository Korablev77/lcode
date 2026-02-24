#include <string>

using namespace std;

// x + y = K
// x^2 + y^2 -> max
// 2x*(x-K) -> max => x -> max => x = 9
class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if (num * 9 < sum)
            return "";
        int nines = sum / 9;
        int rem = sum % 9;
        string res;
        for (int i = 0; i < num; i++)
        {
            if (nines-- > 0)
                res += '9';
            else if (rem > 0)
            {
                res += (char)rem + '0';
                rem = 0;
            } else
                res += '0';
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    return 0;
}
