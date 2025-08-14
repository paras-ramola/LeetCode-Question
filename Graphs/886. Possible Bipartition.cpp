//Approach 1:dfs


class Solution {
public:
    vector<int> color; // Stores the color of each node: -1 = uncolored, 0 = green, 1 = red

    // DFS function to try coloring the graph and check for bipartiteness
    bool dfs(int node, unordered_map<int, list<int>>& adj, int currColor) {
        color[node] = currColor; // Assign the current node the given color

        // Traverse all neighbors of the current node
        for (auto i : adj[node]) {
            // If the neighbor has the same color as current → not bipartite
            if (color[i] == color[node]) {
                return false;
            }
            // If the neighbor is not yet colored, recursively color it
            else if (color[i] == -1) {
                int newColor = 1 - currColor; // Alternate between 0 and 1
                if (dfs(i, adj, newColor) == false) {
                    return false; // If any recursive call fails, return false
                }
            }
        }
        return true; // No conflicts found, bipartite check passes here
    }

    bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
        // Initially, no node is colored
        color.resize(n + 1, -1); // Use n+1 for 1-based indexing (nodes are from 1 to n)

        // Build adjacency list from dislikes
        unordered_map<int, list<int>> adj;
        for (auto i : dislikes) {
            adj[i[0]].push_back(i[1]); // Edge from i[0] → i[1]
            adj[i[1]].push_back(i[0]); // Edge from i[1] → i[0] (undirected graph)
        }

        // Try to color each uncolored node
        for (int i = 1; i <= n; i++) {
            if (color[i] == -1) { // If this node is not yet colored
                // Start DFS with color 1 (red)
                if (dfs(i, adj, 1) == false) {
                    return false; // Found a conflict → not bipartite
                }
            }
        }

        return true; // Successfully colored all components
    }
};

// Approach 2:BFS
