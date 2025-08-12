//Approach 1:BFS

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source,
                   int destination) {

        unordered_map<int, list<int>> adj;

        // Build adjacency list
        for (auto e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> visited(n, false);
        visited[source] = true;

        queue<int> q;
        q.push(source);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            // If we reached the destination, path exists
            if (node == destination) {
                return true;
            }

            // Explore all unvisited neighbors
            for (auto neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        return false;
    }
};


//Approach 2:DFS
class Solution {
public:
    bool solve(int src, int dest, unordered_map<int, list<int>> &adj,
               vector<int> &visited) {
        // If we reach the destination, path exists
        if (src == dest)
            return true;

        visited[src] = true;

        // Explore all unvisited neighbors
        for (auto neighbor : adj[src]) {
            if (!visited[neighbor]) {
                if (solve(neighbor, dest, adj, visited)) {
                    return true; // Found a path
                }
            }
        }
        return false; // No path from this branch
    }

    bool validPath(int n, vector<vector<int>>& edges, int source,
                   int destination) {
        unordered_map<int, list<int>> adj;

        // Build adjacency list
        for (auto e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> visited(n, false);

        return solve(source, destination, adj, visited);
    }
};
