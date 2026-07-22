// Appproach 1:Reccusion
// T.C:O(n^amount)
	​

class Solution {
public:


    int solve(vector<int>& coins, int amount, int cnt) {
        if (amount == 0) {
            return cnt;
        }
        if (amount < 0) {
            return INT_MAX;
        }
        cnt++;
        int minCnt = INT_MAX;
        for (int i = 0; i < coins.size(); i++) {
            minCnt = min(solve(coins, amount - coins[i], cnt), minCnt);
        }
        cnt--;
        return minCnt;
    }
    int coinChange(vector<int>& coins, int amount) {
        int res = solve(coins, amount, 0);
        return res >= INT_MAX ? -1 : res;
    }
};

// Approach 2: memoization
// T.C:(0x amount)

class Solution {
public:
// T.C:O(amount×n)​
    vector<int> dp;
    int solve(vector<int>& coins, int amount) {
        if (amount == 0) {
            return 0;
        }
        if (amount < 0) {
            return INT_MAX;
        }

        if (dp[amount] != -1) {
            return dp[amount];
        }

        int ans = INT_MAX;
        for (int i = 0; i < coins.size(); i++) {
            int res = solve(coins, amount - coins[i]);

            if (res != INT_MAX) {
                ans = min(ans, res + 1);
            }
        }
        return dp[amount] = ans;
    }
    int coinChange(vector<int>& coins, int amount) {
        dp.resize(amount + 1, -1);
        int res = solve(coins, amount);
        return res >= INT_MAX ? -1 : res;
    }
};

//Approach 3:Bottom up
// T.C:0(amount*n)


class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<long long > dp(amount + 1, INT_MAX);//we dont know how many coins are req at start
        dp[0] = 0;//0 coins to make 0

        for (int i= 1; i <= amount; i++) {
            for (int c : coins) {
                int prev = i - c;//if we can make this coin value from any prevone
                if (prev >= 0 && dp[prev] != INT_MAX) {
                    dp[i] = min(dp[i], dp[prev] + 1);
                }
            }
        }
        return dp[amount]==INT_MAX?-1:dp[amount];
    }
};
