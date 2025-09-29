//Approach 1: BFS
//T.C:O(n + m)
// BFS visits each node at most once → n nodes.
// For each node, we iterate over all neighbors → total iterations = sum of degrees = 2m (undirected edges).

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // Build adjacency list: node -> list of (neighbor, road score)
        unordered_map<int, list<pair<int, int>>> adjList;
        for (auto &road : roads) {
            int u = road[0];
            int v = road[1];
            int score = road[2];

            adjList[u].push_back({v, score});
            adjList[v].push_back({u, score}); // undirected graph
        }

        int minRoadScore = INT_MAX;            // Initialize minimum score
        vector<bool> visited(n + 1, false);    // Track visited nodes (1-indexed)

        // BFS queue: stores (current node, road score to reach it)
        queue<pair<int,int>> q;
        q.push({1, 0});  // Start BFS from node 1

        while (!q.empty()) {
            auto [currentNode, roadScore] = q.front();
            q.pop();
            visited[currentNode] = true;

            // Explore neighbors
            for (auto &[neighbor, neighborScore] : adjList[currentNode]) {
                if (!visited[neighbor]) {
                    q.push({neighbor, neighborScore});
                    minRoadScore = min(minRoadScore, neighborScore); // update min score
                }
            }
        }

        return minRoadScore;
    }
};

//Approach 2:DFS


class Solution {
public:
    int ans = INT_MAX;

    void findMinScore(unordered_map<int, list<pair<int, int>>>& path,
                      vector<bool> &vis, int city) {
        vis[city] = true;
        for (auto it : path[city]) {
            int v=it.first;
            ans = min(ans, it.second);
            if (!vis[v]) {
                findMinScore(path, vis, v);
            }
        }
    }
    int minScore(int n, vector<vector<int>>& roads) {
        unordered_map<int, list<pair<int, int>>> path;
        for (auto it : roads) {
            path[it[0]].push_back({it[1], it[2]});
            path[it[1]].push_back({it[0], it[2]});
        }
        vector<bool> vis(n + 1, false);
        findMinScore(path, vis, 1);
        return ans;
    }
};
