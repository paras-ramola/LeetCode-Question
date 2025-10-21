// Approach 1:Topological Sort (pre-requisite relationship)
//T.C:0(V+E)

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        // Step 1: Build adjacency list and indegree array
        unordered_map<int, list<int>> graph;
        vector<int> indegree(n, 0);
        
        for (auto relation : relations) {
            int prereq = relation[0] - 1;  // convert to 0-based index
            int course = relation[1] - 1;
            graph[prereq].push_back(course);
            indegree[course]++;
        }

        // Step 2: Initialize total_time array and queue for topological order
        vector<int> totalTime(n, 0);
        queue<int> q;
        
        for (int i = 0; i < n; i++) {
            totalTime[i] = time[i]; // base time to complete each course
            if (indegree[i] == 0) {//complete  courses with no prerequisites first
                q.push(i); 
            }
        }

        // Step 3: Process courses in topological order
        while (!q.empty()) {
            int currCourse = q.front();
            q.pop();

            for (auto nextCourse : graph[currCourse]) {
                indegree[nextCourse]--;
                
                // Update total time to complete nextCourse
                totalTime[nextCourse] = max(
                    totalTime[nextCourse],
                    totalTime[currCourse] + time[nextCourse]
                );

                // If all prerequisites for nextCourse are done, push it to queue
                if (indegree[nextCourse] == 0) {
                    q.push(nextCourse);
                }
            }
        }

        // Step 4: The answer is the maximum time among all courses
        return *max_element(totalTime.begin(), totalTime.end());
    }
};
