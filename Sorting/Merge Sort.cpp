// T.C:0(n log n)

class Solution {
public:
    void merge(vector<int>& nums, int s, int e) {

        int mid = s + (e - s) / 2;
        int leftLen = mid - s+1;
        int rightLen = e - mid ;
        vector<int> left(leftLen);
        vector<int> right(rightLen);

        int mainIdx = s;
        for (int i = 0; i <leftLen; i++) {
            left[i] = nums[mainIdx++];
        }
        for (int i =0; i <rightLen; i++) {
            right[i] = nums[mainIdx++];
        }

        int i = 0, j = 0;
        mainIdx = s;
        while (i < leftLen && j < rightLen) {
            if (left[i] < right[j]) {
                nums[mainIdx++] = left[i++];
            } else {
                nums[mainIdx++] = right[j++];
            }
        }

        while (i < leftLen) {
            nums[mainIdx++] = left[i++];
        }
        while (j < rightLen) {
            nums[mainIdx++] = right[j++];
        }
    }
    void mergeSort(vector<int>& nums, int s, int e) {
        if (s < e) {
          // get the mid
            int mid = s + (e - s) / 2;

            mergeSort(nums, s, mid );//sort left part
            mergeSort(nums, mid+1, e);//sort right part

          //merge them
            merge(nums, s, e);
        }
    }
    vector<int> sortArray(vector<int>& nums) {

        mergeSort(nums, 0, nums.size() - 1);

        return nums;
    }
};
