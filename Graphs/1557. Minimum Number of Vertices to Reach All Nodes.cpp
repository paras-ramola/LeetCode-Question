//Approach 1:

class Solution {
public:

// A Node with indegree = 0 can't be reached from any node exept itself so it must be kept to traverse a graph
//A Node with indegree > 0 can be reached from any node ->no need to keep it seprately 

    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {

        vector<bool> inDegree(n, false); // keeps track of which nodes have incoming edges

        //  mark nodes that have an incoming edge
        for (auto i : edges) {
            int v=i[1];
            inDegree[v] = true;       // mark that node i[1] has an incoming edge
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (inDegree[i] == false) {  // if node has no incoming edge
                ans.push_back(i);        // add it to the answer
            }
        }

        return ans; // return all starting nodes
    }
};
