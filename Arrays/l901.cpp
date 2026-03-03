#include <cassert>
#include <vector>
#include <utility>

using namespace std;

class StockSpanner {
public:
    StockSpanner() {}

    int next(int price) {
        int less = 1;
        while (!prices_.empty() && prices_.back().first <= price)
        {
            auto p = prices_.back();
            prices_.pop_back();
            less += p.second;
        }
        prices_.push_back({price, less});
        return less;
    }
private:
    vector<pair<int, int>> prices_; // {price, less than that}
};

int main(int argc, char const *argv[])
{
    StockSpanner stockSpanner;
    assert(stockSpanner.next(100) == 1);
    assert(stockSpanner.next(80) == 1);
    assert(stockSpanner.next(60) == 1);
    assert(stockSpanner.next(70) == 2);
    assert(stockSpanner.next(60) == 1);
    assert(stockSpanner.next(75) == 4);
    assert(stockSpanner.next(85) == 6);
    return 0;
}
