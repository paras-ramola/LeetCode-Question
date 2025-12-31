// ***Pattern: Whenver range is given eg: [1, n] -> use values as idx ****

// Approach 1:
// T.C:0(n),
// S.C:0(1) (exluding the op)

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            int num = abs(nums[i]);
            int idx = num - 1; // Convert num val to an arr idx (subtract 1 since
                         // values are 1-indexed but indices are 0-indexed)

            if (nums[idx] < 0) { // If already negative, it's a duplicate
                res.push_back(num);

            } else {
                nums[idx] *= -1; //// mark the traversed index with negative val
            }
        }
    }
    return res;
}
}
;

// Similar : 287. Find the Duplicate Number
