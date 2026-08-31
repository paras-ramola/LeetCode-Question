

//Approach 1:

// T.C: O(n) + O(n) = O(n)
// S.C: O(n)
// because we store all critical point indexes
class Solution {
public:

    vector<int> nodesBetweenCriticalPoints(ListNode* head) {

        // Store the indexes of all critical points
        vector<int> points;

        ListNode* curr = head;

        // Previous and next node values
        int prevVal = -1;
        int nextVal = -1;

        // Index of current node
        int idx = 1;

        while (curr != NULL) {

            // Get the next node's value
            if (curr->next == NULL) {
                nextVal = -1;
            } else {
                nextVal = curr->next->val;
            }

            // A node can be a critical point only if
            // it has both a previous and next node.
            if (prevVal != -1 && nextVal != -1) {

                int currVal = curr->val;

                // Critical point = local minimum OR local maximum
                // Local minimum:  curr < prev AND curr < next
                // Local maximum:  curr > prev AND curr > next

                if ((currVal < prevVal && currVal < nextVal) ||
                    (currVal > prevVal && currVal > nextVal)) {
                    points.push_back(idx);
                }
            }

            // Current node becomes previous node
            prevVal = curr->val;
            curr = curr->next;
            idx++;
        }

        int n = points.size();

        // Need at least 2 critical points
        // to calculate a distance.
        if (n <= 1) {
            return {-1, -1};
        }

        // Maximum distance:  Distance between first and last critical point.
        int maxDistance = points[n - 1] - points[0];

        // Minimum distance: Minimum distance between two consecutive  critical points.
        int minDistance = INT_MAX;

        for (int i = 0; i < n - 1; i++) {
            minDistance = min( minDistance, points[i + 1] - points[i] );
        }


        return {minDistance, maxDistance};
    }
};


//Approach 2:
// T.C: O(n)
// We traverse the linked list only once.

// S.C: O(1)
// We only use a few variables.
// No vector/list of critical points is stored.

class Solution {
public:

    vector<int> nodesBetweenCriticalPoints(ListNode* head) {

        // res[0] = minimum distance
        // res[1] = maximum distance
        vector<int> res = {INT_MAX, -1};

        ListNode* curr = head;

        int prevVal = -1;
        int nextVal = -1;

        int idx = 1;  // Current node's index

        // Index of the first critical point
        int firstCrit = -1;

        // Index of the previous critical point
        int prevCrit = -1;


        while (curr != NULL) {

            // Get next node's value
            if (curr->next == NULL) {
                nextVal = -1;
            } else {
                nextVal = curr->next->val;
            }

            // Current node must have both previous
            // and next nodes to be a critical point.
            if (prevVal != -1 && nextVal != -1) {

                int currVal = curr->val;

                // Check for local minimum OR local maximum
                if ((currVal < prevVal && currVal < nextVal) ||
                    (currVal > prevVal && currVal > nextVal)) {

                    // First critical point found
                    if (firstCrit == -1) {
                        firstCrit = idx;
                        prevCrit = idx;
                    }

                    // Another critical point found
                    else {
                        // Distance between current and  previous critical point
                        res[0] = min(res[0], idx - prevCrit);

                        // Distance between first and  current critical point
                        res[1] = idx - firstCrit;

                        // Current critical point becomes  the previous critical point
                        prevCrit = idx;
                    }
                }
            }

            // Current node becomes previous node
            prevVal = curr->val;

            curr = curr->next;
            idx++;
        }


        // If we didn't find at least 2 critical points,
        // answer is {-1, -1}.
        if (res[0] == INT_MAX || res[1] == -1) {
            return {-1, -1};
        }

        return res;
    }
};
