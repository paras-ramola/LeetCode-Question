//Approach 1:Detecting cylce in a DAG using DFS
class Solution {
public:
    vector<bool> visited;   // marks nodes that have been fully processed
    vector<bool> inCurrentPath; // marks nodes currently in DFS path

    // DFS function to detect cycle starting from 'node'
    bool hasCycle(vector<vector<int>>& graph, int node) {
        visited[node] = true;        // mark node as visited
        inCurrentPath[node] = true;  // mark node as part of current DFS path

        for (int neighbor : graph[node]) {
            // if neighbor is unvisited and DFS from neighbor finds a cycle
            if (!visited[neighbor] && hasCycle(graph, neighbor)) {
                return true;
            }
            // if neighbor is already in the current DFS path → cycle detected
            else if (inCurrentPath[neighbor]) {
                return true;
            }
        }

        inCurrentPath[node] = false; // remove node from current DFS path
        return false;                // no cycle found from this node
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        visited.resize(n, false);
        inCurrentPath.resize(n, false);

        // Check for cycles starting from every node
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                hasCycle(graph, i);
            }
        }

        // Nodes not part of any cycle (not in any DFS path currently) are safe
        vector<int> safeNodes;
        for (int i = 0; i < n; i++) {
            if (!inCurrentPath[i]) {
                safeNodes.push_back(i);
            }
        }

        return safeNodes;
    }
};
