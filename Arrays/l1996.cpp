#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

static bool cmp_attack (const vector<int> & a, const vector<int> & b)
{
    if (a[0] > b[0])
        return true;
    if (a[0] == b[0])
        return a[1] < b[1];
    return false;
}

class Solution {
public:
    int numberOfWeakCharacters(vector<vector<int>>& properties) {
        std::sort(properties.begin(), properties.end(), cmp_attack);
        
        int weak = 0;
        int max_def = properties[0][1];
        for (int i = 1; i < properties.size(); i++)
        {
            // attack of i is always <= i-1
            // defense is less for the same attack group => weak counter is not increased
            if (properties[i][1] < max_def)
                weak++;
            max_def = max(max_def, properties[i][1]);
        }
        return weak;
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> t1 = {{5,5},{6,3},{3,6}};
    vector<vector<int>> t2 = {{1,5},{10,4},{4,3}};

    Solution s;
    assert(s.numberOfWeakCharacters(t1) == 0);
    assert(s.numberOfWeakCharacters(t2) == 1);
    return 0;
}
