// Approach 1: DFS


class Solution {
public:
    vector<vector<int>> ans;

    void dfs(int src, int dest, vector<vector<int>>& graph, vector<int> path) {
        path.push_back(src);
        if (dest == src) {
            ans.push_back(path);
            return;
        }

        for (auto i : graph[src]) {
            dfs(i, dest, graph, path);
        }
    }
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {

        int n=graph.size();

        vector<int> path;
        dfs(0, n - 1, graph, path);

        return ans;
    }
};


//approach 2:BFS

