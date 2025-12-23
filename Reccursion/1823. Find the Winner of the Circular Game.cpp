// Appraoch 1: Vector +erase
// T.C:0(n*n)
// Erase->0(n)
// S.C:0(n)

class Solution {
public:
    int findTheWinner(int n, int k) {

        // Create a list to store friends numbered from 1 to n
        vector<int> friends;

        // Insert friends into the vector {1, 2, 3, ..., n}
        for (int i = 1; i <= n; i++) {
            friends.push_back(i);
        }

        // Index 'i' keeps track of the current position
        // We start counting from index 0 (friend 1)
        int i = 0;

        // Continue the game until only one friend remains
        while (friends.size() > 1) {

            // Move (k - 1)( cuz k is 1-indexed) steps ahead from curr index
            // % friends.size() ensures circular counting
            i = (i + (k - 1)) % friends.size();

            // Remove the friend at index 'i' ->  This friend loses the game
            friends.erase(friends.begin() + i);

            // After removal, the next friend automatically (erase() automatically shifts and resizes the arr)
            // becomes the new starting point, so 'i' stays same
        }

        // The last remaining friend is the winner
        return friends[0];
    }
};

// Approach 2: Queue
// T.C:0(n*k)
// S.c:0(n)



class Solution {
public:
    int findTheWinner(int n, int k) {

        // Queue to represent friends sitting in a circle
        queue<int> q;

        // Push friends numbered from 1 to n into the queue
        for (int i = 1; i <= n; i++) {
            q.push(i);
        }

        // Continue until only one friend is left
        while (q.size() > 1) {

            // We need to eliminate the k-th friend
            int steps = (k - 1) % q.size();//idx of kth friend


            // Move all the friend before kth friend at the back
            // And remove the friend at the front (kth friend)
            for (int j = 0; j < steps; j++) {
                q.push(q.front()); // move front to back
                q.pop();           // remove from front
            }

            // Remove the k-th friend (loser)
            q.pop();
            // now the next friend comes to the front
        }

        // The last remaining friend is the winner
        return q.front();
    }
};

// Approach 3:Reccursion / Josephus recurrence
// T.C:0(n)
// S.C:0(n)

class Solution {
public:

    // This function returns the WINNER INDEX (0-based)
    // for n people and step size k
    int findIdxWinner(int n, int k) {

        // Base case:
        // If there is only 1 person, that person (index 0) is the winner
        if (n == 1) {
            return 0;
        }

        // Recursive call:
        // Find winner index when there are (n - 1) people
        int idx = findIdxWinner(n - 1, k);

        // When the n-th person is added back (curr case),
        // all positions shift by k steps
        idx = (idx + k) % n;

        // Return updated index
        return idx;
    }

    // This func returns the winner NUMBER (1-based)
    int findTheWinner(int n, int k) {

        // Get winner index in 0-based indexing
        int winIdx = findIdxWinner(n, k);

        // Convert 0-based index to 1-based friend number
        return winIdx + 1;
    }
};

