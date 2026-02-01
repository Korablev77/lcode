#include <cassert>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : _cap(capacity) { }

    int get(int key) {
        auto it = _storage.find(key);
        if (it == _storage.end())
            return -1;
        _list.push_front(key);
        _list.erase(it->second._iter);
        it->second._iter = _list.begin();
        return it->second._val;
    }
    
    void put(int key, int value) {
        // yes it's 2 looups instead of 1, but code keeps compact
        if (get(key) != -1)
        {
            _storage[key]._val = value;
            return;
        }

        // invalidate least recently used element
        if (_storage.size() >= _cap)
        {
            int to_remove = _list.back();
            _list.pop_back();
            _storage.erase(to_remove);
        }

        _list.push_front(key);

        Item it;
        it._val = value;
        it._iter = _list.begin();

        _storage.insert({key, it});
    }
private:
    struct Item
    {
        int _val;
        list<int>::iterator _iter;
    };
    int _cap;
    unordered_map<int, Item> _storage;
    list<int> _list;
};

int main(int argc, char const *argv[])
{
    LRUCache lRUCache(2);
    lRUCache.put(1, 1); // cache is {1=1}
    lRUCache.put(2, 2); // cache is {1=1, 2=2}
    assert(lRUCache.get(1) == 1);    // return 1
    lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    assert(lRUCache.get(2) == -1);    // returns -1 (not found)
    lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    assert(lRUCache.get(1) == -1);    // return -1 (not found)
    assert(lRUCache.get(3) == 3);    // return 3
    assert(lRUCache.get(4) == 4);    // return 4
    return 0;
}
