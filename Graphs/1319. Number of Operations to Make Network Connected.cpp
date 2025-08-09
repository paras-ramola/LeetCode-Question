// Appraoch 1: DSU (Disjoint Set Union) data structures


class Solution {
public:
    // 
    vector<int> parent; // Stores the parent (or representative) of each node
    vector<int> rank;   // Used to keep the tree flat (Union by rank)

    // Find function with path compression
    int find(int x) {
        // If 'x' is not its own parent, recursively find its parent
        // and apply path compression (make x point directly to the root/parent)
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union function to connect two nodes
    // Returns true if they were already connected, false otherwise
    bool Union(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y);

        // If both nodes have the same parent, they are already connected
        if (x_parent == y_parent) {
            return true; // Already connected
        }

        // Union by rank — attach smaller tree under the larger tree
        if (rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        } 
        else if (rank[x_parent] < rank[y_parent]) {
            parent[x_parent] = y_parent;
        } 
        else {
            // If ranks are equal, attach one under the other and increase rank
            parent[x_parent] = y_parent;
            rank[y_parent] += 1;
        }
        return false; // New connection was made
    }

    int makeConnected(int n, vector<vector<int>>& connections) {
        int cables = connections.size();

        // To connect 'n' computers, we need at least 'n-1' cables
        // If fewer cables are available, it's impossible
        if (cables < n - 1) {
            return -1;
        }

        // Initialize DSU
        rank.resize(n, 0);
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i; // Each node is its own parent initially
        }

        int components = n; // Initially, every computer is its own component

        // Process each cable connection
        for (auto cable : connections) {
            int x = cable[0];
            int y = cable[1];

            // If they are not already connected, merge them
            if (Union(x, y) != true) {
                components--; //  component count reduces after merging
            }
        }

        // To connect all components into one, we need (components - 1) extra cables
        return components - 1;
    }
};

//Approach 2: DFS

class Solution {
public:

    // Adjacency list to store the network graph
    unordered_map<int, list<int>> adj;
    vector<int> visited; // array to keep track of visited computers

    //  DFS to mark all computers in the curr connected component as visited
    void dfs(int x) {
        visited[x] = true;      // Mark curr computer as visited
        for (auto i : adj[x]) { // Go through all connected computers
            if (!visited[i]) {
                dfs(i); // Visit unvisited neighbors
            }
        }
    }

    int makeConnected(int n, vector<vector<int>>& connections) {
        int cables = connections.size();

        // Rule: To connect 'n' computers, need at least 'n-1' cables
        if (cables < n - 1) { // if less tha 'n-1' cable -> impossible
            return -1;
        }

        // all computers initially unvisited
        visited.resize(n, false);

        // Build the adjacency list from the given cable connections
        for (auto cable : connections) {
            int x = cable[0];
            int y = cable[1];

            adj[x].push_back(y); // Connect x → y
            adj[y].push_back(x); // Connect y → x (undirected)
        }

        // Dfs will mark all comp of a network visited
        // so no. of times we do dfs shows no. of disconnected component
        // to connect 'm' disconnected component we need 'm-1' cable

        int components = 0; // Count of disconnected groups of computers

        // Count how many disconnected components exist
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i);       // Visit all nodes in this component
                components++; // Found a new component
            }
        }

        // To connect all components into one, we need (components - 1) extra cables
        return components - 1;
    }
};
