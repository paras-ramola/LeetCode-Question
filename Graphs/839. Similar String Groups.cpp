//Approach 1:BFS/DFS
//T.C:0( (N^2) * k )

class Solution {
public:
    //  Two strings are "similar" if:
    // - They are of the same length, AND
    // - They differ in exactly 0 or 2 positions
    // (We don’t check if mismatched chars are different because they are
    // anagrams)
    bool isSimilar(string str1, string str2) {
        if (str1.size() != str2.size()) {
            return false;
        }

        int mismatchCount = 0;

        for (int i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i]) {
                mismatchCount++;
            }

            // More than 2 mismatches → cannot be made equal with one swap
            if (mismatchCount > 2) {
                return false;
            }
        }

        // Similar if strings are identical (0 mismatches)
        // or differ in exactly two positions
        return (mismatchCount == 0 || mismatchCount == 2);
    }

    //  BFS to explore all connected similar strings
    void bfs(unordered_map<int, list<int>>& graph, vector<int>& visited,
             int startNode) {
        queue<int> q;
        q.push(startNode);
        visited[startNode] = true;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            // Visit all directly connected similar strings
            for (int neighbor : graph[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    int numSimilarGroups(vector<string>& words) {
        int n = words.size();
        unordered_map<int, list<int>> graph; // adjacency list

        // Build graph — connect indices of similar strings
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isSimilar(
                        words[i],
                        words[j])) { // Form a graph of similar nodes(indexes)
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        int groupCount = 0;
        vector<int> visited(n, false);

        // Run BFS from every unvisited node → each BFS = one connected group
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                bfs(graph, visited, i);
                groupCount++;
            }
        }

        return groupCount;
    }
};

//Approach 2: DSU
//T.C:0( (N^2) * k )


class Solution {
public:
    vector<int> parent;
    vector<int> rank;

    //  Find operation with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    //  Union operation with union by rank
    void Union(int x, int y) {
        int parent_x = find(x);
        int parent_y = find(y);

        if (parent_x == parent_y)
            return; // Already in the same group

        // Attach the smaller tree to the root of the larger one
        if (rank[parent_x] > rank[parent_y]) {
            parent[parent_y] = parent_x;
        } else if (rank[parent_x] < rank[parent_y]) {
            parent[parent_x] = parent_y;
        } else {
            parent[parent_x] = parent_y;
            rank[parent_y]++;
        }
    }

    //  Two strings are "similar" if:
    // - They have the same length
    // - They differ in exactly 0 or 2 positions
    bool isSimilar(string str1, string str2) {
        if (str1.size() != str2.size())
            return false;

        int mismatchCount = 0;

        for (int i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i]) {
                mismatchCount++;
                if (mismatchCount > 2)
                    return false; // more than 2 mismatches → not similar
            }
        }

        return (mismatchCount == 0 || mismatchCount == 2);
    }



        int numSimilarGroups(vector<string> & strs) {

            int n = strs.size();
            rank.resize(n, 0);
            parent.resize(n);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }

            int groups = n; // in starting all are alone
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    // if both strings are similar and they dont lie in same
                    // group(same parent)
                    if (isSimilar(strs[i], strs[j]) && find(i) != find(j)) {
                        Union(i, j);
                        groups--; // two groups merged into one
                    }
                }
            }

            return groups;
        }
    };
