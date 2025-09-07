//we have options to choose day to buy or sell -> reccursion

//Appraoch 1:Reccursion
//T.C:0(2^n)


//Appraoch 2:Memo+Reccusrion
//T.C:0(2*n)=0(n)
class Solution {
public:


/*Note:
1.
when you buy: you lose money =>-money
when you sell:you gain money=> money
2.If you buy today(1),you must sell the next day/upcoming days (0) 
*/


    // Memoization table: t[day][buy]
    // - day = index of the current day in prices[]
    // - buy = 1 if we are allowed to buy, 0 if we must sell
    vector<vector<int>> t;

    // Recursive function to calculate max profit
    int solve(int day, int buy, vector<int>& prices) {
        // Base case: if we've reached the end, no profit possible
        if (day >= prices.size()) {
            return 0;
        }

        // If already computed, return the stored result
        if (t[day][buy] != -1) {
            return t[day][buy];
        }

        int priceToday = prices[day];
        int maxProfit = 0;

        if (buy) {
            // Option 1: Buy stock today (-priceToday) and move to "sell" state
            int buyToday = -priceToday + solve(day + 1, 0, prices);

            // Option 2: Skip buying today, stay in "buy" state
            int skipToday = solve(day + 1, buy, prices);

            // Take the best of the two
            maxProfit = max(buyToday, skipToday);

        } else {
            // Option 1: Sell stock today (+priceToday) and move back to "buy" state
            int sellToday = priceToday + solve(day + 1, 1, prices);

            // Option 2: Skip selling today, stay in "sell" state
            int skipToday = solve(day + 1, buy, prices);

            // Take the best of the two
            maxProfit = max(sellToday, skipToday);
        }

        // Save result in DP table and return
        return t[day][buy] = maxProfit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // Only 2 states for buy (0 or 1) are actually needed
        t.resize(n + 1, vector<int>(2, -1));

        int day = 0;  // Start at first day
        int buy = 1;  // Must buy first (can’t sell without buying)

        return solve(day, buy, prices);
    }
};

//Appraoch 2:Bottom-Up



//1st Way
//State Defintion
/* t[i][1] = maximum profit we can earn starting from day i if we are allowed to buy.
t[i][0] = maximum profit we can earn starting from day i if we are currently holding stock and must sell.*/

//Note:Memory Limit: to remove the error use two dp(2,0) to store curr and next day or use two variable
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // DP table: t[day][buy]
        // - day = index of the day (0 … n)
        // - buy = 1 if we can buy, 0 if we must sell
        // Value stored = maximum profit achievable from 'day' till end
        vector<vector<int>> t(n + 1, vector<int>(2, 0));

        // Fill table backwards (from last day → day 0)
        for (int day = n - 1; day >= 0; day--) {
            for (int buy = 0; buy <= 1; buy++) {

                int priceToday = prices[day];

                if (buy) {
                    // Case 1: Buy today → we pay money, so subtract price
                    int buyToday = -priceToday + t[day + 1][0];

                    // Case 2: Skip buying today → move to next day still allowed to buy
                    int skipToday = t[day + 1][1];

                    // Pick whichever is more profitable
                    t[day][1] = max(buyToday, skipToday);

                } else {
                    // Case 1: Sell today → we earn money, so add price
                    int sellToday = priceToday + t[day + 1][1];

                    // Case 2: Skip selling today → move to next day still holding stock
                    int skipToday = t[day + 1][0];

                    // Pick whichever is more profitable
                    t[day][0] = max(sellToday, skipToday);
                }
            }
        }

        // Start on day 0, in "buy" state (since we don't have stock yet)
        return t[0][1];
    }
};

//2nd Way
//t[i]=>profit till ith day
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        // profit[i] = maximum profit achievable up to day i
        vector<int> profit(n + 1, 0);

        // Start from day 1 because we need at least 2 days to make a transaction
        for (int day = 1; day < n; day++) {
            // Two choices on each day:
            // 1. Do nothing → profit stays same as previous day
            // 2. Trade today=> Profit=Trade between yesterday and today →  (prices[day] - prices[day-1]) is the profit from this transaction
          // +prev_profit
            profit[day] = max( profit[day - 1],                       // skip trading today
                profit[day - 1] + (prices[day] - prices[day - 1]) // trade today
            );
        }

        // Maximum profit achievable up to the last day
        return profit[n - 1];
    }
};


