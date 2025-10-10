//Approach 1:dijkastra

// T.C: O( E logV )

// Each edge is relaxed at most once.
// Each push/pop operation in the priority queue takes 𝑂(log𝑉)
// There can be up to 𝑂(𝐸) pushes/pops.

class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges,
                          vector<double>& succProb,
                          int start_node, int end_node) {
        // Step 1: Build adjacency list (undirected graph)
        unordered_map<int, vector<pair<int, double>>> adj;
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            double prob = succProb[i];
            adj[u].push_back({v, prob});
            adj[v].push_back({u, prob});
        }

        // Step 2: Probability of reaching each node (initially 0)
        vector<double> probability(n, 0.0);
        probability[start_node] = 1.0;  // start node has probability 1

        // Step 3: Max-heap to always pick the path with the highest probability so far
        // pair = {probability, node}
        priority_queue<pair<double, int>> pq;
        pq.push({1.0, start_node});

        // Step 4: Modified Dijkstra’s algorithm
        while (!pq.empty()) {
            auto [currProb, currNode] = pq.top(); 
            pq.pop();

            // If we've already found a better probability for this node, skip it
            if (currProb < probability[currNode])
                continue;

            // Explore neighbors
            for (auto [nextNode, edgeProb] : adj[currNode]) {
                double newProb = currProb * edgeProb;
                // If this new path gives a higher success probability, update it
                if (newProb > probability[nextNode]) {
                    probability[nextNode] = newProb;
                    pq.push({newProb, nextNode});
                }
            }
        }

        // Step 5: Return the maximum probability to reach end_node
        return probability[end_node];
    }
};
