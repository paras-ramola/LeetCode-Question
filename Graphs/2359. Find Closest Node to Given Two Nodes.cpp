// Appraoch 1:DFS
// T.C: 0(N) ,  S.C: 0(N)
class Solution {
public:
    void dfs(vector<int>& dist, vector<bool>& vis, vector<int>& edges,
             int node) {

        vis[node] = true;

        int nextNode = edges[node];
        // if there is a valid edge and the neighbor is not visited yet
        if (nextNode != -1 && !vis[nextNode]) {
            // distance to neighbor = distance to currentNode + 1
            dist[nextNode] = 1 + dist[node];
            dfs(dist, vis, edges, nextNode);
        }
    }
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size(); // no of Nodes

        // visited arrays for both starting nodes
        vector<bool> vis1(n, false);
        vector<bool> vis2(n, false);

        // distance arrays, initialized with INT_MAX (unreachable)
        vector<int> dist1(n, INT_MAX); // dist of each node with node1
        vector<int> dist2(n, INT_MAX); // dist of each node with node2

        // distance to starting nodes is zero
        dist1[node1] = 0;
        dist2[node2] = 0;

        // run DFS for both starting points
        dfs(dist1, vis1, edges, node1);
        dfs(dist2, vis2, edges, node2);

        int smallestMaxDis = INT_MAX; // minimum among all "maximum distances"
        int smallestmMaxDisIdx = -1;  // ans

        for (int i = 0; i < n; i++) {
            int maxDis = max(dist1[i], dist2[i]);
            if (maxDis < smallestMaxDis) {
                smallestMaxDis = maxDis;
                smallestmMaxDisIdx = i;
            }
        }

        return smallestmMaxDisIdx;
    }
};

//Approach 2: BFS


class Solution {
public:
    void bfs(vector<int>& distance, vector<int>& edges, int startNode) {

        // distance to starting node is zero
        distance[startNode] = 0;

        queue<int> q;
        q.push(startNode);

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();

            int nextNode = edges[currentNode];
            // if there is a valid edge and the nextNode is not yet visited
            if (nextNode != -1 && distance[nextNode] == INT_MAX) {
                distance[nextNode] = distance[currentNode] + 1;
                q.push(nextNode);
            }
        }
    }
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size(); // no of Nodes

        // distance arrays, initialized with INT_MAX (unreachable)
        vector<int> dist1(n, INT_MAX); // dist of each node with node1
        vector<int> dist2(n, INT_MAX); // dist of each node with node2

        // run DFS for both starting points
        bfs(dist1, edges, node1);
        bfs(dist2, edges, node2);

        int smallestMaxDis = INT_MAX; // minimum among all "maximum distances"
        int smallestmMaxDisIdx = -1;  // ans

        for (int i = 0; i < n; i++) {
            int maxDis = max(dist1[i], dist2[i]);
            if (maxDis < smallestMaxDis) {
                smallestMaxDis = maxDis;
                smallestmMaxDisIdx = i;
            }
        }

        return smallestmMaxDisIdx;
    }
};
