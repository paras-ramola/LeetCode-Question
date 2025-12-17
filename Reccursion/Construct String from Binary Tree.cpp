// Approach 1: 
// T.C:0(n)

class Solution {
public:

    string tree2str(TreeNode* root) {

        // If tree is empty, return empty string
        if (root == NULL) {
            return "";
        }

        // If no left and no right child -> just return its value without any brackets
        if (root->left == NULL && root->right == NULL) {
            return to_string(root->val);
        }

        // Recursively convert left subtree into string
        string left = tree2str(root->left);

        // Recursively convert right subtree into string
        string right = tree2str(root->right);

        // Case 1:
        // Left child is missing BUT right child exists
        // We MUST add empty () to show left child is absent
        if (root->left == NULL) {
            return to_string(root->val) + "()" + "(" + right + ")";
        }

        // Case 2:
        // Right child is missing but left child exists
        // No need to add empty () here
        if (root->right == NULL) {
            return to_string(root->val) + "(" + left + ")";
        }

        // Case 3:
        // Both left and right children exist
        // Add both inside parentheses
        return to_string(root->val) + "(" + left + ")" + "(" + right + ")";
    }
};


// Approach 2:(My  Approach ->BRUTE FORCE)

class Solution {
public:
    
    // Preorder traversal to build the string
    void preorder(TreeNode* root, string& res) {

        // If node is NULL, it represents a missing child
        if (root == NULL) {

            // If last added was already "()", remove it (unnecessary)
            if (res.size() >= 2 && res.substr(res.size() - 2) == "()") {
                res.pop_back();
                res.pop_back();
                return;
            }

            // Otherwise, add empty parentheses
            res += "()";
            return;
        }

        // If this is the first (root) node, just add its value
        if (res.size() == 0) {
            res += to_string(root->val);
        } 
        // For all other nodes, wrap value in parentheses
        else {
            res += '(';
            res += to_string(root->val);
        }

        // Visit left child
        preorder(root->left, res);

        // Visit right child
        preorder(root->right, res);

        // Remove unnecessary empty parentheses at the end
        if (res.size() >= 2 && res.substr(res.size() - 2) == "()") {
            res.pop_back();
            res.pop_back();
        }

        // Close the current node's parentheses
        res += ')';
    }

    string tree2str(TreeNode* root) {

        string res = "";

        // Empty tree → empty string
        if (root == NULL)
            return res;

        // Start preorder traversal
        preorder(root, res);

        // Remove extra closing ')' for root
        res.pop_back();

        return res;
    }
};

