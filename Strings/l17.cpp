// Given a string containing digits from 2-9 inclusive,
// return all possible letter combinations that the number could represent
// Return the answer in any order.

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> buttons = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

        vector<string> sets;
        for (auto c : digits)
        {
            int i = c - '0';
            sets.push_back(buttons[i]);
        }

        vector<string> res;
        for (char x : sets[0])
            res.push_back(string(1, x));

        for (int i = 1; i < sets.size(); i++)
        {
            string & w = sets[i];
            vector<string> res_new;
            for (char c : w)
            {
                for (int j = 0; j < res.size(); j++)
                {
                    string x = res[j];
                    string y = x+c;
                    res_new.push_back(x + c);
                }
            }
            res = std::move(res_new);
        }
        return res;
    }
};
int main(int argc, char const *argv[])
{
    Solution s;
    assert(s.letterCombinations("23") ==
        vector<string>({"ad","ae","af","bd","be","bf","cd","ce","cf"}));
    return 0;
}
