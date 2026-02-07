// You are given a string s.
// We want to partition the string into as many parts as possible
// so that each letter appears in at most one part. For example,
// the string "ababcc" can be partitioned into ["abab", "cc"],
// but partitions such as ["aba", "bcc"] or ["ab", "ab", "cc"] are invalid.

// Return a list of integers representing the size of these parts.

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    static bool cmp (const pair<int, int> & a, const pair<int, int> & b)
    {
        if (a.first < b.first)
            return true;
        if (a.first == b.first)
            return a.second < b.second;
        return false;
    }

    vector<int> partitionLabels(string s) {
        pair<int, int> pos[30];
        for (int i = 0; i < 30; i++)
        {
            pos[i].first = -1;
            pos[i].second = -1;
        }
        for (int i = 0; i < s.size(); i++)
        {
            if (pos[s[i] - 'a'].first == -1)
                pos[s[i] - 'a'].first = i;
            pos[s[i] - 'a'].second = i;
        }
        std::sort(pos, &pos[29], cmp);

        vector<int> res;
        int i = 0, j = 1;
        while (i < 30)
        {
            if (pos[i].first == -1)
            {
                j = ++i + 1;
                continue;
            }
            pair<int, int> merged = pos[i];
            while (j < 30 && merged.second > pos[j].first)
            {
                merged.second = std::max(merged.second, pos[j].second);
                j++;
            }
            res.push_back(merged.second - merged.first + 1);
            i = j++;
        }

        return res;
    }
};

int main(int argc, char const *argv[])
{
    string t1 = "ababcbacadefegdehijhklij";
    string t2 = "eccbbbbdec";

    Solution s;
    assert(s.partitionLabels(t1) == vector<int>({9,7,8}));
    assert(s.partitionLabels(t2) == vector<int>({10}));
    return 0;
}
