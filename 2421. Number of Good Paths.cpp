// Approach : DSU
//T.C:O(nlogn)
class Solution {
public:

    vector<int> rank;   // stores "rank" (approximate tree height) for DSU
    vector<int> parent; // parent array for DSU

    // DSU find with path compression
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // DSU union by rank
    void Union(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent) return; // already in same component

        if (rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        } else if (rank[y_parent] > rank[x_parent]) {
            parent[x_parent] = y_parent;
        } else {
            // same rank → attach arbitrarily and increase rank
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
    }

    // count number of "good pairs" inside one value group
    // input: list of parents of nodes with same value
    void findPairs(vector<int>& nodes_parent, int& res) {
        sort(nodes_parent.begin(), nodes_parent.end()); // group same parents together
        int i = 0, n = nodes_parent.size();

        while (i < n) {
            int cnt = 0;                  // how many nodes share this parent
            int curr_parent = nodes_parent[i];
            while (i < n && nodes_parent[i] == curr_parent) {
                cnt++;
                i++;
            }
            // each group contributes "cnt choose 2" good paths
            res += (cnt * (cnt - 1)) / 2;
        }
    }

    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        int n = vals.size();
        int result = n; // each node itself is a "good path" of length 0

        // initialize DSU
        rank.resize(n, 1);
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;

        // build adjacency list
        unordered_map<int, list<int>> adj;
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // group nodes by their value
        map<int, list<int>> val_to_nodes; // map keeps values sorted ascending
        for (int i = 0; i < n; i++) {
            val_to_nodes[vals[i]].push_back(i);
        }

        // track which nodes are "active" (already processed)
        vector<bool> is_active(n, false);

        // process values in increasing order
        for (auto& it : val_to_nodes) {
            list<int> nodes = it.second;

            // activate all nodes with this value
            for (int u : nodes) {
                for (int v : adj[u]) {
                    // if neighbor v is already active with <= current value,
                    // merge u and v into same DSU component
                    if (is_active[v]) {
                        Union(u, v);
                    }
                }
                is_active[u] = true;
            }

            // collect DSU parents of all nodes with this value
            vector<int> nodes_parent;
            for (int u : nodes) {
                nodes_parent.push_back(find(u));
            }

            // count good paths inside each connected component
            findPairs(nodes_parent, result);
        }

        return result;
    }
};
