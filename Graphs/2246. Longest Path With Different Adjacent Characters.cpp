// Approach 1:DFS
class Solution {
public:
    int longest = 0;  // Global result: longest valid path found

    // DFS returns the longest valid path length *starting at node `u` and going downward*
    int dfs(int u, int parent, unordered_map<int, list<int>>& adj, string& s) {
        
        // Store the two longest downward paths from `u` that we can combine
        int best1 = 0; // longest
        int best2 = 0; // second longest

        // Visit all children (neighbors except parent)
        for (int v : adj[u]) {
            if (v == parent) continue;  // skip the edge back to parent

            // find the longest path in child
            int childLen = dfs(v, u, adj, s);

            // If same character as current node, cannot use this edge
            if (s[v] == s[u]) continue;

            // Update top two best(longest) child paths
            if (childLen > best1) {
                best2 = best1;
                best1 = childLen;
            } else if (childLen > best2) {
                best2 = childLen;
            }
        }

        //  path through curr node = best1 + best2 + 1 (including curr  itself)
        longest = max(longest, best1 + best2 + 1);

//cant return longest as path should be  a straight line(only one child)
        // Return the longest path upwards (only one child path can be continued)
        return best1 + 1;
    }

    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();

        // Build adjacency list for tree
        unordered_map<int, list<int>> adj;
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
            adj[i].push_back(parent[i]);
        }

        // Run DFS from root (0)
        dfs(0, -1, adj, s);

        return longest;
    }
};
