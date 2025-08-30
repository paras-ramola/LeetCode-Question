//Approach 1:Kadane's ALgo
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int i = 0;

        int maxSum = INT_MIN; // Stores the maximum subarray sum found so far
        int sum = 0;          // Stores the current subarray sum

        // Traverse through all elements
        while (i < n) {
            sum += nums[i];                // Add current element to running sum
            maxSum = max(maxSum, sum);     // check maximum everytime (safe for -ve sum)

            // If running sum becomes negative, reset it to 0
            // (because continuing with a negative sum will only reduce future sums)
            if (sum < 0) {
                sum = 0;
            }

            i++;
        }

        return maxSum; // Return the maximum subarray sum
    }
};
