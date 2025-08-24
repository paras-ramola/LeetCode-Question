// Approach 1.Reccursion
// T.C: 0(2 ^ N) ,at every index two choices->take or skip

class Solution {
public:
    int solve(int i, vector<int>& nums, int prevIdx) {

        if (i >= nums.size()) // out of bounds
            return 0;

        // Option 1: skip the curr elment:no elment is added:->'prev' remains same
        int skip = solve(i + 1, nums, prevIdx);

        // Option 2: Take the curr element if it's greater than 'previous'
        int take = 0; // do we take curr elment
        if (prevIdx==-1||nums[i] > nums[prevIdx) {
            // Add curr elment +1 (nums[i]), and move to next elment,  'prev' becomes  curr 'i'
            take = 1 + solve(i + 1, nums, i);
        }

        return max(skip, take);
    }
    int lengthOfLIS(vector<int>& nums) {

        int n = nums.size();

        if (n == 1)
            return 1; //only 1 elment

        return solve(0, nums, INT_MIN);
    }
};

//Approach 2:Memoization
//T.C:  0(N^ 2)-> n+1->currIdx,n+1->prevIdx=>total states to store
class Solution {
public:
    // RECCURSION+MEMOIZATION

    int solve(int i, int prevIdx, vector<int>& nums, vector<vector<int>>& dp) {
        if (i >= nums.size())
            return 0;

//if already computed return the result
        if (prevIdx != -1 && dp[i][prevIdx] != -1) {
            return dp[i][prevIdx];
        }

//skip curr->prevIdx remains same
        int skip = solve(i + 1, prevIdx, nums, dp);

        int take = 0;
        // Can take current pair only if it is increasing the subseq
        if (prevIdx == -1 || nums[i] > nums[prevIdx]) {
            take = 1 + solve(i + 1, i, nums, dp);//elment added ->prevIdx changes(prevIdx=i)
        }

        if (prevIdx != -1) {
            dp[i][prevIdx] = max(skip, take);
        }
//if prevIdx=-1 we can't store in arr->dp[i][-1] so return it 
        return max(skip, take);
    }
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();

//make an dp of [n+1][n+1]=-1
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

        return solve(0, -1, nums, dp);
    }
};

//Approach 3:Bottom-UP
//T.C:0(N^2)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();

        // State Define: dp[i] = length of LIS ending at index i
        vector<int> dp(n, 1);

        int LIS = 1; // At least 1 element is always in the LIS

        for (int i = 1; i < n; i++) {
            // Check all previous elements before index i
            for (int j = 0; j < i; j++) {
                // if a prev elment at 'j' in less than curr elment at'i'
                if (nums[j] < nums[i]) {
                    // lis at idx 'i' becomes max(Lis[i]'s idx,lis[j]'s idx+1(curr idx))
                    dp[i] = max(dp[i], dp[j] + 1);
                                   // If  adding nums[i]  extend the increasing subseq ending at nums[j]
                }
                LIS = max(LIS, dp[i]);
            }
        }

        return LIS;
    }
};

//Approach 4;Patience Sorting
//T.C: 0(N *log(N))
