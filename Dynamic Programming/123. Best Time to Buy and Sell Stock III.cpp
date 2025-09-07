//we have options to choose day to buy and sell->reccursion
//Approach 1:Reccursion
//T.C:(02^n)

//Appraoch 2:Memoization+Reccursion
//T.C:(2*3*n)

class Solution {
public:
    vector<vector<vector<int>>> t;

    int solve(int day, int buy, int transactions, vector<int>& prices) {
        // Base case: no days left or already made 2 transactions
        if (day >= prices.size() || transactions >= 2) {
            return 0;
        }

        // If already computed, return from DP table
        if (t[day][buy][transactions] != -1) {
            return t[day][buy][transactions];
        }

        int priceToday = prices[day];
        int maxProfit = 0;

        if (buy) {
            // Option 1: Buy today
            int buyToday = -priceToday + solve(day + 1, 0, transactions, prices);
            // Option 2: Skip today
            int skipToday = solve(day + 1, buy, transactions, prices);
            maxProfit = max(buyToday, skipToday);

        } else {
            // Option 1: Sell today → transaction count increases
            int sellToday = priceToday + solve(day + 1, 1, transactions + 1, prices);
            // Option 2: Skip today
            int skipToday = solve(day + 1, buy, transactions, prices);
            maxProfit = max(sellToday, skipToday);
        }

        // Save and return result
        return t[day][buy][transactions] = maxProfit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // DP table: n days × 2 states × 3 transactions
        t.resize(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));

        int day=0;//start from 0th day
        int buy=1;//at start you have to buy a stock(1), to sell->0
        int transactions=0;//0 transactions intially

        return solve(0, 1, 0, prices);  
    }
};

//appraoch 3:Bottom Up
//T.C:0(n),S.c:0(n)
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

//State Definintion:t[i][0/1][k]=>maxm profit  we can earn if we start at ith day with  sell/buy and k transactions

        // DP table: dimensions = [day][buy][transactions]
        // day → 0..n
        // buy → 0 = holding stock (need to sell), 1 = free to buy
        // transactions → how many completed transactions so far (0..2)
        //
        // We allocate 3 for transactions to avoid out-of-bound  when we do "transactions+1" after a sell.
        vector<vector<vector<int>>> t(
            n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        // Fill table bottom-up (starting from last day → going backwards)
        for (int day = n - 1; day >= 0; day--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int transactions = 0; transactions < 2; transactions++) {
                    
                    int priceToday = prices[day];

                    if (buy) {
                        // We are free to buy:
                        // Option 1: Buy today (-price) → next state: "not free to buy"
                        int buyToday = -priceToday + t[day + 1][0][transactions];
                        
                        // Option 2: Skip buying → remain in buy state
                        int skipToday = t[day + 1][1][transactions];

                        // Take the better of buy vs skip
                        t[day][1][transactions] = max(buyToday, skipToday);

                    } else {
                        // We currently hold stock, so we can sell:
                        // Option 1: Sell today (+price) → increase completed transactions
                        int sellToday = priceToday + t[day + 1][1][transactions + 1];

                        // Option 2: Skip selling → remain in "holding" state
                        int skipToday = t[day + 1][0][transactions];

                        // Take the better of sell vs skip
                        t[day][0][transactions] = max(sellToday, skipToday);
                    }
                }
            }
        }

        // Final answer: start at day 0, free to buy (buy=1), with 0 completed transactions
        return t[0][1][0];
    }
};


//Bottom-Up +constant space
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // Since each day only depends on "day+1",
        // we only need 2 DP layers: current and next.
        // Dimensions: [buy][transactions]
        // buy → 0 or 1 &  transactions → 0..2
        vector<vector<int>> next(2, vector<int>(3, 0));
        vector<vector<int>> curr(2, vector<int>(3, 0));

        // Process days in reverse (from last day → first)
        for (int day = n - 1; day >= 0; day--) {
            for (int buy = 0; buy <= 1; buy++) {
                for (int transactions = 0; transactions <= 2; transactions++) {

                    int priceToday = prices[day];

                    if (buy) {
                        // We are free to buy:
                        // Option 1: Buy today (-price) → move to sell state
                        int buyToday = -priceToday + next[0][transactions];

                        // Option 2: Skip buying today → stay in buy state
                        int skipToday = next[1][transactions];

                        curr[1][transactions] = max(buyToday, skipToday);

                    } else {
                        // We currently hold stock:
                        // Option 1: Sell today (+price) → complete transaction (+1)
                        if (transactions < 2) {
                            int sellToday = priceToday + next[1][transactions + 1];
                            int skipToday = next[0][transactions];
                            curr[0][transactions] = max(sellToday, skipToday);
                        } else {
                            // Already completed 2 transactions → cannot sell anymore
                            curr[0][transactions] = next[0][transactions];
                        }
                    }
                }
            }
            // Move current state → next for next iteration
            next = curr;
        }

        // Answer = start at day 0, free to buy (buy=1), with 0 completed transactions
        return curr[1][0];
    }
};
