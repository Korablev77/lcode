// Given two strings s1 and s2, return true if s2 contains a permutation of s1.
// In other words, return true if one of s1's permutations is the substring of s2.

#include <cassert>
#include <cstring>
#include <string>

using namespace std;

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int vocab1[30];
        memset(vocab1, 0, 30 * 4);
        int hash1 = 0;
        for (auto x : s1)
        {
            hash1 += (int)x;
            vocab1[x - 'a']++;
        }

        int len1 = s1.size();
        int len2 = s2.size();
        if (len1 > len2)
            return false;

        int vocab2[30];
        memset(vocab2, 0, 30 * 4);
        int hash2 = 0;
        for (int i = 0; i < len1; i++)
        {
            hash2 += (int)s2[i];
            vocab2[s2[i] - 'a']++;
        }
        for (int i = len1; i < len2; i++)
        {
            if (hash1 == hash2 && memcmp(vocab1, vocab2, 30 * 4) == 0)
                return true;
            hash2 -= (int)s2[i-len1];
            hash2 += (int)s2[i];
            assert(vocab2[s2[i-len1] - 'a'] > 0);
            vocab2[s2[i-len1] - 'a']--;
            vocab2[s2[i] - 'a']++;
        }

        return memcmp(vocab1, vocab2, 30 * 4) == 0;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    assert(s.checkInclusion("ab", "eidbaooo") == true);
    assert(s.checkInclusion("ab", "eidboaoo") == false);
    assert(s.checkInclusion("adc", "dcda") == true);

    return 0;
}

