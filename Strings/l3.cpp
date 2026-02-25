#include <cassert>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        char letters[256];
        memset(letters, 0, 256);
        int window_size = 0;
        int max = 0;
        for (int i = 0; i < s.size(); i++)
        {
            while (letters[s[i]] > 0)
            {
                letters[s[i - window_size]]--;
                window_size--;
            }
            letters[s[i]]++;
            window_size++;
            max = std::max(max, window_size);
        }
        return max;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    assert(s.lengthOfLongestSubstring("abcabcbb") == 3);
    assert(s.lengthOfLongestSubstring("pwwkew") == 3);
    return 0;
}
