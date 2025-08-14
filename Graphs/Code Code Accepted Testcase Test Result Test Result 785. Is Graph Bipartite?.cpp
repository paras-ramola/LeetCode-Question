// Approach1 :DFS
class Solution {
public:
    // DFS helper to try coloring the graph
    bool dfs(int node, vector<vector<int>>& graph, vector<int>& color, int currColor) {
        
        // Step 1: Color the current node
        color[node] = currColor;

        // Step 2: Visit all adjacent nodes
        for (auto adjNode : graph[node]) {
            
            // Case 1: Adjacent node has the same color → Not bipartite
            if (color[adjNode] == color[node]) {
                return false;
            }

            // Case 2: Adjacent node is not colored yet (-1)
            if (color[adjNode] == -1) {
                // Assign the opposite color: if currColor=1 → newColor=0, if currColor=0 → newColor=1
                int newColor = 1 - currColor;

                // DFS into the adjacent node with the opposite color
                if (dfs(adjNode, graph, color, newColor) == false) {
                    return false; // If any recursive call finds a conflict, return false
                }
            }
        }

        // Step 3: If all adjacent nodes are fine, return true
        return true;
    }

    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size(); // Number of nodes in the graph

        // -1 means uncolored, 0 and 1 are the two colors (think "red" and "green")
        vector<int> color(n, -1);

        // The graph can be disconnected, so check each component
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) { // If this node is not yet colored
                // Start coloring this component with color 1 (arbitrary choice)
                if (dfs(i, graph, color, 1) == false) {
                    return false; // If any component is not bipartite, whole graph isn't
                }
            }
        }

        // If no conflicts were found, the graph is bipartite
        return true;
    }
};

//Approach 2:BFS


class Solution {
public:
    // BFS approach to check if the graph is bipartite
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();

        // color[i] = -1 means unvisited node
        // color[i] = 1 means red, color[i] = 0 means green
        vector<int> color(n, -1);

        queue<int> q;

        // Loop through all nodes because the graph can be disconnected
        for (int i = 0; i < n; i++) {
            // If the node is not yet colored, start BFS from it
            if (color[i] == -1) {
                q.push(i);
                color[i] = 1; // Assign red color to starting node

                // Standard BFS traversal
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    // Check all adjacent nodes
                    for (auto adjNode : graph[node]) {
                        // If adjacent node has the same color → Not bipartite
                        if (color[adjNode] == color[node]) {
                            return false;
                        }
                        // If adjacent node is not yet colored
                        if (color[adjNode] == -1) {
                            // Assign the opposite color to adjacent node
                            int newColor = 1 - color[node];
                            color[adjNode] = newColor;
                            q.push(adjNode);
                        }
                    }
                }
            }
        }

        // If no conflict in coloring → graph is bipartite
        return true;
    }
};
