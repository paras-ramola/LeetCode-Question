//Approach 1: DFS

class Solution {
public:
    vector<int> ans;//to store final ans

    vector<int> dfs(int node, int parent, unordered_map<int, list<int>>& adj,
                    string& labels) {

        vector<int> labelsCnt(26, 0);// count array for labels in current node's subtree
       
      // Visit all children of the current node
        for (auto child : adj[node]) {
            if (child == parent)
                continue;
            
             // Recursively get label counts for the child's subtree
            vector<int> childLabelsCnt = dfs(child, node, adj, labels);

            // Add the child's label counts to the current node's label counts
            for (int i = 0; i < 26; i++) {
                labelsCnt[i] += childLabelsCnt[i];
            }
        }
 
        // Current node's label index (0 for 'a', 1 for 'b', etc.)
        int currLabel = labels[node] - 'a';

        // Count the current node's label in labelsCnt
        labelsCnt[currLabel] += 1;

        // ans[node] should include:
        // 1 (the current node itself, initialized earlier) +
        // number of other nodes in the subtree having the same label
        ans[node] += labelsCnt[currLabel];


        return labelsCnt; // Return updated label counts to parent
    }
    vector<int> countSubTrees(int n, vector<vector<int>>& edges,
                              string labels) {

             ans.resize(n, 0); // Start with 1 because each node matches itself

        // Build adjacency list for the tree
        unordered_map<int, list<int>> adj;
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Run DFS from root node (0), with -1 as parent (no parent)
        dfs(0, -1, adj, labels);
        return ans;
    }
};

//**Problem:Creating a vector for each Node->OPTIMIZE THIS
// Approach 2:


class Solution {
public:
    vector<int> ans;        // ans[i] = number of nodes in subtree of i (including i) 
                            // that have the same label as node i
    vector<int> labelsCnt;  // frequency of labels seen during DFS

    // DFS to process subtree rooted at `node`
    void dfs(int node, int parent, unordered_map<int, list<int>>& adj,
             string& labels) {

        // Convert current node's label to an index (e.g. 'a' -> 0, 'b' -> 1, etc.)
        int currLabelIdx = labels[node] - 'a';

        // Store count of this label before processing the subtree
        int before = labelsCnt[currLabelIdx];

        // Increase current node's label  cnt in the global count
        labelsCnt[currLabelIdx]++;

        // Traverse all children of this node
        for (auto child : adj[node]) {
            if (child == parent) continue; // skip going back to parent
            dfs(child, node, adj, labels); // process child subtree
        }

        // After DFS, the increase in label count = how many nodes  in this subtree (including current node) have the same label
        ans[node] = labelsCnt[currLabelIdx] - before;
    }

    vector<int> countSubTrees(int n, vector<vector<int>>& edges,
                              string labels) {
        ans.resize(n, 0);        // initialize result array
        labelsCnt.resize(26, 0); // frequency for all lowercase letters

        // Build adjacency list for the undirected tree
        unordered_map<int, list<int>> adj;
        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Start DFS from root (0) with no parent (-1)
        dfs(0, -1, adj, labels);

        return ans;
    }
};
