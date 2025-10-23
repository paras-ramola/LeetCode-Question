

// Approach 1:Map+ BFS on Routes
//T.C: 0(n*m^2)
//n => no of routes,m => no of stops
//adj:0(n*m) 
//BFS: routes iterate->0(n*m), for every route we are traversing all its stops
//=>0(n*m)*0(m)
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {

        // If source and target are same, no bus needed
        if (source == target) return 0;

        int n = routes.size();

        // Map each stop to all routes that pass through it
        unordered_map<int, vector<int>> adj; 
        for (int route = 0; route < n; route++) {
            for (auto& stop : routes[route]) {
                adj[stop].push_back(route);
            }
        }

        // To track which routes are already visited
        vector<bool> vis(n, false);

        queue<int> q;

        // Push all routes containing the source stop
        for (auto route : adj[source]) {
            q.push(route);
            vis[route] = true;
        }

        int bus = 0; // number of buses taken so far

        // BFS traversal over routes
        while (!q.empty()) {
            int N = q.size();
            bus++; // one more bus used

            // process all routes at current bus level
            while (N--) {
                int route = q.front();
                q.pop();

                // check all stops in this route
                for (auto stop : routes[route]) {
                    // If we reach target stop
                    if (stop == target) return bus;

                    // visit all other routes that share this stop
                    for (auto ind : adj[stop]) {
                        if (!vis[ind]) {
                            q.push(ind);
                            vis[ind] = true;
                        }
                    }
                }
            }
        }

        // If no route leads to target
        return -1;
    }
};

/
// Approach 2 — BFS on Stops (Instead of Routes)
 // Idea:
// Treat bus stops as graph nodes.
// If two stops belong to the same bus route, then they are connected — you can go from one to the other using that bus.
// You can ride one bus (traverse all stops in that route) in one BFS level.
// When you switch from one bus route to another, that counts as taking one more bus.

 // Algorithm:

// Build a map:For each stop, store all routes that include that stop (same as before).
// BFS starting from source stop:
// Use a queue to store stops.
// Keep track of how many buses (routes) have been used so far.
// For each stop, traverse all routes that include it.
// For each route, add all stops in that route to the queue.
// Mark routes as visited to avoid repeating the same route.
// Return the number of buses when you first reach the target stop.


class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;

        int n = routes.size();
        unordered_map<int, vector<int>> stopToRoutes;

        // Map: stop -> list of routes that pass through it
        for (int i = 0; i < n; i++) {
            for (int stop : routes[i]) {
                stopToRoutes[stop].push_back(i);
            }
        }

        queue<int> q; // stores stops
        unordered_set<int> visitedStops;
        vector<bool> visitedRoutes(n, false);

        q.push(source);
        visitedStops.insert(source);
        int buses = 0;

        // BFS over stops
        while (!q.empty()) {
            int size = q.size();
            buses++; // taking one more bus

            while (size--) {
                int stop = q.front();
                q.pop();

                // all routes passing through this stop
                for (int route : stopToRoutes[stop]) {
                    if (visitedRoutes[route]) continue;
                    visitedRoutes[route] = true;

                    // all stops in this route
                    for (int nextStop : routes[route]) {
                        if (nextStop == target) return buses;
                        if (!visitedStops.count(nextStop)) {
                            q.push(nextStop);
                            visitedStops.insert(nextStop);
                        }
                    }
                }
            }
        }

        return -1;
    }
};
