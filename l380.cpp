#include <cassert>
#include <vector>
#include <random>
#include <unordered_map>
#include <utility>

using namespace std;

class RandomizedSet {
public:
    RandomizedSet() : _gen(_rd()) {
    }
    
    bool insert(int val) {
        if (_map.find(val) != _map.end())
            return false;
        size_t idx = _vec.size();
        _vec.push_back(val);
        _map.insert({val, idx});
        return true;
    }
    
    bool remove(int val) {
        auto x = _map.find(val);
        if (x == _map.end())
            return false;

        int key = x->first;
        size_t pos = x->second;

        int y = _vec.back();
        _vec[pos] = y;
        _vec.pop_back();
        _map.find(y)->second = pos;
        _map.erase(key);
        return true;
    }
    
    int getRandom() {
        uniform_int_distribution<> distr(0, _vec.size() - 1);
        return _vec[distr(_gen)];
    }
private:
    random_device _rd; 
    mt19937 _gen;

    vector<int> _vec; // main storage
    unordered_map<int, size_t> _map; // value -> vec position
};

int main(int argc, char const *argv[])
{
    RandomizedSet s;
    assert(s.insert(1));
    assert(!s.remove(2));
    assert(s.insert(2));
    assert(s.getRandom());
    assert(s.remove(1));
    assert(!s.insert(2));
    assert(s.getRandom() == 2);

    RandomizedSet s1;
    assert(!s1.remove(0));
    assert(!s1.remove(0));
    assert(s1.insert(0));
    assert(s1.getRandom() == 0);
    assert(s1.remove(0));
    assert(s1.insert(0));
    return 0;
}
