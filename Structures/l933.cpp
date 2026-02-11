// You have a RecentCounter class which counts the number of recent requests within a certain time frame.
// Implement the RecentCounter class:
// RecentCounter() Initializes the counter with zero recent requests.
// int ping(int t) Adds a new request at time t, where t represents some time in milliseconds,
// and returns the number of requests that has happened in the past 3000 milliseconds (including the new request).
// Specifically, return the number of requests that have happened in the inclusive range [t - 3000, t].
// It is guaranteed that every call to ping uses a strictly larger value of t than the previous call.

#include <cassert>
#include <vector>
#include <string>
#include <utility>

using namespace std;

class RecentCounter {
public:
    int ping(int t) {
        tms_.push_back(t);
        auto p = tms_.begin();
        for (; p != tms_.end() && *p < t - 3000; p++);
        tms_.erase(tms_.begin(), p);
        return tms_.size();
    }

private:
    vector<int> tms_;
};

int main(int argc, char const *argv[])
{
    RecentCounter s;
    vector<pair<int, int>> v = {{1,1}, {100,2}, {3001,3}, {3002,3}};
    for (auto c : v)
        assert(s.ping(c.first) == c.second);
    return 0;
}
