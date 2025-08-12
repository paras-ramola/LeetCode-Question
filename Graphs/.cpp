//Approach 1:BFS

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();

        vector<int> visited(n, false);
        visited[0] = true;

        queue<int> q;
        q.push(0); // Start from room 0

        while (!q.empty()) {
            int room = q.front();
            q.pop();

            for (int key : rooms[room]) { // keys are just the adjacency list
                if (!visited[key]) {
                    visited[key] = true;
                    q.push(key);
                }
            }
        }

        // Check if all rooms are visited
        for (bool v : visited) {
            if (!v) return false;
        }
        return true;
    }
};


//Approach 2:DFS


class Solution {
public:
    // Recursive DFS function
    void dfs(int room, vector<vector<int>>& rooms, vector<int>& visited) {
        visited[room] = true; // Mark current room as visited
        
        // Go through all keys in the current room
        for (int key : rooms[room]) {
            // If the room this key opens hasn't been visited, visit it
            if (!visited[key]) {
                dfs(key, rooms, visited);
            }
        }
    }

    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        // Keeps track of which rooms have been visited
        vector<int> visited(rooms.size(), false);
        
        // Start DFS from room 0 (we always start here)
        dfs(0, rooms, visited);

        // After DFS, check if all rooms were visited
         for (auto i : visited) {
            if (i == false)
                return false;
        }
        return true; // All rooms visited
    }
};
