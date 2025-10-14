// Approach 1:
// T.C: 0(V*V)


class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        // Adjacency list using unordered_set for O(1) lookup
        unordered_map<int, unordered_set<int>> adj;

        for (auto road : roads) {
            int cityA = road[0];
            int cityB = road[1];
            adj[cityA].insert(cityB);
            adj[cityB].insert(cityA);
        }

        int maxRank = 0;

        // Compare every pair of cities
        for (int city1 = 0; city1 < n; city1++) {
            for (int city2 = city1 + 1; city2 < n; city2++) {
                // Rank = total number of direct connections of both cities
                int city1_rank = adj[city1].size();
                int city2_rank = adj[city2].size();
                int total_rank = city1_rank + city2_rank;

                // If both cities are directly connected, subtract 1 to avoid
                // double counting
                if (adj[city1].find(city2) != adj[city1].end()) {
                    total_rank -= 1;
                }

                // Update the maximum network rank found so far
                maxRank = max(maxRank, total_rank);
            }
        }

        return maxRank;
    }
};


// Approach 2:



class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        // Create an adjacency matrix to mark direct connections between cities
        vector<vector<bool>> connected(n, vector<bool>(n, false));

        // Degree count of each city (number of directly connected roads)
        vector<int> degree(n, 0);

        // Build the connection data
        for (auto road : roads) {
            int cityA = road[0];
            int cityB = road[1];

            connected[cityA][cityB] = true;
            connected[cityB][cityA] = true;
            degree[cityA]++;
            degree[cityB]++;
        }

        int maxRank = 0;

        // Compare every pair of cities
        for (int city1 = 0; city1 < n; city1++) {
            for (int city2 = city1 + 1; city2 < n; city2++) {
                // Sum of roads connected to both cities
                int totalRank = degree[city1] + degree[city2];

                // Subtract one if they share a direct road (to avoid double-counting)
                if (connected[city1][city2]) {
                    totalRank -= 1;
                }

                // Track the maximum network rank found so far
                maxRank = max(maxRank, totalRank);
            }
        }

        return maxRank;
    }
};

