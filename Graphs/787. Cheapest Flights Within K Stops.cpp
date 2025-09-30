//Approach 1:BFS
// T.C: O(E⋅(k+1))
// E = flights.size() (number of edges)
// k = maximum number of stops allowed


class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst,
                          int k) {
        // build adjacency list: city -> (neighbor, cost)
        unordered_map<int, list<pair<int, int>>> adj;
        for (auto it : flights) {
            int city1 = it[0];
            int city2 = it[1];
            int cost = it[2];
            adj[city1].push_back({city2, cost});
        }

        // distance array, initialized to infinity
        vector<int> dist(n, INT_MAX);
        dist[src] = 0; // source city cost is 0

        // BFS queue: (city, cost so far)
        queue<pair<int, int>> q;
        q.push({src, 0});

        int lvl = 0; // number of stops used
        while (!q.empty() && lvl <= k) {
            int N = q.size(); // process all nodes at this level
            while (N--) {
                auto [u, u_cost] = q.front();
                q.pop();

                // check neighbors
                for (auto [v, v_cost] : adj[u]) {
                    // if cheaper route found, update and push
                    if (dist[v] > u_cost + v_cost) {
                        dist[v] = u_cost + v_cost;
                        q.push({v, u_cost + v_cost});
                        //v->cost to reach v from src(u_cost+v_cost)
                    }
                }
            }
            lvl++; // move to next level (one more stop)
        }

        // return answer, -1 if no route
        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};
