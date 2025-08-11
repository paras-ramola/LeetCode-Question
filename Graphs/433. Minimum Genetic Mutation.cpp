/*
Approach 1:BFS

BFS ensures we find the minimum number of mutations  because:
  1. BFS explores all strings reachable in 'k' mutations before moving to 'k+1'.
  2. We only increment `changes` after completing a whole BFS level,because each level represents *exactly one more mutation step*
           from the prev level.
  3. In DFS, we might follow a longer path before finding the target,but BFS guarantees the first time we find `endGene` is with the fewest changes.
  */
class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        // All possible gene characters
        vector<char> gene = {'A', 'C', 'G', 'T'};

        // Convert bank to unordered_set for O(1) lookup
        unordered_set<string> bankSet(bank.begin(), bank.end());

        // If endGene not in bank, no solution possible
        if (bankSet.find(endGene) == bankSet.end())
            return -1;

        // BFS queue
        queue<string> q;
        q.push(startGene);

        // Visited map to avoid cycles
        unordered_map<string, bool> visited;
        visited[startGene] = true;

        int changes = 0; // Number of mutations
        while (!q.empty()) {
            int n = q.size(); // Process one BFS level

            while (n--) {
                string front = q.front();
                q.pop();

                // Found target gene
                if (front == endGene)
                    return changes;

                // Try changing each position to all possible gene letters
                for (int i = 0; i < front.size(); i++) {
                    string temp = front;
                    for (auto c : gene) {
                        temp[i] = c;

                        // Only proceed if mutation is valid and not visited
                        if (bankSet.count(temp) && !visited[temp]) {
                            q.push(temp);
                            visited[temp] = true;
                        }
                    }
                }
            }
            changes++; // One level completed → one mutation step
        }
        return -1; // No path found
    }
};

//why use bfs ->because in queue we only increase count of mutation/changes  only when all changes in a level a fully traversed ->because all string in a lvl are there fue to a single change in prev level->so you cant increase mutation/changes for each string(DFS)
