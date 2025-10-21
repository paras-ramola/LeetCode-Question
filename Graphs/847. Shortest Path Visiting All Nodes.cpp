// Approach 1: BFS+ BITMASKING
// Time Complaexity:
// How many possible states?
// There are N nodes.
// For each node, the bitmask can have 2ⁿ different values (because each of N nodes can be either visited or not).
// So total possible states = N × 2ⁿ

// What happens for each state?
// For every state (node, mask): We look at all neighbors of that node.
// In the worst case, every node is connected to all other nodes → up to N neighbors.
// So, processing one state can take O(N) time.

// Total states = N × 2ⁿ
// Work per state = O(N)
// Therefore, total time = O(N × 2ⁿ × N) = O(2ⁿ × N²)


// shortes->BFS

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {

        int n = graph.size();

        if (n == 0 || n == 1) // if single node or no node
            return 0;

        // store {node,bitMask} for visited
        set<pair<int, int>> vis;

        queue<pair<int, int>> q;

        for (int i = 0; i < n; i++) {
            int bitMask = 1 << i;
            q.push({i, bitMask}); // find total path from all nodes
            vis.insert({i, bitMask});
        }

        int allNodesVis = (1 << n) - 1; // 1111->(2^n-1)
        int path = 0;

        // Perform multi-source BFS
        while (!q.empty()) {
            int N = q.size();
            path++;
            while (N--) {
                auto [u, u_mask] = q.front();
                q.pop();
                for (auto v : graph[u]) {
                    // Mark the curr neigh 'v' as vis. in the bitmask.
                    // 'u_mask' already has all previously visited nodes.
                    // So, we set the bit for 'v' (1 << v) and combine it with 'u_mask' using OR (|)
                    int v_mask = (1 << v) | u_mask;

                    if (v_mask == allNodesVis) { // If all nodes are visited,
                                                 // return the path length
                        return path;
                    }

                    if (vis.find({v, v_mask}) == vis.end()) {
                        q.push({v, v_mask});
                        vis.insert({v, v_mask});
                    }
                }
            }
        }

        return -1;
    }
};






/*
Why we need Bitmask for "Shortest Path Visiting All Nodes":

1. Problem:
   - We need to find the shortest path that visits ALL nodes.
   - BFS needs to track not just the current node, but also which nodes 
     have already been visited along this path.

2. Why 2D vector (isVisited[parent][child]) does NOT work:
   - If you only mark edges as visited:
       isVisited[u][v] = true
     you lose information about the **set of previously visited nodes**.
   - Example:
       Path 1: 0 -> 1 -> 2 -> 3  (visited nodes: {0,1,2})
       Path 2: 0 -> 4 -> 2 -> 3  (visited nodes: {0,2,4})
     - Both paths reach node 3 from node 2.
     - Using only isVisited[u][v], we would skip Path 2 because edge 2->3 is "visited".
     - ❌ This might skip the shortest valid path.

3. Why using string ("node_mask") approach is inefficient:
   - The  problem requires you to know which nodes have been visited so far, not just which edge (or pair) you’ve traveled.
🧩 Example:
Graph: 0 - 1 - 2
If you only store "0_1" and "1_2":
You know you’ve gone from 0→1 and 1→2

❌ But you don’t know whether node 0 is still “visited” when you’re at node 2. (You need this to decide when all nodes have been visited.)

That’s exactly what the bitmask does efficiently —
it remembers all visited nodes at once, not just your current edge.

4. Why Bitmask works:
   - Represent each visited node as a **bit** in an integer.
   - Example for 5 nodes: node 0 -> bit 0, node 1 -> bit 1, etc.
   - Bitmask stores **exact set of visited nodes efficiently**.
   - BFS can check if `(currentNode, bitmask)` state has been seen before.
   - This ensures correctness and keeps performance optimal.

*/
