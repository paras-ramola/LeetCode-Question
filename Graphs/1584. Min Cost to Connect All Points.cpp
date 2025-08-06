/*
Appraoch 1: Prism ALgo
T.c:O(n² log n)

*/

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {

        // Step 1: Build the adjacency list for a complete graph
        // Each node (point) is connected to every other node with an edge of Manhattan distance
        unordered_map<int, list<pair<int, int>>> adj;
        for (int i = 0; i < points.size(); i++) {
            for (int j = i + 1; j < points.size(); j++) {
                int x1 = points[i][0];
                int y1 = points[i][1];
                int x2 = points[j][0];
                int y2 = points[j][1];
                
                int dist = abs(x2 - x1) + abs(y2 - y1); // Manhattan distance

                // Add undirected edges between i and j
                adj[i].push_back({j, dist});
                adj[j].push_back({i, dist});
            }
        }

        // Step 2: Use Prim's Algorithm to find Minimum Spanning Tree (MST)

        // Min-heap: stores {weight, node} pairs; 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        minHeap.push({0, 0});//starts from node 0 with cost 0

        unordered_map<int, bool> visited; // To track visited nodes

        int minSum = 0; // Total cost of MST

        while (!minHeap.empty()) {
            auto [wt, node] = minHeap.top(); // Get the edge with the smallest weight
            minHeap.pop();

            if (visited[node]) // If node is already in MST, skip it
                continue;
            
            visited[node] = true;    // Mark node as included in MST
            minSum += wt;            // Add edge weight to total cost

            // Add all unvisited neighbors of this node to the min-heap
            for (auto& neigh : adj[node]) {
                int adjNode = neigh.first;
                int adjWeight = neigh.second;

                if (!visited[adjNode]) {
                    minHeap.push({adjWeight, adjNode});
                }
            }
        }

        return minSum; // Return total cost of connecting all points
    }
};


/*
Approach 2:Kruskal Algorithm
T.C:O(n² log n) 
  */
class Solution {
public:

    // Comparator to sort edges based on weight (3rd element of vector)
    static bool comp(const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2];
    }

    // Find function with path compression
    int find(int x, vector<int>& parent) {
        if (x != parent[x]) {
            parent[x] = find(parent[x], parent);
        }
        return parent[x];
    }

    // Union by rank, returns true if x and y are already connected
    bool Union(int x, int y, vector<int>& rank, vector<int>& parent) {
        int x_parent = find(x, parent);
        int y_parent = find(y, parent);

        if (x_parent == y_parent)
            return true; // Already in same set

        // Union by rank
        if (rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        } else if (rank[x_parent] < rank[y_parent]) {
            parent[x_parent] = y_parent;
        } else {//if rank of both are equal->make anyone parent of another
            parent[x_parent] = y_parent;//make y_parent parent of x
            rank[y_parent]++;
        }
        return false; // Union done
    }

    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();

        // Step 1: Create a list of all edges with their weights (Manhattan distance)
        vector<vector<int>> adj;// (u,v,w)
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                int dist = abs(x1 - x2) + abs(y1 - y2); // Manhattan distance
                adj.push_back({i, j, dist});
            }
        }

        // Step 2: Initialize Disjoint Set Union (DSU) structures
        vector<int> parent(n);
        vector<int> rank(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i; // each point is its own parent initially
        }

        // Step 3: Sort edges by weight (Kruskal's requirement)
        sort(adj.begin(), adj.end(), comp);

        // Step 4: Iterate over edges, add them if they connect disjoint sets
        int minSum = 0;
        for (auto& edge : adj) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            // If not already connected(different parents) , include the edge and union the sets
            if (!Union(u, v, rank, parent)) {
                minSum += weight;//add the weights of new edges
            }
        }

        return minSum;
    }
};
