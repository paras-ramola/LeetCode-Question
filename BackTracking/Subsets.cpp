// approach 1: Reccusion+ backtracking
// T.C:0(2^n)


class Solution {
public:
    int n;  // Size of input array
    vector<vector<int>> ans;  // Stores all subsets

    // Recursive function to generate all subsets using backtracking
    void solve(vector<int>& nums, vector<int>& curr, int idx) {
        // Add the current subset to the answer
        ans.push_back(curr);

        // Loop through remaining elements starting from idx
        for (int i = idx; i < n; i++) {
            // Include nums[i] in the current subset
            curr.push_back(nums[i]);

            // Recur for the next elements
            solve(nums, curr, i + 1);

            // Backtrack: remove the last element before the next iteration
            curr.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        n = nums.size();           // Store the size of input
        vector<int> temp;          // Temporary vector to build subsets
        solve(nums, temp, 0);      // Start recursion from index 0
        return ans;                // Return all generated subsets
    }
};



// appraoch 2: Reccursion +backtracking
// TAKE IT OR LEAVE IT

class Solution {
public:
//T.C:0(2^n)
    void solve(const vector<int>& nums, vector<vector<int>>& ans,
               vector<int>& temp, int i) {
        if (i == nums.size()) {
            ans.push_back(temp);
            return;
        }

        // Exclude the current element
        solve(nums, ans, temp, i + 1);

        // Include the current element
        temp.push_back(nums[i]);
        solve(nums, ans, temp, i + 1);

        // Backtrack to remove the last element before returning
        temp.pop_back();
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> temp;
        solve(nums, ans, temp, 0);
        return ans;
    }
};

// approach 3:ITERATAIVE
// T.C: 0(n* 2^n)
// Copying a subset of max size n takes O(n).
// Space Complexity: O(n* 2^n) for storing all subsets.


class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;          // To store all subsets
        vector<int> empty;                // Start with an empty subset
        ans.push_back(empty);             // Add the empty subset initially

        // Iterate through each number in the input array
        for(int num : nums) {
            int n = ans.size();           // Current number of subsets
            // (We need to know this because we'll be adding new subsets to ans during iteration)
            
            // **For each existing subset, create a new subset by adding the curr number**
            for(int i = 0; i < n; i++) {
                vector<int> output = ans[i]; // Copy the current subset
                output.push_back(num);       // Add the current number
                ans.push_back(output);       // Add the new subset to ans
            }
        }

        return ans; // Return all generated subsets
    }
};

