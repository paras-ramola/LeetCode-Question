//Approach 1:DFS

class Solution {
public:
    int dfs(int src, int parent, unordered_map<int, list<int>>& adj,
            vector<bool>& hasApple) {

        int total_time = 0;

        // Visit all children (neighbors except parent)
        for (auto child : adj[src]) {
            if (child == parent) continue;

            // Time required from this parent to child
            int time_from_child = dfs(child, src, adj, hasApple);

            // **If this child or its subtree has apples**,-> we need to go there (time_from child) +  go back up to parent(+2)
            if (time_from_child > 0 || hasApple[child]) {
                total_time += time_from_child + 2; // accumulate
            }
        }

        return total_time;
    }

    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        unordered_map<int, list<int>> adj;

        // Build adjacency list
        for (auto e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Run DFS from root (0, with no parent → -1)
        return dfs(0, -1, adj, hasApple);
    }
};
