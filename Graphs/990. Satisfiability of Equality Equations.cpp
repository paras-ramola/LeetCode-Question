//Approach 1:DSU
class Solution {
public:
    // Find function with path compression
    int find(int x, vector<int>& parent) {
        if (x != parent[x]) {
            parent[x] = find(parent[x], parent); // Path compression
        }
        return parent[x];
    }

    // Union function (returns true if already connected)
    bool Union(int x, int y, vector<int>& parent, vector<int>& rank) {
        int x_parent = find(x, parent);
        int y_parent = find(y, parent);

        // Already in the same set
        if (x_parent == y_parent) {
            return true;
        }

        // Union by rank → attach smaller tree under bigger one
        if (rank[x_parent] > rank[y_parent]) {
            parent[y_parent] = x_parent;
        } 
        else if (rank[x_parent] < rank[y_parent]) {
            parent[x_parent] = y_parent;
        } 
        else {
            parent[x_parent] = y_parent;
            rank[y_parent] += 1; // Increase rank if equal
        }
        return false;
    }

    bool equationsPossible(vector<string>& equations) {
        // There are only 26 lowercase letters a–z
        vector<int> parent(26);
        vector<int> rank(26, 1);

        // Initially, each variable is its own parent
        for (int i = 0; i < 26; i++) {
            parent[i] = i;
        }

        //only thing to keep track of eq[1]=>'=' or '!'

        // Step 1: Handle all "==" equations first (connect variables)
        for (auto eq : equations) {
            int a = eq[0] - 'a';
            int b = eq[3] - 'a';

            if (eq[1] == '=') { // "==" case
                Union(a, b, parent, rank);
            }
        }

        // Step 2: Check all "!=" equations for contradictions
        for (auto eq : equations) {
            int a = eq[0] - 'a';
            int b = eq[3] - 'a';

            if (eq[1] == '!') { // "!=" case
                // If they are in the same group, contradiction
                if (find(a, parent) == find(b, parent)) {
                    return false;
                }
            }
        }

        return true; // No contradictions found
    }
};
