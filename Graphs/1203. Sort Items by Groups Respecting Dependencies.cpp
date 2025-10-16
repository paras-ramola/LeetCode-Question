//Approach 1:Topological Sort(khan's Algo)

// T.C=O(n+E)​
//building adj:O(n+E)​ +topoSort: O(n+E)​

class Solution {
public:
    // Function to perform Topological Sort using Kahn's Algorithm
    vector<int> topoSort(unordered_map<int, vector<int>>& adj, vector<int>& indegree) {

        vector<int> ordering; // stores final topological order
        queue<int> q;
        for (int i = 0; i < indegree.size(); i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            ordering.push_back(curr);
            // Decrease indegree of all adjacent nodes
            for (auto after : adj[curr]) {
                indegree[after]--;
                if (indegree[after] == 0) {
                    q.push(after);
                }
            }
        }

        // If we couldn't include all nodes, there’s a cycle → return empty
        if (indegree.size() != ordering.size()) {
            return {};
        }
        return ordering;
    }

    vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {

        // Step 1: Assign new group numbers to ungrouped items (-1)
        for (int i = 0; i < n; i++) {
            if (group[i] == -1) {
                group[i] = m++; // new unique group ID
            }
        }

        // Step 2: Initialize adj lists and indegree arr
        vector<int> itemIndegree(n, 0);           // indegree for items
        vector<int> groupIndegree(m, 0);          // indegree for groups
        unordered_map<int, vector<int>> itemAdj;  // item dependency graph
        unordered_map<int, vector<int>> groupAdj; // group dependency graph

        // Step 3: Build both item and group dependency graphs
        for (int item = 0; item < n; item++) {
            for (auto before : beforeItems[item]) {
                // Item dependency (before → item)
                itemAdj[before].push_back(item);
                itemIndegree[item]++;

                // If dependency crosses groups, add to group graph
                if (group[before] !=
                    group[item]) { // if bith belongs to diff group
                    int fromGroup = group[before];
                    int toGroup = group[item];
                    groupAdj[fromGroup].push_back(toGroup);
                    groupIndegree[toGroup]++;
                }
            }
        }

        // Step 4: Perform topological sort on items and groups
        vector<int> itemOrder = topoSort(itemAdj, itemIndegree);
        vector<int> groupOrder = topoSort(groupAdj, groupIndegree);

        // If sorting fails for either (cycle detected), return empty
        if (itemOrder.empty() || groupOrder.empty())
            return {};

        // Step 5: Arrange items(ordered) within their respective groups
        unordered_map<int, vector<int>> itemsInGroup;
        for (auto item : itemOrder) {
            int g = group[item];
            itemsInGroup[g].push_back(item);
        }

        // Step 6: Build the final answer using sorted group order
        vector<int> result;
        for (auto g : groupOrder) {
            auto& items = itemsInGroup[g]; // take ordered items vec from the
                                           // map
            result.insert(result.end(), items.begin(), items.end()); // insert the items at the end in
                                        // (first->last) manner
        }

        return result;
    }
};
