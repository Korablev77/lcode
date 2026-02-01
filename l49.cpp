#include <cstring>
#include <vector>
#include <unordered_set>
#include <string>

#include <stdio.h>

using namespace std;

// Easier way is just to simply sort string content!
class Solution {
public:
    struct Word
    {
        Word(const Word & o) : _group(o._group)
        {
            memcpy(_letters, o._letters, 30 * 4);
        }
        Word(const string & s)
        {
            for (char c : s)
                _letters[c - 'a']++;
        }

        int _letters[30] = {};
        int _group = -1; // position in grouped vector

        bool operator == (const Word & other) const
        {
            return memcmp(&_letters, &other._letters, 30 * 4) == 0;
        }
    };

    struct WordHash {
        size_t operator()(const Word & w) const {
            size_t hash = 0;
            for (int i = 0; i < 30; i++)
                hash += i * w._letters[i];
            return hash;
        }
    };

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_set<Word, WordHash> processed;
        vector<vector<string>> grouped;
        for (int i = 0; i < strs.size(); i++)
        {
            Word w(strs[i]);
            auto it = processed.find(w);
            if (it == processed.end())
            {
                w._group = grouped.size();
                processed.insert(w);
                vector<string> new_group = { strs[i] };
                grouped.push_back(new_group);
                continue;
            }
            grouped[it->_group].push_back(strs[i]);
            w._group = it->_group;
            processed.insert(w);
        }
        return grouped;
    }
};

int main(int argc, char const *argv[])
{
    vector<string> t1 = { "eat","tea","tan","ate","nat","bat" };
    vector<string> t2 = { "" };
    vector<string> t3 = { "a" };

    Solution s;
    auto r1 = s.groupAnagrams(t1);
    for (auto x : r1)
    {
        printf("\n");
        for (auto y : x)
            printf("%s ", y.c_str());
    }
    printf("\n");
    return 0;
}