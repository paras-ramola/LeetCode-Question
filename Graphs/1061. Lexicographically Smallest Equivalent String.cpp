/*Approach 1:DSU
Jahan bhi "2 entities ko ek group / set me jodna" ho → wahan DSU best hota hai.
T.C=>O(n + m) (n=>union call ->findParen=>O(α(26)) ≈ O(1) +m->replacing baseStr)

from two char ->make parent  ->lexiographically smaller
now for baseStr find the parent of each char->we will get equivalent smallest lexiographically char 
  */

   class Solution {
public:
    // DSU parent array: stores parent of each character ('a'..'z' → 0..25)
    vector<int> parent;

    // FIND operation with path compression
    int findParent(int x) {
        if (x == parent[x]) 
            return x;
        // Path compression → directly link node to ultimate parent
        return parent[x] = findParent(parent[x]);
    }

    // UNION operation → always attach larger to smaller char (to keep lexicographically smallest)
    void Union(int x, int y) {
        int x_parent = findParent(x);
        int y_parent = findParent(y);

        if (x_parent == y_parent) return; // already in same set

        // Always keep lexicographically smaller character as the parent
        if (x_parent < y_parent) {
            parent[y_parent] = x_parent;
        } else {
            parent[x_parent] = y_parent;
        }
    }

    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int n = s1.size();

        // Step 1: Initialize DSU → each character is its own parent
        parent.resize(26);
        for (int i = 0; i < 26; i++) {
            parent[i] = i;
        }

        // Step 2: Build equivalence relationships btwn char at same idx
        for (int i = 0; i < n; i++) {
            int x = s1[i] - 'a';
            int y = s2[i] - 'a';
            Union(x, y);
        }

        // Step 3: Replace each character in baseStr with 
        // the lexicographically smallest equivalent char
        for (int i = 0; i < baseStr.size(); i++) {
            int idx = baseStr[i] - 'a';
            char p = findParent(idx) + 'a'; // convert parent index back to char
            baseStr[i] = p;
        }

        return baseStr;
    }
};
//Approach 2:DFS:
//T.C: 0( N + 26 M)=> in worst case all 26 char are traversed * baseStr.len(M)

class Solution {
public:
    // Depth-First Search to find the lexicographically smallest
    // character reachable from 'curr' in the equivalence graph
    char dfs(char curr, unordered_map<int, list<int>>& adj,
             vector<int>& visited) {
        
        visited[curr - 'a'] = 1; // mark current char as visited
        char minChar = curr;     // initialize minimum as current char

        // Explore all neighbors (equivalent characters)
        for (auto i : adj[curr]) {
            if (!visited[i - 'a']) {
                // Recursively find the smallest equivalent char
                minChar = min(minChar, dfs(i, adj, visited));
            }
        }
        // Return the smallest char found in this connected component
        return min(curr, minChar);
    }

    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int n = s1.size();

        // Build adjacency list graph of equivalences
        unordered_map<int, list<int>> adj;
        for (int i = 0; i < n; i++) {
            adj[s1[i]].push_back(s2[i]);
            adj[s2[i]].push_back(s1[i]);
        }

        int m = baseStr.size();
        // For every character in baseStr, find its smallest equivalent
        for (int i = 0; i < m; i++) {
            vector<int> visited(26, 0);   // fresh visited array for each search
            baseStr[i] = dfs(baseStr[i], adj, visited);
        }

        return baseStr;
    }
};
