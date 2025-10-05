//Approach 1:DSU
//T.C: O((E + Q) log(E + Q))
// Sorting edges	O(E log E) , Sorting queries	O(Q log Q)
// Union-Find operations (amortized)	O((E + Q) * α(N))


class Solution {
public:
    vector<int> rank;
    vector<int> parent;

    // ---------- DSU: Find with path compression ----------
    int find(int x) {
        if (x == parent[x])
            return x;
        return parent[x] = find(parent[x]); // Path compression
    }

    // ---------- DSU: Union by rank ----------
    void Union(int x, int y) {
        int parent_x = find(x);
        int parent_y = find(y);

        if (parent_x == parent_y)
            return; // already in same set

        // attach smaller rank tree under larger one
        if (rank[parent_x] > rank[parent_y]) {
            parent[parent_y] = parent_x;
        } else if (rank[parent_x] < rank[parent_y]) {
            parent[parent_x] = parent_y;
        } else {
            parent[parent_x] = parent_y;
            rank[parent_y]++;
        }
    }

    // ---------- Main function ----------
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        // initialize DSU
        rank.resize(n, 0);
        parent.resize(n);
        for (int i = 0; i < n; i++)
            parent[i] = i;

        int qSize = queries.size();

        // store original query index to restore answer order later
        for (int i = 0; i < qSize; i++)
            queries[i].push_back(i);

        // sort edges and queries by distance limit
        auto cmp = [&](vector<int>& a, vector<int>& b) { return a[2] < b[2]; };
        sort(edgeList.begin(), edgeList.end(), cmp);
        sort(queries.begin(), queries.end(), cmp);

        vector<bool> ans(qSize, false);
        int pt = 0; // pointer for edges

        // process each query
        for (int i = 0; i < qSize; i++) {
            int start = queries[i][0];
            int end = queries[i][1];
            int limit = queries[i][2];
            int idx = queries[i][3]; // original index

            // union all edges with weight < current limit
            while (pt < edgeList.size() && edgeList[pt][2] < limit) {
                Union(edgeList[pt][0], edgeList[pt][1]);
                pt++;
            }

            // check if start and end are connected-
            if (find(start) == find(end))
                ans[idx] = true;
        }

        return ans;
    }
};
