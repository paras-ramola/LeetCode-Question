// Approach 1: DFS/BFS
class Solution {
public:
    vector<int> visited;

    // DFS to mark all stones in the same group (same row or column)
    void dfs(int idx, vector<vector<int>>& stones) {
        visited[idx] = true;
        int row = stones[idx][0];
        int col = stones[idx][1];

        // Check all other stones
        for (int i = 0; i < stones.size(); i++) {
            // If same row or same column and not visited, it's in the same group
            if ((stones[i][0] == row || stones[i][1] == col) && !visited[i]) {
                dfs(i, stones);
            }
        }
    }

    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        visited.resize(n, false); // visited[i] means stone i already in some group

        int group = 0; // number of connected groups
        for (int i = 0; i < n; i++) {
            // Found a new group (stone not visited yet)
            if (!visited[i]) {
                dfs(i, stones);
                group++;
            }
        }

        // Concept:
        // In each group of size k, we can remove (k - 1) stones and only 1 is left
        //so for k groups ->k stones are left 
        // So total removed = n - number_of_groups/stones left
        return n - group;
    }
};

// Approach 2:DSU

class Solution {
public:
    vector<int> parent; // Parent representative for each stone
    vector<int> rank;   // Helps keep DSU trees shallow

    // Find with path compression
    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union two sets by rank
    bool Union(int x, int y) {
        int x_parent = find(x);
        int y_parent = find(y);

        if (x_parent == y_parent) return true; // already in same set

        if (rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        } else if (rank[x_parent] < rank[y_parent]) {
            parent[x_parent] = y_parent;
        } else {
            parent[x_parent] = y_parent;
            rank[y_parent] += 1;
        }
        return false;
    }

    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        
        // DSU initialization
        rank.assign(n, 0);
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;

        // Connect stones that share a row or column
        for (int i = 0; i < n; i++) {
            int row = stones[i][0];
            int col = stones[i][1];
            for (int j = 0; j < n; j++) {
                if (stones[j][0] == row || stones[j][1] == col) {
                    Union(i, j);
                }
            }
        }

        // Count number of unique connected components/groups
        unordered_set<int> uniqueGroups;
        for (int i = 0; i < n; i++) {
            int i_parent=find(i);
            uniqueGroups.insert(i_parent); // a root/parent represent one group
        }

        // Stones removed = total stones - number of groups
        return n - (int)uniqueGroups.size();
    }
};

