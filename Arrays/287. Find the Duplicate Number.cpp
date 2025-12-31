// Approach 1:
// T.C;0(n)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {

        // Loop through each element in the array
        for (int i = 0; i < nums.size(); i++) {
          
            // Take abs val because some num  may already be marked -ve
            int num = abs(nums[i]);

            // Use the  same number as an index (range [1,n] < size(n+1)) 
            int idx = num; 

            // If the val at this idx is already -ve,
            // it means we have visited this num before → duplicate found
            if (nums[idx] < 0) {
                return num;
            }
            // Otherwise, mark this index as visited  by making the value negative
            else {
                nums[idx] *= -1;
            }
        }
        // This line will not be reached  because a duplicate is guaranteed
        return -1;
    }
};

// Approach 2: Slow & fast pointers
// T.C;0(n)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {

        int slow = 0;
        int fast = 0;

        // Move slow by 1 step and fast by 2 steps -> If there is a duplicate, they will meet inside the cycle
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        // found the duplicate number

        slow = 0;//reset slow to start

      
        // Move both pointers one step at a time ->  They will meet at the duplicate number
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }

        return slow;
    }
};


// Approach 3: Index Sort/Cyclic Sort
// T.C;0(n)
// If the array had no duplicate, then after sorting:
// Every number x would be at index x − 1
// i.e., nums[i] = i + 1
// Since one number is duplicated, two numbers want the same index, and that’s how we detect the duplicate.
class Solution {
public:
    int findDuplicate(vector<int>& nums) {

        int i = 0;

        // Loop through the array
        while (i < nums.size()) {

            int num = nums[i];       // current num
            int idx = num - 1;       // correct idx for this num

            // Case 1: num is already at correct position
            if (num == i + 1) {
                i++;                // move to next index
            }

            // Case 2: duplicate found
            // the correct position already has the same number
            else if (num == nums[idx]) {
                return num;         // duplicate number
            }

            // Case 3: place number at its correct position
            else {
                nums[i] = nums[idx];
                nums[idx] = num;
            }
        }

        return 0; // duplicate always exists
    }
};

