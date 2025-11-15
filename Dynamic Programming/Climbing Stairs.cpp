

// INTUTION:reccursion-> O(2ⁿ) ->TLE

// approach 1:
// T.C: 0(n)
// solve(i, n) is called at most once for every value of i from 0 to n.
// After the first call, the result is stored in t[i] and used if same value is encountered.


class Solution {
public:

//Memoization
    // Recursive function with memoization
    int solve(int n, vector<int>& dp) {
        if (n < 0) return 0;       // No way to climb negative steps
        if (n == 0) return 1;      // return 1 -> we reached destination 

        if (dp[n] != -1) return dp[n];  // if curr position is already computed 

        // Compute the number of ways and memoize(store) it
        //there is either 1 or 2 steps to reach destination 
        return dp[n] = solve(n - 1, dp) + solve(n - 2, dp);
    }

    int climbStairs(int n) {
        vector<int> dp(n + 1, -1);  // Initialize memo table 
        return solve(n, dp);
    }
};


// Approach 2:
// T.C:0(n)
class Solution {
public:
    // BOTTOM-UP

    int climbStairs(int n) {
        if(n==0 ||n==1 ||n==2){
            return n;
        }
        // Initialize dp array with -1:not yet calculated
        vector<int> dp(n + 1, -1);

        dp[0] = 0; // 0 way to climb 0 stairs
        dp[1] = 1; // 1 way to climb 1 stairs
        dp[2] = 2; // 2 way to climb 2 stairs

        // no of ways to climn n stairs=dp[n-1]+dp[n-2]
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n];
    }
};
