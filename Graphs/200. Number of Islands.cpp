//Appraoch 1:DFS
//T.C:0(n*m)
// For each cell, you look at 4 neighbors → that’s a constant number of checks → O(1) per cell.
// Total work = n*m * O(1) = O(n*m).
class Solution {
public:
    vector<vector<int>> directions{{-1, 0}, {1, 0} ,{0, -1}, {0, 1}};
    void dfs(int i, int j, vector<vector<char>>& grid, int n, int m) {
        grid[i][j] = '0';

        for(auto dir:directions){
            int x = dir[0];
            int y = dir[1];
            int new_x = x + i;
            int new_y = y + j;
            if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m &&
                grid[new_x][new_y] == '1') {
                dfs(new_x, new_y, grid, n, m);
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();//rows
        int m = grid[0].size();//cols

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    dfs(i, j, grid, n, m);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

//Appraoch 2:BFS
//T.C:0(n*m)
class Solution {
public:
    vector<vector<int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    void bfs(int i, int j, vector<vector<char>>& grid, int n, int m) {

        queue<pair<int, int>> q;
        q.push({i, j});
        grid[i][j] = '0';

        while (!q.empty()) {
            auto temp=q.front();
            q.pop();
            for (auto dir : directions) {
                int x = dir[0];
                int y = dir[1];
                int new_x = x + temp.first;
                int new_y = y + temp.second;
                if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m &&
                    grid[new_x][new_y] == '1') {
                    q.push({new_x,new_y});
                    grid[new_x][new_y]='0';
                }
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();    // rows
        int m = grid[0].size(); // cols

        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    bfs(i, j, grid, n, m);
                    cnt++;
                }
            }
        }
        return cnt;
    }
};
