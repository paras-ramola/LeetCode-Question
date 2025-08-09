// Approach 1: DFS

class Solution {
public:

    unordered_map<int, list<int>> adj;
    vector<int> visited;

    // DFS to find the size of a connected component
    long long dfs(int x) {
        visited[x] = true; // Mark current node as visited
        long long componentSize = 1; // Count this node

        // Visit all unvisited neighbors
        for (auto i : adj[x]) {
            if (!visited[i]) {
                componentSize += dfs(i); // Add size of neighbor's component
            }
        }
        return componentSize; // Return total size of this connected component
    }

    long long countPairs(int n, vector<vector<int>>& edges) {
        visited.resize(n, false); // Initially, all nodes are unvisited

        // Build adjacency list from edges
        for (auto e : edges) {
            int x = e[0];
            int y = e[1];
            adj[x].push_back(y); // Undirected edge
            adj[y].push_back(x);
        }

        long long cnt = 0;              // Final count of unreachable pairs
        long long remainingNode = n;    // Number of nodes left to check

        // Find all connected components
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                long long compSize = dfs(i); // Size of curr  connected component

                // All nodes in this component are unreachable from  all nodes in the remaining graph
                remainingNode -= compSize;
                cnt += remainingNode * compSize;
            }
        }
        return cnt;
    }
};

//Approach 2:DSU

class Solution {
public:
    vector<int> parent;
    vector<int> rank;

    // Find with path compression
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]); // compress path
        }
        return parent[x];
    }

    // Union by rank (returns true if already connected)
    bool Union(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent)
            return true; // already in same component

        if (rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        } 
        else if (rank[x_parent] < rank[y_parent]) {
            parent[x_parent] = y_parent;
        } 
        else {
            parent[x_parent] = y_parent;
            rank[y_parent] += 1;
        }
        return false;
    }

    long long countPairs(int n, vector<vector<int>>& edges) {
        // Step 1: Initialize DSU
        rank.resize(n, 0);
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }

        // Step 2: Union all edges->group edges into diff component
        for (auto &e : edges) {
            Union(e[0], e[1]);
        }

        //Goal: to find size of each component ,to find unreachable pair

        // Step 3: Count size of each connected component
        unordered_map<int, int> size;
        for (int i = 0; i < n; i++) {
            int root = find(i); // if nodes have same parent ,they belong to a dingle component
            size[root]++;//store the size of that component
        }

        // Step 4: Calculate unreachable pairs
        long long cnt = 0;
        long long remNode = n; // remaining uncounted nodes

        for (auto &comp : size) {
            long long compSize = comp.second;//curr comp size
            remNode -= compSize;//all rem nodes after remving curr component and previously visited
            cnt += remNode * compSize; // each node in component × nodes in remaining graph
        }

        return cnt;
    }
};

