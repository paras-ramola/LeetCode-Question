// Approach 1:Dijkastra
// T.C:0(M* E log(v))  , M=no of time shortest path is called
class Graph {
public:
    int N;  // number of nodes
    unordered_map<int, vector<pair<int, int>>> adj; // adjacency list: node -> [(neighbor, weight)]

    // Constructor: build graph from given edges
    Graph(int n, vector<vector<int>>& edges) {
        N = n;
        for (auto vec : edges) {
            int u = vec[0];
            int v = vec[1];
            int cost = vec[2];
            adj[u].push_back({v, cost});
        }
    }

    // Add a single directed edge
    void addEdge(vector<int> edge) {
        int u = edge[0];
        int v = edge[1];
        int cost = edge[2];
        adj[u].push_back({v, cost});
    }

    // Find shortest path using Dijkstra’s algorithm
    int shortestPath(int node1, int node2) {
        vector<int> dist(N, INT_MAX); // distance array
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // start from node1
        dist[node1] = 0;
        pq.push({0, node1}); // {distance, node}

        while (!pq.empty()) {
            auto [u_cost, u] = pq.top(); // current node and its cost
            pq.pop();

            // If we already found a shorter path before, skip
            if (u_cost > dist[u]) continue;

            // Traverse all neighbors
            for (auto [v, v_cost] : adj[u]) {
                if (dist[v] > dist[u] + v_cost) {
                    dist[v] = dist[u] + v_cost;
                    pq.push({dist[v], v});
                }
            }
        }

        // If node2 is unreachable
        return dist[node2] == INT_MAX ? -1 : dist[node2];
    }
};

// Approach 2:Flyod Warshall 0(N^3)



class Graph {
public:
    int N;
    vector<vector<int>> adjMatrix;

    Graph(int n, vector<vector<int>>& edges) {
        N = n;
        adjMatrix = vector<vector<int>>(n, vector<int>(n, 1e9)); 

        for (auto& vec : edges) {
            int u = vec[0];
            int v = vec[1];
            int wt = vec[2];
            adjMatrix[u][v] = wt;
        }

        // Distance to itself = 0
        for (int i = 0; i < n; i++) {
            adjMatrix[i][i] = 0;
        }

        // Run Floyd–Warshall algorithm to precompute all-pairs shortest paths
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    adjMatrix[i][j] = min(adjMatrix[i][j], adjMatrix[i][k] + adjMatrix[k][j]);
                }
            }
        }
    }

    void addEdge(vector<int> edge) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];

        // Update all pairs that can be improved via this new edge
        for (int i = 0; i < N; i++) {          // loop over all source nodes
          for (int j = 0; j < N; j++) {      // loop over all destination nodes
        // Check if going from i → u → v → j is shorter  than the current known shortest path i → j
        adjMatrix[i][j] = min( adjMatrix[i][j],  adjMatrix[i][u] + wt + adjMatrix[v][j]);
    }
}


    int shortestPath(int node1, int node2) {
        return adjMatrix[node1][node2] == 1e9 ? -1 : adjMatrix[node1][node2];
    }
};

