// You are given an array prices where prices[i] is the price of a given stock on the ith day.
// You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
// Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int buy = prices[0];
        int profit = 0; 
        for (int i = 1; i < prices.size(); i++)
        {
            buy = min(buy, prices[i]);
            profit = max(profit, prices[i] - buy);
        }
        return profit;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> t1 = {7, 1, 5, 3, 6, 4};
    vector<int> t2 = {7, 6, 4, 3, 1};
    Solution s;
    assert(s.maxProfit(t1) == 5);
    assert(s.maxProfit(t2) == 0);

    return 0;
}
