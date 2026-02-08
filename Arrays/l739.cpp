// Given an array of integers temperatures represents the daily temperatures,
// return an array answer such that answer[i] is the number of days you
// have to wait after the ith day to get a warmer temperature.
// If there is no future day for which this is possible, keep answer[i] == 0 instead.

#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size(), 0);
        vector<int> stack;
        stack.push_back(0);

        for (int i = 1; i < temperatures.size(); i++)
        {
            while (stack.size() > 0 && temperatures[stack.back()] < temperatures[i])
            {
                auto p = stack.back();
                stack.pop_back();
                res[p] = i - p;
                continue;
            }

            // stack.back() >= temperatures[i])
            stack.push_back(i);
        }

        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = {73,74,75,71,69,72,76,73};
    vector<int> t2 = {30,40,50,60};
    vector<int> t3 = {30,60,90};

    Solution s;
    assert(s.dailyTemperatures(t1) == vector<int>({1,1,4,2,1,1,0,0}));
    assert(s.dailyTemperatures(t2) == vector<int>({1,1,1,0}));
    assert(s.dailyTemperatures(t3) == vector<int>({1,1,0}));

    return 0;
}

