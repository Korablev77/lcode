// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

int rand7();

class Solution {
public:
    int rand10() {
        for (;;)
        {
            // let's use number system with 7 base: x = a + 7*b, where a,b in [0, 6]
            int r1 = rand7() - 1; // 0-6
            int r2 = 7 * (rand7() - 1); // 7-42
            int x = r1 + r2; // in range 0-48
            if (x >= 40) // cause 41-48 makes distribution non-uniform
                continue;
            return (x % 10) + 1;

    }
};
