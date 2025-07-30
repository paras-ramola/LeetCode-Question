/*Approach 1: RECCURSION+MEMO

*/

class Solution {
public:
    // RECCURSION+MEMO

    const int MOD = 1e9 + 7;

    typedef long long ll;

    // Memoization table: stores {maxProduct, minProduct} at each cell
    vector<vector<pair<ll, ll>>> t;

    pair<ll, ll> solve(int i, int j, int m, int n, vector<vector<int>>& grid) {

        // If we reach the bottom-right cell, return its value
        if (i == m - 1 && j == n - 1) {
            return t[i][j] = {grid[i][j], grid[i][j]};
        }

        // If already computed, return memoized result
        if (t[i][j] != make_pair(LLONG_MIN, LLONG_MAX)) {
            return t[i][j];
        }

        // Initialize max and min product values for the current cell
        ll maxVal = LLONG_MIN;
        ll minVal = LLONG_MAX;

        // Move Down if within bounds
        if (i + 1 < m) {
            auto [downMax, downMin] = solve(i + 1, j, m, n, grid);
            // Multiply current cell value with both min and max from the path to the left
            maxVal = max({maxVal, grid[i][j] * downMax, grid[i][j] * downMin});
            minVal = min({minVal, grid[i][j] * downMax, grid[i][j] * downMin});
        }

        // Move Right if within bounds
        if (j + 1 < n) {
            auto [rightMax, rightMin] = solve(i, j + 1, m, n, grid);
            // Multiply current cell value with both min and max from the path to the right
            maxVal = max({maxVal, grid[i][j] * rightMax, grid[i][j] * rightMin});
            minVal = min({minVal, grid[i][j] * rightMax, grid[i][j] * rightMin});
        }

        return t[i][j] = {maxVal, minVal};
    }

    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Initialize memoization table with {LLONG_MIN, LLONG_MAX}
        t = vector<vector<pair<ll, ll>>>(
            m + 1, vector<pair<ll, ll>>(n + 1, {LLONG_MIN, LLONG_MAX}));
        //***can't use -1 to intialize as it can be an answer

        auto [maxProd, minProd] = solve(0, 0, m, n, grid);

        // If the max val  is -ve, return -1
        return maxProd < 0 ? -1 : maxProd % MOD;
    }
};
***************************************************************************************************************************************************************************


/*
2.APPRAOCH 2:    // BOTTOM-UP DP

  */

class Solution {
public:
    // BOTTOM-UP DP
    const int MOD = 1e9 + 7;
    typedef long long ll;

    int maxProductPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // STATE DEFINE:
        // t[i][j].first  = maximum product to reach cell (i, j)
        // t[i][j].second = minimum product to reach cell (i, j)
        vector<vector<pair<ll, ll>>> t(m, vector<pair<ll, ll>>(n));

        // Initialize starting point — only one way to be here
        t[0][0] = {grid[0][0], grid[0][0]};

        // Fill first column — only reachable from the top
        for (int row = 1; row < m; row++) {
            t[row][0].first = t[row - 1][0].first * grid[row][0];
            t[row][0].second = t[row - 1][0].second * grid[row][0];
        }

        // Fill first row — only reachable from the left
        for (int col = 1; col < n; col++) {
            t[0][col].first = t[0][col - 1].first * grid[0][col];
            t[0][col].second = t[0][col - 1].second * grid[0][col];
        }

        // Fill the rest of the table
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                ll upMax = t[i - 1][j].first;
                ll upMin = t[i - 1][j].second;
                ll leftMax = t[i][j - 1].first;
                ll leftMin = t[i][j - 1].second;

                // Current cell value
                ll val = grid[i][j];

                // Possible values reaching (i, j) from top or left
                ll maxVal = max(
                    {upMax * val, upMin * val, leftMax * val, leftMin * val});
                ll minVal = min(
                    {upMax * val, upMin * val, leftMax * val, leftMin * val});

                // Store max and min products at (i, j)
                t[i][j] = {maxVal, minVal};
            }
        }

        // Final cell (bottom-right corner)
        auto [maxProd, minProd] = t[m - 1][n - 1];

        // If result is -ive, return -1
        if (maxProd < 0)
            return -1;

        return maxProd % MOD;
    }
};
