// Approach 1:Topological sort(BFS)
//0( V + 26E ) => 0( V + E)


class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {

        // Build adjacency list and indegree count
        unordered_map<int, list<int>> adj;
        int n = colors.size();
        vector<int> inDegree(n, 0);

        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            adj[u].push_back(v);
            inDegree[v]++;
        }

        // Result variable: largest color count found
        int largest = 0;

        // Count of nodes processed in topological order
        int cntNode = 0;

        // colorVals[node][c] = max count of color 'c' in any path ending at
        // 'node'
        vector<vector<int>> colorVals(n, vector<int>(26, 0));

        // Queue for Kahn’s topological sort
        queue<int> q;

        // Start with all nodes having indegree 0
        for (int i = 0; i < n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
                int colorIdx = colors[i] - 'a';
                colorVals[i][colorIdx] = 1; // at least 1 of its own color
            }
        }

        // Process nodes in topological order
        while (!q.empty()) {
            int curr = q.front();
            int currColor = colors[curr] - 'a';
            q.pop();
            cntNode++;

            // Update answer with the max value of current node’s color
            largest = max(largest, colorVals[curr][currColor]);

            // Traverse neighbors
            for (auto next : adj[curr]) {
                int nextColor = colors[next] - 'a';

                // Update color counts for each possible color
                for (int i = 0; i < 26; i++) {
                    // Update the best count of each color at 'next':
                    // take the max between (already known best at 'next')
                    // and (best count at 'curr' + 1 if 'next' itself has this color)
                    colorVals[next][i] =
                        max(colorVals[next][i],
                            colorVals[curr][i] + (nextColor == i));
                }

                // Reduce indegree, and if it becomes 0, push into queue
                inDegree[next]--;
                if (inDegree[next] == 0) {
                    q.push(next);
                }
            }
        }

        // If not all nodes were processed, graph has a cycle → invalid
        if (cntNode != n) {
            return -1;
        }
        return largest;
    }
};
