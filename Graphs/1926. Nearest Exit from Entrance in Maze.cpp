//APproach 1:BFS
//shortest Path->BFS
class Solution {
public:
    // Possible moves: right, down, left, up
    vector<vector<int>> directions{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size();
        int n = maze[0].size();

        queue<pair<int, int>> q;
        q.push({entrance[0], entrance[1]});
        
        // Mark entrance as visited so we don't revisit it
        maze[entrance[0]][entrance[1]] = '+';

        int steps = 0; // BFS level counter
        while (!q.empty()) {
            int N = q.size(); // Process current BFS layer
            while (N--) {
                auto [x, y] = q.front();
                q.pop();

                // Check if this cell is an exit (on boundary) but not the entrance
                if ((x == 0 || x == m - 1 || y == 0 || y == n - 1) &&
                    !(x == entrance[0] && y == entrance[1])) {
                    return steps;
                }

                // Explore all four directions
                for (auto dir : directions) {
                    int new_x = x + dir[0];
                    int new_y = y + dir[1];
                    
                    // Check bounds and unvisited open space
                    if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n &&
                        maze[new_x][new_y] == '.') {
                        q.push({new_x, new_y});
                        maze[new_x][new_y] = '+'; // Mark visited
                    }
                }
            }
            steps++; // Increment after processing a full BFS level
        }
        return -1; // No exit found
    }
};
