// F(0) = 0, F(1) = 1
// F(n) = F(n - 1) + F(n - 2), for n > 1.

// Approach 1: Reccursion
// T.C:0(2^n) , S.C;0(n)
class Solution {
public:
    int fib(int n) {

        if (n <= 1)
            return n;

        return fib(n - 1) + fib(n - 2);
    }
};


// Approach 2: iterative
// T.C: 0(n), S.C: 0(1)
class Solution {
public:
    int fib(int n) {

        if (n <= 1)
            return n;

        int a = 0, b = 1;
        for (int i = 2; i <= n; i++) {
            int c = a + b;
            a = b;
            b = c;
        }
        return b;
    }
};

// Approach 3: DP Tabulation/Bottom Up
// T.C:0(n), S.C:0(n)
class Solution {
public:
    int fib(int n) {
        int f[n+1];
        if (n == 1 || n == 0) return n;
        f[0] = 0;
        f[1] = 1; 
        for (int i=2; i<=n; i++) {
            f[i] = f[i-1] + f[i-2];
        }
        return f[n];
    }
};
