#include <cassert>
#include <unordered_map>

using namespace std;

// code below is awful but works! and even without using std::list :)
// if i had more time i would properly implement double-linked list at least
class LFUCache {
public:
    LFUCache(int capacity) : _cap(capacity) { }
    ~LFUCache()
    {
        while (_list != nullptr)
        {
            ListNode * next = _list->_next;
            delete _list;
            _list = next;
        }
    }

    int get(int key) {
        auto map_it = _storage.find(key);
        if (map_it == _storage.end())
            return -1;

        ListNode * p = map_it->second._list_pos;
        p->_cnt++;

        ListNode * next = p->_next;
        if (next == nullptr || next->_cnt > p->_cnt)
            return map_it->second._val;

        int cnt = p->_cnt;
        while (cnt >= next->_cnt && (next->_next != nullptr && next->_next->_cnt <= cnt))
            next = next->_next;

        // now swap "next" and p places so that p comes right after "next"
        moveNode(p, next);
        return map_it->second._val;
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
            int to_remove = _list->_key;
            removeNodeFront();
            _storage.erase(to_remove);
        }

        MapItem i;
        i._val = value;
        i._list_pos = addNodeFront(key);
        _storage.insert({key, i});
    }
private:
    struct ListNode
    {
        int _key;
        int _cnt = 1;

        // double linked list cause we want to swap nodes in the middle
        ListNode * _next = nullptr;
        ListNode * _prev = nullptr;
    };

    ListNode * addNodeFront(int key)
    {
        ListNode * n = new ListNode;
        n->_key = key;
        if (_list == nullptr)
        {
            _list = n;
            return n;
        }

        // fast track!
        if (_list->_cnt > 1)
        {
            n->_next = _list;
            _list->_prev = n;
            _list = n;
            return n;
        }

        ListNode * p = _list;
        while (1 == p->_cnt && (p->_next != nullptr && p->_next->_cnt == 1))
            p = p->_next;

        // insert node n AFTER p
        if (p->_next != nullptr)
            p->_next->_prev = n;
        n->_next = p->_next;
        p->_next = n;
        n->_prev = p;

        return n;
    }

    void removeNodeFront()
    {
        ListNode * next = _list->_next;
        if (next != nullptr)
            next->_prev = nullptr;
        delete _list;
        _list = next;
    }

    // place p1 right AFTER p2
    void moveNode(ListNode * p1, ListNode * p2)
    {
        // unlink p1 from its previous position
        ListNode * next = p1->_next;
        if (p1->_prev != nullptr)
            p1->_prev->_next = p1->_next;
        if (p1->_next != nullptr)
            p1->_next->_prev = p1->_prev;

        // insert p1 after p2
        p1->_next = p2->_next;
        if (p2->_next != nullptr)
            p2->_next->_prev = p1;
        p2->_next = p1;
        p1->_prev = p2;

        if (_list == p1) // meh
            _list = next;
    }

    struct MapItem
    {
        int _val;
        ListNode * _list_pos;
    };

    int _cap;
    unordered_map<int, MapItem> _storage;
    ListNode * _list = nullptr; // head of the list
};

static void long_test1()
{
    LFUCache lfu(10);
    lfu.get(5);
    lfu.get(8);
    lfu.get(9);
    lfu.put(4,30);
    lfu.put(9,3);
    lfu.get(9);
    lfu.get(10);
    lfu.get(10);
    lfu.put(6,14);
    lfu.put(3,1);
    lfu.get(3);
    lfu.put(10,11);
    lfu.get(8);
    lfu.put(2,14);
    lfu.get(1);
    lfu.get(5);
    lfu.get(4);
    lfu.put(11,4);
    lfu.put(12,24);
    lfu.put(5,18);
    lfu.get(13);
    lfu.put(7,23);
    lfu.get(8);
    lfu.get(12);
    lfu.put(3,27);
    lfu.put(2,12);
    lfu.get(5);
    lfu.put(2,9);
    lfu.put(13,4);
    lfu.put(8,18);
    lfu.put(1,7);
    lfu.get(6);
    lfu.put(9,29);
    lfu.put(8,21);
    lfu.get(5);
    lfu.put(6,30);
    lfu.put(1,12);
    lfu.get(10);
    lfu.put(4,15);
    lfu.put(7,22);
    lfu.put(11,26);
    lfu.put(8,17);
    lfu.put(9,29);
    lfu.get(5);
    lfu.put(3,4);
    lfu.put(11,30);
    lfu.get(12);
    lfu.put(4,29);
    lfu.get(3);
    lfu.get(9);
    lfu.get(6);
    lfu.put(3,4);
    lfu.get(1);
    lfu.get(10);
    lfu.put(3,29);
    lfu.put(10,28);
    lfu.put(1,20);
    lfu.put(11,13);
    lfu.get(3);
    lfu.put(3,12);
    lfu.put(3,8);
    lfu.put(10,9);
    lfu.put(3,26);
    assert(lfu.get(8) == 17);
    lfu.get(7);
    lfu.get(5);
    lfu.put(13,17);
    lfu.put(2,27);
    lfu.put(11,15);
    lfu.get(12);
    lfu.put(9,19);
    lfu.put(2,15);
    lfu.put(3,16);
    lfu.get(1);
    lfu.put(12,17);
    lfu.put(9,1);
    lfu.put(6,19);
    lfu.get(4);
    lfu.get(5);
    lfu.get(5);
    lfu.put(8,1);
    lfu.put(11,7);
    lfu.put(5,2);
    lfu.put(9,28);
    lfu.get(1);
    lfu.put(2,2);
    lfu.put(7,4);
    lfu.put(4,22);
    lfu.put(7,24);
    lfu.put(9,26);
    lfu.put(13,28);
}

