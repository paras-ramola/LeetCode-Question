
//Approach 1:DFS
//T.C:0(V+E) each node is visited once ,each edge is visited twice


class Solution {
public:
//DFS
    // use map to keep track of cloned nodes-> so they are not cloned again and again
    unordered_map<Node*, Node*> mp;

    void dfs(Node* node, Node* cloneNode) {
        for (auto neigh : node->neighbors) {
            if (mp.find(neigh) ==
                mp.end()) { // if a clone of neigh node is not present
                Node* cloneNeigh = new Node(neigh->val); // clone it
                mp[neigh] = cloneNeigh;
                cloneNode->neighbors.push_back(
                    cloneNeigh); // push cloneNeighbors of cloneNode in list
                dfs(neigh, cloneNeigh);

            } else { // if clone of neigh node is present
                // acces the clone node from map
                cloneNode->neighbors.push_back(mp[neigh]);
            }
        }
    }
    Node* cloneGraph(Node* node) {

        if (node == NULL)
            return node;

        // clone the given node
        Node* cloneNode = new Node(node->val);
        // store clone of a node in map
        mp[node] = cloneNode;

        // Now,clone its neighbors and reccursively thier neighbors
        dfs(node, cloneNode);

        return cloneNode;
    }
};

//Approach 2:BFS

class Solution {
public:
    unordered_map<Node*, Node*> mp; // map original -> clone

    Node* cloneGraph(Node* node) {
        if (node == nullptr) return nullptr;

        // create clone of starting node
        Node* startClone = new Node(node->val);
        mp[node] = startClone;

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            Node* currClone = mp[curr]; // get its clone safely

            // clone neighbors
            for (auto neigh : curr->neighbors) {
                if (mp.find(neigh) == mp.end()) {//if neigh is not cloned yet
                    Node* neighClone = new Node(neigh->val);//clone it 
                    mp[neigh] = neighClone;//map clone node to original Node
                    q.push(neigh);
                }
                // link neighbor clone to current clone
                currClone->neighbors.push_back(mp[neigh]);
            }
        }

        return startClone; // return clone of starting node
    }
};
