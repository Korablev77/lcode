#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int cur_free = 0, max_free = 0;
        int first_range = 0;
        for (int i = 0; i < seats.size(); i++)
        {
            if (seats[i] == 0)
                cur_free++;

            if (seats[i] == 1)
            {
                if (max_free == 0)
                    first_range = cur_free;
                max_free = max(max_free, cur_free);
                cur_free = 0;
            }
        }

        int middle = max_free % 2 != 0 ? max_free / 2 + 1 : max_free / 2;
        if (seats.back() == 0)
            middle = max(cur_free, middle);
        if (seats.front() == 0)
            middle = max(middle, first_range);
        return middle;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = { 1, 0, 0, 0, 1, 0, 1 };
    vector<int> t2 = { 1, 0, 0, 0 };
    vector<int> t3 = { 0, 1 };
    vector<int> t4 = { 0, 0, 1 };
    vector<int> t5 = { 1, 0, 0, 1 };

    Solution s;
    assert(s.maxDistToClosest(t1) == 2);
    assert(s.maxDistToClosest(t2) == 3);
    assert(s.maxDistToClosest(t3) == 1);
    assert(s.maxDistToClosest(t4) == 2);
    assert(s.maxDistToClosest(t5) == 1);

    return 0;
}