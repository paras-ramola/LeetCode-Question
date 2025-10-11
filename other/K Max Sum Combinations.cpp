// approach 1: brute force
/*
	Time Complexity: O((N ^ 2) * log(N ^ 2))
	Space Complexity: O(N ^ 2)

	Where 'N' is the number of elements the given arrays.
*/

#include<algorithm>

vector<int> kMaxSumCombination(vector<int> &a, vector<int> &b, int n, int k){
	// Array to store all the possible sum combinations.
	vector<int>tempArray;
	
	// Loop to traverse the array 'A'.
	for(int i = 0; i < n; i++){
		// Loop to traverse the array 'B'.
		for(int j = 0; j < n; j++){
			int currentSum = a[i] + b[j];
			// Add the sum of current combination .
			tempArray.push_back(currentSum);
		}
	}
	// Sort the array in descending order.
	sort(tempArray.begin(), tempArray.end(), greater<int>()); 
	
	// Return the first 'K' values.
	vector<int> result(tempArray.begin(), tempArray.begin() + k);
	return result;
}

// approach 2: Priority_queue
// Youtube:https://youtu.be/KWgh9keTRAU?si=KWkqjJJtQBKb1K8o
 // Time Complexity: O(N * log(N))
    // Space Complexity: O(N)

vector<int> kMaxSumCombinations(vector<int>& A, vector<int>& B, int K) {
    int N = A.size();
    sort(A.begin(), A.end(), greater<int>());
    sort(B.begin(), B.end(), greater<int>());

    // Max heap: stores {sum, i, j}
    priority_queue<pair<int, pair<int, int>>> pq;
    set<pair<int, int>> visited;

    pq.push({A[0] + B[0], {0, 0}});
    visited.insert({0, 0});

    vector<int> result;

    while (K-- && !pq.empty()) {
        auto top = pq.top(); pq.pop();
        int sum = top.first;
        int i = top.second.first;
        int j = top.second.second;

        result.push_back(sum);

        // Next pair (i+1, j)
        if (i + 1 < N && vis.find({i+1,j})==vis.end()) {
            pq.push({A[i + 1] + B[j], {i + 1, j}});
            visited.insert({i + 1, j});
        }

        // Next pair (i, j+1)
        if (j + 1 < N && vis.find({i,j+1})==vis.end()) {
            pq.push({A[i] + B[j + 1], {i, j + 1}});
            visited.insert({i, j + 1});
        }
    }

    return result;
}
