
// Approach 1:DSU
// T.C:0(n)

    class Solution {
public:

//3 contd for single valid binary tree
// 1 contd:one node can have only two child(satisfied)->given
//2 contd:a node can have only one parent
//3 contd:only one B.Tree->single component

    // Number of connected components in the graph
    int components;
    vector<int> parent;

    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    // Union operation: link parent -> child
    // Returns false if invalid (child already has a parent or cycle detected)
    bool Union(int parentNode, int childNode) {
        // If child already has a parent, invalid
        if (find(childNode) != childNode) return false;

        // If parent and child belong to the same tree, it forms a cycle
        if (find(parentNode) == find(childNode)) return false;

        // Link parent -> child
        parent[childNode] = parentNode;
        components--; // merged a component
        return true;
    }

    bool validateBinaryTreeNodes(int n, vector<int>& leftChild,
                                 vector<int>& rightChild) {
        components = n; // initially, each node is its own component
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;

        for (int i = 0; i < n; i++) {
            int lChild = leftChild[i];
            int rChild = rightChild[i];

            // Check left child
            if (lChild != -1 && Union(i, lChild) == false) return false;

            // Check right child
            if (rChild != -1 && Union(i, rChild) == false) return false;
        }

        // There should be exactly 1 component (single tree)
        return components == 1;
    }
};

//Approach 2 : MAP +DFS
// T.C:Tree or sparse graph → edges ≈ nodes → O(V + E) = O(n)

//4 contd for single valid binary tree
// 1 :one node can have only two child(satisfied)->given
//2 :a node can have only one parent
// 3:a single root(with no parent)
//4 :only one B.Tree->single component


class Solution {
public:

    // Standard DFS to mark all reachable nodes from 'node'
    void dfs(int node, unordered_map<int, list<int>>& adj, vector<bool>& visited) {
        visited[node] = true;
        for (auto child : adj[node]) {
            if (!visited[child]) {
                dfs(child, adj, visited);
            }
        }
    }

    bool validateBinaryTreeNodes(int n, vector<int>& leftChild,
                                 vector<int>& rightChild) {

        unordered_map<int, list<int>> adj;       // adjacency list
        unordered_map<int, int> childToParent;   // map child -> parent

        // Build the graph and check for multiple parents
        for (int i = 0; i < n; i++) {
            int lChild = leftChild[i];
            int rChild = rightChild[i];

            // Left child
            if (lChild != -1) {
                if (childToParent.find(lChild) != childToParent.end()) 
                    return false; // child has more than 1 parent
                childToParent[lChild] = i;
                adj[i].push_back(lChild);
            }

            // Right child
            if (rChild != -1) {
                if (childToParent.find(rChild) != childToParent.end()) 
                    return false; // child has more than 1 parent
                childToParent[rChild] = i;
                adj[i].push_back(rChild);
            }
        }

        // Identify the root node (node without parent)
        int root = -1;
        for (int i = 0; i < n; i++) {
            if (childToParent.find(i) == childToParent.end()) {
                if (root != -1) 
                    return false; // more than 1 root found
                root = i;
            }
        }

        if (root == -1) 
            return false; // no root found

        // DFS from the root to check connectivity
        vector<bool> visited(n, false);
        dfs(root, adj, visited);

        // Ensure all nodes were visited (single connected component)
        for (int i = 0; i < n; i++) {
            if (!visited[i]) return false;
        }

        return true;
    }
};
