// Given a string s, remove duplicate letters so that every letter appears once and only once.
// You must make sure your result is the smallest in lexicographical order among all possible results.

#include <cassert>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        int letters[30];
        memset(letters, 0, 30*4);
        for (char x : s)
            letters[x - 'a']++;
        char used[30];
        memset(used, 0, 30);
        string res;
        for (int i = 0; i < s.size(); i++)
        {
            while (!res.empty() && letters[res.back() - 'a'] > 0 && s[i] < res.back())
            {
                // "aba" - can't drop 'b' because then we got 'aa', so just skip second 'a'
                // "ab" better than "ba"!
                if (used[s[i] - 'a'])
                    break;
                used[res.back() - 'a'] = 0; // each letter must be used once
                res.pop_back();

            }

            if (letters[s[i] - 'a']-- > 0 && !used[s[i] - 'a'])
            {
                res.push_back(s[i]);
                used[s[i] - 'a'] = 1;
            }
        }

        return res;
    }
};

// acdbc
// aaaabbbb => ab
// aaabbbccc => abc
// abcabc
int main(int argc, char const *argv[])
{
    Solution s;
    assert(s.removeDuplicateLetters("bcabc") == "abc");
    assert(s.removeDuplicateLetters("cbacdcbc") == "acdb");
    assert(s.removeDuplicateLetters("abacb") == "abc");

    return 0;
}
