#include <cassert>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

class NestedInteger {
public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const { return v.empty(); };

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const { };

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const { vector<NestedInteger> t; return t; };
private:
    vector<NestedInteger> v;
    int x;
};

class NestedIterator {
public:
    using iterator = vector<NestedInteger>::const_iterator;
    NestedIterator(vector<NestedInteger> &nestedList) : it_(nestedList.begin()), end_(nestedList.end())
    {}

    int next() {
        assert(it_->isInteger());
        int res = it_->getInteger();
        it_++;
        return res;
    }

    bool hasNext() { posToInteger(); return !finished(); }
private:
    bool finished() { return it_ == end_ && stack_.empty(); }

    void posToInteger() // set it_ position to the next integer
    {
        while (true)
        {
            adjustIter();
            if (finished())
                return;
            if (it_->isInteger())
                return;

            // so we are iterating over the list
            stack_.push_back({it_ + 1, end_});
            end_ = it_->getList().end();
            it_ = it_->getList().begin();
        }
    }

    void adjustIter()
    {
        while (it_ == end_ && !stack_.empty())
        {
            auto p = stack_.back();
            it_ = p.first;
            end_ = p.second;
            stack_.pop_back();
        }
    }
    iterator it_;
    iterator end_;
    vector<pair<iterator, iterator>> stack_;
};

int main(int argc, char const *argv[])
{
    vector<NestedInteger> v;
    NestedIterator s(v);
    return 0;
}
