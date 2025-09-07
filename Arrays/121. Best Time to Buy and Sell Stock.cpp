// Approach 1:Brute-Force
//T.C: 0(n*n)


//Approach 2:
//T.C;0(n)

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        int maxProfit = 0;          // stores the maximum profit found so far
        int bestBuy = prices[0];    // best (minimum) price to buy stock up to current day

        // Start from day 1 (since day 0 is the first buy day, you can’t sell then)
        for (int day = 1; day < n; day++) {

            // Check profit if we sell today (price today - best buy price so far)
            maxProfit = max(maxProfit, prices[day] - bestBuy);

            // Update the best buy price if today’s price is cheaper
            bestBuy = min(bestBuy, prices[day]);
        }
        return maxProfit;   // return the maximum profit possible
    }
};
