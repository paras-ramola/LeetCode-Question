// Approach 1:DFS
// (using cycle Detection in a directed graph)
//T.C: 0(n) ->each node is preoccesed once  and each edge once 0(2N)


class Solution {
public:
    int longest = -1; // store length of longest cycle

    // DFS to detect cycle length
    void dfs(vector<int>& edges, vector<bool>& visited, vector<bool>& inPath,
             vector<int>& cnt, int node) {
        visited[node] = true; // mark current node visited
        inPath[node] = true;
        int nextNode = edges[node]; // get neighbor

        if (nextNode != -1) {
            if (!visited[nextNode]) {
                cnt[nextNode] = 1 + cnt[node];
                dfs(edges, visited, inPath, cnt, nextNode);
            } else {//if visited already
                if (inPath[nextNode]) { // if in curr path
                    int cycleLen = cnt[node] - cnt[nextNode] + 1;
                    longest = max(longest, cycleLen);
                }
            }
        }
        inPath[node] = false;
    }

    int longestCycle(vector<int>& edges) {
        int n = edges.size();
        vector<bool> visited(n, false);
        vector<bool> inpath(n, false);
        vector<int> cnt(n, 1);//cnt of nth node in a path

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {

                dfs(edges, visited, inpath, cnt, i);
            }
        }
        return longest;
    }
};
