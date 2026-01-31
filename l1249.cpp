#include <cassert>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        vector<int> stack;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
                stack.push_back(i+1);
            if (s[i] == ')')
            {
                if (stack.size() > 0 && stack.back() >= 0)
                    stack.pop_back();
                else
                    stack.push_back(-(i+1));
            }
        }

        // so far we have only invalid parent sequences in the stack
        // all is left to do is format resulting string
        char * r = (char*)malloc(s.size() - stack.size() + 1);
        int j = 0;
        int k = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (j < stack.size() && abs(stack[j])-1 == i)
            {
                j++;
                continue;
            }
            r[k++] = s[i];
        }
        r[s.size() - stack.size()] = '\0';
        string res = r;
        free(r);
        return res;
    }
};

int main(int argc, char const *argv[])
{
    string s1 = "lee(t(c)o)de)";
    string s2 = "a)b(c)d";
    string s3 = "))((";
    string s4 = "())()(((";

    Solution sol;
    assert(sol.minRemoveToMakeValid(s1) == "lee(t(c)o)de");
    assert(sol.minRemoveToMakeValid(s2) == "ab(c)d");
    assert(sol.minRemoveToMakeValid(s3) == "");
    assert(sol.minRemoveToMakeValid(s4) == "()()");

    return 0;
}
