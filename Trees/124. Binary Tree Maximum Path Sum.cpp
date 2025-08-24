
// Approach 1:DFS


class Solution {
public:
    int maxVal = INT_MIN;  // Will store the final answer (maximum path sum)

    // Helper function: returns the maximum path sum that can be extended upwards
    int dfs(TreeNode* root) {

        // Base case: null node contributes 0
        if (root == NULL)
            return 0;

        // If it's a leaf node, update maxVal with its value and return its value
        if (root->left == NULL && root->right == NULL) {
            maxVal = max(maxVal, root->val);
            return root->val;
        }

        // Recursively calculate path sum from left and right subtrees
        int left = dfs(root->left);
        int right = dfs(root->right);

        // If left/right sum is negative, ignore it (take 0 instead),
        // because including a negative path would reduce the sum
        left = (left > 0 ? left : 0);
        right = (right > 0 ? right : 0);

        // Path through current root = node value + best path from left + best path from right
        int sum = root->val + left + right;

        // Update the global max if this path is the best so far
        maxVal = max(sum, maxVal);

        // Return the either of longest path(left or right) +curr Node val
        //cant return sum as it contains two child->path should be straight
        return max(left, right) + root->val;
    }

    int maxPathSum(TreeNode* root) {
        dfs(root);  // Run DFS to calculate max path
        return maxVal;  // Final answer
    }
};
