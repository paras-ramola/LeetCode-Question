//Appraoch 1:BRUTE FORCE
//T.C:0(n*n) S.C:0(1)

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {

        int n = nums.size();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int sum=nums[i]+nums[j];
                if(sum==target){
                    return {i,j};
                }
            }
        }
        return {-1,-1};
    }
};




//Approach 2:Hash map
//T.C: 0(n) , S.C;0(n)

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();

        unordered_map<int, int> mp;  
        // key   -> number from nums
        // value -> its index in the array

        for (int i = 0; i < n; i++) {
            int curr = nums[i];             // current number
            int req_sum = target - curr;    // number needed to reach target

            // If req_sum already exists in map, we found the pair
            if (mp.find(req_sum) != mp.end()) {
                return {mp[req_sum], i};    // return indices of the pair
            }

            // Otherwise, store the current number with its index
            mp[curr] = i;
        }

        // If no pair is found (though problem guarantees one exists)
        return {-1, -1};
    }
};
