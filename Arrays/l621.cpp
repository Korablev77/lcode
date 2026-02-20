// You are given an array of CPU tasks, each labeled with a letter from A to Z, and a number n.
// Each CPU interval can be idle or allow the completion of one task.
// Tasks can be completed in any order, but there's a constraint: there has to be a gap
// of at least n intervals between two tasks with the same label.
// Return the minimum number of CPU intervals required to complete all tasks.

#include <algorithm>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

// turns out that a SIMPLE solution exists:
// res = (maxFreq - 1) * (n + 1) + maxCount;
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int pending[30];
        memset(pending, 0, 30 * sizeof(int));
        for (int i = 0; i < tasks.size(); i++)
            pending[tasks[i] - 'A']++;

        int executing[30];
        memset(executing, 0, 30 * sizeof(int));

        int * it = std::max_element(pending, pending + 30);
        (*it)--;
        executing[it-pending] = 1;
        int i = 1;
        int to_process = tasks.size() - 1;
        while (to_process > 0)
        {
            i++;
            // remove tasks which are done
            int executing_tmp[30];
            memset(executing_tmp, 0, 30 * sizeof(int));

            for (int j = 0; j < 30; j++)
                if (i - executing[j] <= n)
                    executing_tmp[j] = executing[j];
            memcpy(executing, executing_tmp, 30 * 4);

            // push new task or idle:
            // find available and most frequent task and make sure it's not executing now
            int max = 0;
            int k = 30;
            for (int j = 0; j < 30; j++)
            {
                if (executing[j] == 0 && pending[j] > max)
                {
                    max = pending[j];
                    k = j;
                }
            }

            // k == pending.size() means IDLE
            if (k < 30)
            {
                executing[k] = i;
                pending[k]--;
                to_process--;
            }
        }
        return i;
    }
};

int main(int argc, char const *argv[])
{
    vector<char> t1 = {'A','A','A','B','B','B'};
    vector<char> t2 = {'A','C','A','B','D','B'};
    vector<char> t3 = {'A','A','A','B','B','B'};
    vector<char> t4 = {'A','B','C','D','E','A','B','C','D','E'};
    vector<char> t5 = {'A','A'};

    Solution s;
    assert(s.leastInterval(t1, 2) == 8);
    assert(s.leastInterval(t2, 1) == 6);
    assert(s.leastInterval(t3, 3) == 10);
    assert(s.leastInterval(t4, 4) == 10);
    assert(s.leastInterval(t5, 2) == 4);

    return 0;
}
