/*

Approach 1: Tarjan’s Algorithm for Bridge Finding
using: DFS()
T.C:O(V + E)

  */

class Solution {
public:
    int timer = 1; // Keeps track of the discovery time of each node (DFS order)

    vector<vector<int>>
        result; // Stores the final list of critical connections (bridges)

    // DFS function to explore the graph and detect bridges
    void dfs(int src, int parent, unordered_map<int, list<int>>& adj,
             vector<int>& tin, vector<int>& low, vector<bool>& visited) {

        visited[src] = true; // Mark the current node as visited

        // Initialize discovery time and low value for current node
        tin[src] = low[src] = timer++;

        // Traverse all neighbors of the current node
        for (auto neigh : adj[src]) {

            if (neigh == parent)
                continue; // Skip the edge leading back to the parent (important
                          // in undirected graphs)

            if (!visited[neigh]) {
                // If neighbor is not visited, do DFS on it
                dfs(neigh, src, adj, tin, low, visited);

                // After returning from DFS, check if the connection is a bridge
                // If the lowest node reachable from neigh is > the discovery time of src, 
                // it means there is no back edge(it means the adjnode we are connected to a node           
                //   came after parent node ,so if  parent node is removed we can't reach back to parent node 
                // or above through any adjacent node) — removing this edge  disconnects the graph
                if (low[neigh] > tin[src]) {
                    result.push_back(
                        {neigh, src}); // This is a critical connection
                }

                // Update the low value of the current node after visiting the  neighbor
                low[src] = min(low[src], low[neigh]);

            } else {
                // If neighbor is already visited and it's not parent,
                // it's a back edge — update the low value of the current node
                low[src] = min(low[src], low[neigh]);
            }
        }
    }

    vector<vector<int>> criticalConnections(int n,
                                            vector<vector<int>>& connections) {

        unordered_map<int, list<int>> adj; // Adjacency list to store the graph

        // Convert edge list to adjacency list
        for (auto i : connections) {
            adj[i[0]].push_back(i[1]);
            adj[i[1]].push_back(i[0]);
        }

        vector<int> tin(n); // tin[i] = discovery time of node i
        vector<int> low(n); // low[i] = lowest discovery time reachable from i  apart from parent node
        vector<bool> visited(n, false); // Tracks which nodes have been visited

        // Start DFS from node 0, with no parent (-1)
        dfs(0, -1, adj, tin, low, visited);

        return result; // Return the list of critical connections
    }
};
