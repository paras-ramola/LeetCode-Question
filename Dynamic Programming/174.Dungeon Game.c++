/* Approach 1: BRUTE FORCE

(i)Lineat Search:find a number within given constrain and check if it can reach to dest in minm intial health.

(ii)Binary Search(**Optimized*):use binary search to find the minm intial health
    T.C:O(log(H)* 2^(m+n)) ,H=4*1e7   (range of health:[1 - 4*1e7])
*/
class Solution {
public:
    // Approach: Binary Search
    //  to check if we can survive starting with `minHealth`
    bool canSurvive(int i, int j, int health, int m, int n, vector<vector<int>>& dungeon) {
        // If out of bounds, return false
        if (i >= m || j >= n) return false;

        // Update curr health with dungeon val at (i, j)
        health += dungeon[i][j];

        // If health drops to 0 or below, we die
        if (health <= 0) return false;

        // If we've reached the destination (bottom-right cell), we survived
        if (i == m - 1 && j == n - 1) return true;

        // Explore both right and down paths
        return canSurvive(i + 1, j, health, m, n, dungeon) ||
               canSurvive(i, j + 1, health, m, n, dungeon);
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();

        // Binary search range for health (worst-case high limit based on constraints)
        int left = 1;
        int right = 4 * 1e7;  // 200(m)*200(n)*1000(dun[i][j])
        int minHealth =  4 * 1e7;

        // Binary search to find the min valid initial health
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (canSurvive(0, 0, mid, m, n, dungeon)) {
                // If we can survive with 'mid', try to find smaller valid health
                minHealth = mid;
                right = mid - 1;
            } else {
                // Else, we need more initial health
                left = mid + 1;
            }
        }

        return minHealth;
    }
};
// ***********************************************************************************************************************

//Options->(right or down)->reccursion
//Appraoch : Reccursion
  //T.C: 0( 2^(m+n) ), m+n=max_Depth of reccursive tree ,2^=2 choices at each step(right or down)

class Solution {
public:
    int solve(int i, int j, int m, int n, vector<vector<int>>& dungeon) {
        // Base Case:  out of bounds, return a very large number => so it can be chosen
        if (i >= m || j >= n)
            return INT_MAX;

        // Base Case: If we've reached the bottom-right cell 
        if (i == m - 1 && j == n - 1) {
            // If the cell has a negative value (damage), return the health needed to survive it
            // (+1 to stay alive with at least 1 health)
            if (dungeon[i][j] < 0) {
                return abs(dungeon[i][j]) + 1;
            } else {
                // If it's positive or zero, only 1 health is needed to survive
                return 1;
                //**you can't return 0 => saying no health is req as 0 means hero DIES**
            }
        }

        // Recursive Calls: Try moving right and down
        int right = solve(i, j + 1, m, n, dungeon);  // Health required from right cell
        int down = solve(i + 1, j, m, n, dungeon);   // Health required from down cell

        // min health needed from the next step (right or down)
        int prevMinHealth = min(right, down);

        // calculate the health req at the curr cell to ensure survival in the next step
        int reqMinHealth = prevMinHealth - dungeon[i][j];

        // If required health is <= 0, we need only 1 health (extra health not needed)
        return reqMinHealth <= 0 ? 1 : reqMinHealth;
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();      
        int n = dungeon[0].size();  

        return solve(0, 0, m, n, dungeon); // Start from top-left cell
    }
};

// ***********************************************************************************************************************
// Appraoch :DYNAMIC PROGRAMMING
//Appraoch RECCURSION+MEMOIZATION
    //T.C: 0(m*n)

class Solution {
public:

    int t[200][200];//static 2D arr to memoize
    int solve(int i, int j, int m, int n, vector<vector<int>>& dungeon) {
        // Base Case:  out of bounds, return a very large number => so it can be chosen
        if (i >= m || j >= n)
            return INT_MAX;

    //if already computed return value
        if(t[i][j]!=-1){
            return t[i][j];
        }

        // Base Case: If we've reached the bottom-right cell 
        if (i == m - 1 && j == n - 1) {
            // If the cell has a negative value (damage), return the health needed to survive it
            // (+1 to stay alive with at least 1 health)
            if (dungeon[i][j] < 0) {
                return t[i][j]=abs(dungeon[i][j]) + 1;
            } else {
                // If it's positive or zero, only 1 health is needed to survive
                return t[i][j]=1;
                //**you can't return 0 => saying no health is req as 0 means hero DIES**
            }
        }

        // Recursive Calls: Try moving right and down
        int right = solve(i, j + 1, m, n, dungeon);  // Health required from right cell
        int down = solve(i + 1, j, m, n, dungeon);   // Health required from down cell

        // min health needed from the next step (right or down)
        int prevMinHealth = min(right, down);

        // calculate the health req at the curr cell to ensure survival in the next step
        int reqMinHealth = prevMinHealth - dungeon[i][j];

        // If required health is <= 0, we need only 1 health (extra health not needed)
        return t[i][j]=reqMinHealth <= 0 ? 1 : reqMinHealth;
    }

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();      
        int n = dungeon[0].size();  

        memset(t,-1,sizeof(t));//intialize t with -1

        return solve(0, 0, m, n, dungeon); // Start from top-left cell
    }
};
// ***********************************************************************************************************************
  // BOTTOM-UP DP approach
    // T.C: O(m * n), S.C: O(m * n)
class Solution {
public:

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();

        //t[i][j] = minimum health needed to reach (m-1, n-1) safely starting from cell (i, j)
        vector<vector<int>> t(m + 1, vector<int>(n + 1));

        // Fill the table from bottom-right to top-left
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                
                // Case 1: Destination cell (bottom-right)
                if (i == m - 1 && j == n - 1) {
                    // If the cell has a negative value, add that much extra health (+1 to stay alive with at least 1 health)
                    if (dungeon[i][j] < 0)
                        t[i][j] = 1 + abs(dungeon[i][j]);
                    else    // If it's positive or zero, only 1 health is needed to survive
                        t[i][j] = 1;
                } 
                else {
                    // Get min health needed from right and down cells
                    int right = (j + 1 >= n) ? INT_MAX : t[i][j + 1];
                    int down  = (i + 1 >= m) ? INT_MAX : t[i + 1][j];

                    // Min health required from next step
                    int nextMinHealth = min(right, down);

                    // Health needed at current cell
                    int reqMinHealth = nextMinHealth - dungeon[i][j];

                    // If health drops to 0 or below, player needs at least 1
                    t[i][j] = (reqMinHealth <= 0) ? 1 : reqMinHealth;
                }
            }
        }

        // return minimum initial health needed at starting cell
        return t[0][0];
    }
};
