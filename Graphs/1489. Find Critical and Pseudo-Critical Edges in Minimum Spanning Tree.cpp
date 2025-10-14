// Approach : MST(KRUSKAL's ALGO)
//T.C:O(E²)
// Sort edges	O(E log E)	
// Kruskal MST	O(E α(N)) (α = inverse Ackermann function, almost constant)	
// For each edge (2× MST calls)	=>0(E*E)


class Solution {
public:
    int N; // Number of nodes

    // ---------- Disjoint Set Union (Union-Find) ----------
    class DSU {
    public:
        vector<int> parent, rank;

        // Constructor: initialize DSU
        DSU(int n) {
            rank.assign(n, 0);
            parent.resize(n);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        // Find operation with path compression
        int find(int x) {
            if (parent[x] == x)
                return x;
            return parent[x] = find(parent[x]);
        }

        // Union by rank; returns true if merged successfully
        bool Union(int x, int y) {
            int parentX = find(x);
            int parentY = find(y);

            if (parentX == parentY)
                return false; // Already in same set

            if (rank[parentX] > rank[parentY]) {
                parent[parentY] = parentX;
            } else if (rank[parentX] < rank[parentY]) {
                parent[parentX] = parentY;
            } else {
                parent[parentY] = parentX;
                rank[parentX]++;
            }
            return true;
        }
    };

    // ---------- Kruskal's Algorithm ----------(used for finding MST Weiht)
    // skip: index of edge to skip
    // add: index of edge to forcibly include
    int kruskal(vector<vector<int>>& edges, int skip, int add) {
        DSU dsu(N);
        int totalWeight = 0;
        int edgesUsed = 0; // no of edges in a component/connected edge

        // If 'add' edge is provided, include it first
        if (add != -1) {
            int u = edges[add][0];
            int v = edges[add][1];
            int w = edges[add][2];
            if (dsu.Union(u, v)) {
                totalWeight += w;
                edgesUsed++;
            }
        }

        // Add remaining edges in increasing weight order
        for (int i = 0; i < edges.size(); i++) {
            if (i == skip)
                continue; // skip the given edge

            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];

            if (dsu.Union(u, v)) {
                totalWeight += w;
                edgesUsed++;
            }
        }

        // **EDGE CASE**
        // A MST must be connected->(N-1) total edges
        // if skipping of a edges causes it to be unconnected->that is a crtical
        // edge without that edge MST will never form->return INT_MAX (always > MST_WT)
        if (edgesUsed != N - 1)
            return INT_MAX;

        return totalWeight;
    }

    // ---------- Main Function ----------
    vector<vector<int>>
    findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        N = n;

        // Append original indices to edges for tracking
        for (int i = 0; i < edges.size(); i++) {
            edges[i].push_back(i);
        }

        // Sort edges by weight(1st step in Kruskal algo)
        sort(edges.begin(), edges.end(),
             [](vector<int>& a, vector<int>& b) { return a[2] < b[2]; });

        // Get MST weight using standard Kruskal
        int mstWeight = kruskal(edges, -1, -1);

        vector<int> critical, pseudo;

        // Check each edge for critical and pseudo-critical 
        for (int i = 0; i < edges.size(); i++) {
            int edgeIndex = edges[i][3];

            // Case 1: If removing this edge increases MST weight → Critical
            if (kruskal(edges, i, -1) > mstWeight) {
                critical.push_back(edgeIndex);
            }
            // Case 2: If including this edge keeps MST weight same → Pseudo-critical
            else if (kruskal(edges, -1, i) == mstWeight) {
                pseudo.push_back(edgeIndex);
            }
        }

        return {critical, pseudo};
    }
};
