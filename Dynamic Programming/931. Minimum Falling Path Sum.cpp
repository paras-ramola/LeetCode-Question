//Approach:Greedy(taking max val from each row) ->Wrong appraoch

/*Appraoch 1: Reccursion
T.C:O(m * 3^n) =>Worst case, each cell (row, col) branches into 3 recursive calls.
 m=cols,n=Height of recursion tree(rows) .*/
class Solution {
public:
 
    int dfs(int row, int col, vector<vector<int>>& matrix, int n, int m) {

        // Base case: if we are at the last row, just return that cell's value
        if (row == n - 1) {
            return matrix[row][col];
        }

        // Current cell value
        int curr= matrix[row][col];

        // Initialize minimum path sum as very large
        int minSum = INT_MAX;

        // Try moving to the next row in 3 possible directions:
        // (down-left: col-1), (down: col), (down-right: col+1)
        for (int shift = -1; shift <= 1; shift++) {
            int newCol = col + shift;

            // Check if the new column is within bounds
            if (newCol >= 0 && newCol < m) {
                // Add current cell value + best(min) path from next row
                minSum = min(minSum, curr + dfs(row + 1, newCol, matrix, n, m));
            }
        }

        return minSum;  // Return the best path sum from this cell
    }

    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();    // number of rows
        int m = matrix[0].size(); // number of columns

        int minPathSum = INT_MAX;

        //  starting from every column in the first row & finding the best path down
        for (int i = 0; i < m; i++) {
            minPathSum = min(minPathSum, dfs(0, i, matrix, n, m));
        }

        return minPathSum;  // Final answer = minimum path sum
    }
};


//Approach 2: Reccursion+Memoization
// T.C:O(n * m)



class Solution {
public:
    

    int t[101][101];//static 2D array to memoize result for each cell
    int dfs(int row, int col, vector<vector<int>>& matrix, int n, int m) {

        if (row == n - 1) {
            return matrix[row][col];
        }

        if (t[row][col] != INT_MAX) {
            return t[row][col];
        }
        int sum = matrix[row][col];

        int minSum = INT_MAX;

        for (int shift = -1; shift <= 1; shift++) {
            if (row < n && col + shift < m && col + shift >= 0) {
                minSum =
                    min(minSum, sum + dfs(row + 1, col + shift, matrix, n, m));
            }
        }
        return t[row][col] = minSum;
    }
    int minFallingPathSum(vector<vector<int>>& matrix) {

        int n = matrix.size();    // row
        int m = matrix[0].size(); // col

        // dont set -1 because -1 can be a sum of possible path instead set some absurd val like INFINITY

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                t[i][j] = INT_MAX;
            }
        }

        int minPathSum = INT_MAX;
        for (int i = 0; i < m; i++) {
            minPathSum = min(minPathSum, dfs(0, i, matrix, n, m));
        }
        return minPathSum;
    }
};

/*Appraoch 3: Bottom-Up Dynamic Programming
     Time Complexity: O(n * m)
     Space Complexity: O(n * m)
*/



class Solution {
public:
  
    int minFallingPathSum(vector<vector<int>>& matrix) {

        int n = matrix.size();    // number of rows
        int m = matrix[0].size(); // number of columns

        // dp[row][col] will store the minimum falling path sum
        // ending at cell (row, col)
        vector<vector<int>> dp(n, vector<int>(m));

        // Base case:
        // For the first row, the min sum is just the value itself
        for (int col = 0; col < m; col++) {
            dp[0][col] = matrix[0][col];
        }

        // Build dp table row by row
        for (int row = 1; row < n; row++) {
            for (int col = 0; col < m; col++) {

                int curr = matrix[row][col]; // current cell value
                int minSum = INT_MAX; // track minimum among possible parents

                // Check all 3 possible moves from the previous row:
                //   (row-1, col-1), (row-1, col), (row-1, col+1)
                for (int shift = -1; shift <= 1; shift++) {
                    int prevCol = col + shift;

                    // Ensure prevCol is within bounds
                    if (prevCol >= 0 && prevCol < m) {
                        minSum = min(minSum, curr + dp[row - 1][prevCol]);
                    }
                }

                // Store best possible path sum at (row, col)
                dp[row][col] = minSum;
            }
        }

        // Answer = minimum value from the last row
        int minPathSum = INT_MAX;
        for (int col = 0; col < m; col++) {
            minPathSum = min(minPathSum, dp[n - 1][col]);
        }

        return minPathSum;
    }
};

