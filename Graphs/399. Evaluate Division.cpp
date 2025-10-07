// Approach 1:BDF/DFS
// T.C. = O(N + Q × (V + E))
// N = number of equations
// Q = number of queries
// V = nodes,E=edges

class Solution {
public:
    // DFS function to find the product value from 'curr' to 'end'
    double dfs(unordered_map<string, vector<pair<string, double>>>& adj,
               unordered_map<string, bool>& vis,
               string curr, string end, double prod) {
        
        vis[curr] = true; // mark current node as visited

        // base case: if we reach the target node, return the product so far
        if (curr == end) {
            return prod;
        }

        // explore all neighbors
        for (auto [v, val] : adj[curr]) {
            if (!vis[v]) {
                // multiply curr product with edge weight and continue DFS
                double result = dfs(adj, vis, v, end, prod * val);
                if (result != -1) {
                    return result; // if path found, return the result
                }
            }
        }

        return -1; // if no path found
    }

    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values,
                                vector<vector<string>>& queries) {

        // build adjacency list (graph)
        unordered_map<string, vector<pair<string, double>>> adj;
        for (int i = 0; i < equations.size(); i++) {
            string u = equations[i][0];
            string v = equations[i][1];
            double val = values[i];

            adj[u].push_back({v, val});       // u / v = val
            adj[v].push_back({u, 1.0 / val}); // v / u = 1 / val
        }

        vector<double> ans;

        // answer each query using DFS
        for (auto& q : queries) {
            string src = q[0];
            string end = q[1];

            // if either variable not present in graph
            if (adj.find(src) == adj.end() || adj.find(end) == adj.end()) {
                ans.push_back(-1.0);
                continue;
            }

            unordered_map<string, bool> vis; // visited map for each query
            double div = dfs(adj, vis, src, end, 1); // start DFS with product = 1
            ans.push_back(div);
        }

        return ans; // return answers for all queries
    }
};
