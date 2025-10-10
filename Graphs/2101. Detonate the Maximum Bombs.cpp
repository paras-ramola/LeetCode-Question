//Approach 1:DFS


class Solution {
public:
    // DFS tocount how many bombs can be detonated from the curr bomb
    void dfs(unordered_map<int, list<int>>& adjList, vector<bool>& visited, int currBomb, int& count) {
        visited[currBomb] = true; 

        // explore all bombs that can be directly detonated from this bomb
        for (auto nextBomb : adjList[currBomb]) {
            if (!visited[nextBomb]) {
                count++;  // increase total count
                dfs(adjList, visited, nextBomb, count);  // continue chain reaction
            }
        }
    }

    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();

        unordered_map<int, list<int>> adjList;  // adjacency list to store which bomb can trigger which

        // Build the directed graph
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;  // skip same bomb

                int x1 = bombs[i][0], y1 = bombs[i][1], r1 = bombs[i][2];
                int x2 = bombs[j][0], y2 = bombs[j][1];

                // Calculate distance between bomb i and bomb j
                double distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
                //** try to avoid sqrt,pow() as they return double and cause point errors

                // If bomb j lies inside the blast radius of bomb i, add a directed edge
                if (distance <= r1) {
                    adjList[i].push_back(j);
                }
            }
        }

        int maxDetonated = 1;  // at least one bomb (the one we start from)

        // Try starting the chain reaction from each bomb
        for (int i = 0; i < n; i++) {
            vector<bool> visited(n, false);  // track visited bombs
            int count = 1;                   // count bombs detonated in this chain
            dfs(adjList, visited, i, count); 
            maxDetonated = max(maxDetonated, count);
        }

        return maxDetonated;
    }
};


//Aproach 2:BFS

class Solution {
public:
    // BFS to count how many bombs can be detonated starting from a given bomb
    void bfs(unordered_map<int, list<int>>& adjList, int startBomb, int& count, int n) {
        vector<bool> visited(n, false);
        queue<int> q;

        visited[startBomb] = true; // mark the starting bomb as visited
        q.push(startBomb);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            // Visit all bombs that can be triggered by current bomb
            for (auto nextBomb : adjList[curr]) {
                if (!visited[nextBomb]) {
                    visited[nextBomb] = true; // mark as visited when pushing
                    count++;
                    q.push(nextBomb);
                }
            }
        }
    }

    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        unordered_map<int, list<int>> adjList; // store directed edges

        // Build the graph
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;

                long long dx = bombs[j][0] - bombs[i][0];
                long long dy = bombs[j][1] - bombs[i][1];
                long long r1 = bombs[i][2];

                // compare squared distance to avoid using sqrt()
                if (dx * dx + dy * dy <= r1 * r1) {
                    adjList[i].push_back(j); // bomb i can detonate bomb j
                }
            }
        }

        int maxDetonated = 1; // at least one bomb can detonate (itself)

        // Try detonating from each bomb and see which gives max chain
        for (int i = 0; i < n; i++) {
            int count = 1; // start by detonating current bomb
            bfs(adjList, i, count, n);
            maxDetonated = max(maxDetonated, count);
        }

        return maxDetonated;
    }
};