static void long_test2()
{
    LFUCache lfu(10);
    lfu.put(10,13);
    lfu.put(3,17);
    lfu.put(6,11);
    lfu.put(10,5);
    lfu.put(9,10);
    lfu.get(13);
    lfu.put(2,19);
    lfu.get(2);
    lfu.get(3);
    lfu.put(5,25);
    lfu.get(8);
    lfu.put(9,22);
    lfu.put(5,5);
    lfu.put(1,30);
    lfu.get(11);
    lfu.put(9,12);
    lfu.get(7);
    lfu.get(5);
    lfu.get(8);
    lfu.get(9);
    lfu.put(4,30);
    lfu.put(9,3);
    lfu.get(9);
    lfu.get(10);
    lfu.get(10);
    lfu.put(6,14);
    lfu.put(3,1);
    lfu.get(3);
    lfu.put(10,11);
    lfu.get(8);
    lfu.put(2,14);
    lfu.get(1);
    lfu.get(5);
    lfu.get(4);
    lfu.put(11,4);
    lfu.put(12,24);
    lfu.put(5,18);
    lfu.get(13);
    lfu.put(7,23);
    lfu.get(8);
    lfu.get(12);
    lfu.put(3,27);
    lfu.put(2,12);
    lfu.get(5);
    lfu.put(2,9);
    lfu.put(13,4);
    lfu.put(8,18);
    lfu.put(1,7);
    lfu.get(6);
    lfu.put(9,29);
    lfu.put(8,21);
    assert(lfu.get(5) == 18);
    lfu.put(6,30);
    lfu.put(1,12);
    lfu.get(10);
    lfu.put(4,15);
    lfu.put(7,22);
    lfu.put(11,26);
    lfu.put(8,17);
    lfu.put(9,29);
    lfu.get(5);
    lfu.put(3,4);
    lfu.put(11,30);
    lfu.get(12);
    lfu.put(4,29);
    lfu.get(3);
    lfu.get(9);
    lfu.get(6);
    lfu.put(3,4);
    lfu.get(1);
    lfu.get(10);
    lfu.put(3,29);
    lfu.put(10,28);
    lfu.put(1,20);
    lfu.put(11,13);
    lfu.get(3);
    lfu.put(3,12);
    lfu.put(3,8);
    lfu.put(10,9);
    lfu.put(3,26);
    assert(lfu.get(8) == 17);
    assert(lfu.get(7) == -1);
    assert(lfu.get(5) == 18);
    lfu.put(13,17);
    lfu.put(2,27);
    lfu.put(11,15);
    lfu.get(12);
    lfu.put(9,19);
    lfu.put(2,15);
    lfu.put(3,16);
    lfu.get(1);
    lfu.put(12,17);
    lfu.put(9,1);
    lfu.put(6,19);
    lfu.get(4);
    lfu.get(5);
    lfu.get(5);
    lfu.put(8,1);
    lfu.put(11,7);
    lfu.put(5,2);
    lfu.put(9,28);
    lfu.get(1);
    lfu.put(2,2);
    lfu.put(7,4);
    lfu.put(4,22);
    lfu.put(7,24);
    lfu.put(9,26);
    lfu.put(13,28);
    lfu.put(11,26);
}

int main(int argc, char const *argv[])
{
    LFUCache lfu(2);
    lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
    lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
    assert(lfu.get(1) == 1);      // return 1
                     // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                     // cache=[3,1], cnt(3)=1, cnt(1)=2
    assert(lfu.get(2) == -1);      // return -1 (not found)
    assert(lfu.get(3) == 3);      // return 3
                     // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                     // cache=[4,3], cnt(4)=1, cnt(3)=2
    assert(lfu.get(1) == -1);      // return -1 (not found)
    assert(lfu.get(3) == 3);      // return 3
                     // cache=[3,4], cnt(4)=1, cnt(3)=3
    assert(lfu.get(4) == 4);      // return 4
                     // cache=[4,3], cnt(4)=2, cnt(3)=3

    LFUCache lfu1(3);
    lfu1.put(1, 1);
    lfu1.put(2, 2);
    lfu1.put(3, 3);
    lfu1.put(4, 4);
    lfu1.get(4);
    lfu1.get(3);
    lfu1.get(2);
    lfu1.get(1);
    assert(lfu1.get(4) == 4);
    assert(lfu1.get(3) == 3);
    assert(lfu1.get(2) == 2);
    assert(lfu1.get(1) == -1);
    lfu1.put(5, 5);
    lfu1.get(1);
    lfu1.get(2);
    lfu1.get(3);
    lfu1.get(4);
    lfu1.get(5);

    long_test1();
    long_test2();
    return 0;
}
