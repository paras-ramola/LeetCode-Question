//Appraoch 1:BFS
// T.C:0(N+M)
//Each node is visited once → O(n) 
// For each node, we iterate over all neighbors → total iterations over adjacency lists = O(2m) 

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        // Build adjacency list
        // Each pair: (neighbor, isOriginalDirection)
        // isOriginalDirection = 1 -> real road(given)
        // isOriginalDirection = 0 -> fake road
        unordered_map<int, list<pair<int, int>>> adjList;
        for (auto& road : connections) {
            int u = road[0];
            int v = road[1];

            adjList[u].push_back({v, 1}); // original road u->v
            adjList[v].push_back({u, 0}); // fake/virtual road v->u
        }

        vector<bool> visited(n, false); // track visited cities
        int reorderCnt = 0;             // number of roads to reverse

        queue<int> q;
        q.push(0); // start BFS from city 0

        while (!q.empty()) {
            int currCity = q.front();
            q.pop();
            visited[currCity] = true;

            // Explore all neighbors
            for (auto& [neigh, needsReorder] : adjList[currCity]) {
                if (!visited[neigh]) {
                    if (needsReorder ==
                        1) { // road goes away from 0, needs reversal
                        reorderCnt++;
                    }
                    q.push(neigh);
                }
            }
        }

        return reorderCnt;
    }
};

//Appraoch 2:DFS

class Solution {
public:
    int reorderCnt = 0;
    void dfs(unordered_map<int, list<pair<int, int>>>& adjList,
             vector<bool>& visited, int currCity) {
        visited[currCity] = true;
        for (auto& [neigh, needsReorder] : adjList[currCity]) {
            if (!visited[neigh]) {
                if (needsReorder ==
                    1) { // road goes away from 0, needs reversal
                    reorderCnt++;
                }
                dfs(adjList, visited, neigh);
            }
        }
    }
    int minReorder(int n, vector<vector<int>>& connections) {

        unordered_map<int, list<pair<int, int>>> adjList;
        for (auto& road : connections) {
            int u = road[0];
            int v = road[1];

            adjList[u].push_back({v, 1}); // original road u->v
            adjList[v].push_back({u, 0}); // fake/virtual road v->u
        }

        vector<bool> visited(n, false); // track visited cities
        dfs(adjList, visited, 0);

        return reorderCnt;
    }
};

