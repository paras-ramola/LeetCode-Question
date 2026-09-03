//============================================================
//  PROBLEM SUMMARY
//============================================================
//
//  Given a tree of n nodes, find all roots such that the
//  resulting tree has MINIMUM HEIGHT.
//  These roots are called "Minimum Height Tree (MHT) roots".
//
//  Return all such root nodes.
//
//============================================================
//  INTUITION
//============================================================
//
//  Key Observation:
//    Leaf nodes (degree = 1) are always the WORST roots.
//    They are farthest from the center → give maximum height.
//
//  Example 1:  1 - 2 - 3
//    height(1) = 2,  height(3) = 2,  height(2) = 1
//    Answer: {2}  ← central node
//
//  Example 2:  1 - 2 - 3 - 4
//    height(1) = 3,  height(4) = 3
//    height(2) = 2,  height(3) = 2
//    Answer: {2, 3}  ← two central nodes
//
//  INSIGHT:
//    Answer is always the CENTER of the tree.
//    Center = at most 2 nodes (never more).
//
//============================================================
//  APPROACH — Topological Sort (Leaf Trimming)
//============================================================
//
//  Think of it like peeling an onion from outside inward:
//
//    Round 1: remove all current leaf nodes (degree == 1)
//    Round 2: new leaves appear → remove them too
//    Round 3: repeat...
//    STOP   : when 2 or fewer nodes remain → those are the answer
//
//  Why stop at 2?
//    A tree's center is always 1 or 2 nodes.
//    If we remove beyond that, we overshoot the center.
//
//  This is exactly Topological Sort using indegree:
//    • In an undirected tree, degree == 1 means leaf.
//    • After removing a leaf, its neighbor's degree drops by 1.
//    • If neighbor's degree becomes 1 → it's the new leaf.
//
//============================================================
//  COMPLEXITY
//============================================================
//
//  TIME  → O(V + E)
//    Every node and edge is processed at most once.
//
//  SPACE → O(V + E)
//    Adjacency list  → O(V + E)
//    inDeg array     → O(V)
//    BFS queue       → O(V)
//
//============================================================
//  CODE
//============================================================

class Solution {
public:

    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {

        // Edge case: single node → it is its own root
        if (n == 1) return {0};

        // ── Step 1: Build adjacency list + degree array ───────────

        vector<vector<int>> adj(n);
        vector<int> degree(n, 0);

        for (auto& edge : edges) {
            int a = edge[0], b = edge[1];
            adj[a].push_back(b);
            adj[b].push_back(a);
            degree[a]++;
            degree[b]++;
        }

        // ── Step 2: Push all initial leaf nodes into queue ────────
        // Leaf node = degree of 1 in an undirected tree

        queue<int> q;
        for (int i = 0; i < n; i++)
            if (degree[i] == 1)
                q.push(i);

        // ── Step 3: Trim leaves layer by layer ───────────────────
        // Stop when 2 or fewer nodes remain (those are the centers)

        while (n > 2) {

            int leafCount = q.size(); // all current leaves this round
            n -= leafCount;           // remove them from remaining count

            while (leafCount--) {
                int u = q.front();
                q.pop();

                // For each neighbor of this leaf:
                // reduce its degree (as if leaf is removed)
                // if neighbor becomes a leaf → add to next round
                for (int v : adj[u]) {
                    degree[v]--;
                    if (degree[v] == 1)
                        q.push(v);
                }
            }
        }

        // ── Step 4: Remaining nodes in queue = MHT roots ─────────

        vector<int> result;
        while (!q.empty()) {
            result.push_back(q.front());
            q.pop();
        }

        return result;
    }
};
