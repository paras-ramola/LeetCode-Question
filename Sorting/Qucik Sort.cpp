
// | Property      | Meaning                            | Quicksort Behavior | Notes                                      |
// | ------------- | ---------------------------------- | ------------------ | ------------------------------------------ |
// | **Stable**    | Keeps equal elements in same order | ❌ Not stable       | Can be made stable with extra memory       |
// | **In-place**  | Uses small extra memory            | ✅ Yes (O(log n))   | Recursive calls only                       |
// | **Adaptive**  | Faster if input partially sorted   | ❌ No               | Same performance regardless of input order |
// | **Internal**  | Works in main memory               | ✅ Yes              | Not suitable for disk sorting              |
// | **Recursive** | Uses recursion                     | ✅ Yes              | Can be made iterative                      |


// Approach 1:
// Avg case:0(n log n)
// Worst Case:0(n*n)->if arr is already sorted (depth becomes 'n' instead of logn)
// 
class Solution {
public:
    int partition(vector<int>& nums, int s, int e) {
        int pivot = nums[s];

        int cnt = 0;

        for (int i = s + 1; i <= e; i++) {
            if (nums[i] < pivot) {
                cnt++;
            }
        }
        int pivotIdx = s + cnt;
        if (pivotIdx <= e) {
            swap(nums[s], nums[pivotIdx]);
        }

        int i = s, j = e;

        while (s < pivotIdx && j > pivotIdx) {
            while (nums[i] < nums[pivotIdx]) {
                i++;
            }
            while (nums[j] > nums[pivotIdx]) {
                j--;
            }
            if (i < pivotIdx && j > pivotIdx) {
                swap(nums[i], nums[j]);
                i++;
                j--;
            }
        }
        return pivotIdx;
    }
    void quickSort(vector<int>& nums, int s, int e) {
        if (s < e) {
            int p = partition(nums, s, e);

            quickSort(nums, s, p - 1);

            quickSort(nums, p + 1, e);
        }
    }
    vector<int> sortArray(vector<int>& nums) {

        quickSort(nums, 0, nums.size() - 1);

        return nums;
    }
};

// TO improve worst case ->use random partioning
// T.C:0(n logn) ->practical
// Worst Case : better than 0(n*n)


class Solution {
public:
    // Partition function using Hoare's partition scheme
    int partition(vector<int>& nums, int s, int e) {
        // Choose a random pivot index and value
        int pivotIndex = s + rand() % (e - s + 1);
        int pivot = nums[pivotIndex];

        int i = s;
        int j = e;

        // Hoare's partition process
        while (i <= j) {
            // Move i forward until an element >= pivot is found
            while (nums[i] < pivot)
                i++;

            // Move j backward until an element <= pivot is found
            while (nums[j] > pivot)
                j--;

            // Swap out-of-place elements
            if (i <= j) {
                swap(nums[i], nums[j]);
                i++;
                j--;
            }
        }

        // Return the partition boundary (first index of the right subarray)
        return i;
    }

    // Recursive quicksort
    void quickSort(vector<int>& nums, int s, int e) {
        if (s < e) {
            int p = partition(nums, s, e); // p is boundary index

            // Recursively sort both partitions
            quickSort(nums, s, p - 1);
            quickSort(nums, p, e);
        }
    }

    vector<int> sortArray(vector<int>& nums) {

        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};


// 1️⃣ Why Quicksort is preferred over Merge Sort (for arrays)
// Key reasons:

// In-place sorting
// Quicksort rearranges elements in the same array using swaps. Space complexity: O(log n) on average (for recursion stack).  Merge Sort requires O(n) extra memory for merging.
//  For large arrays, saving memory matters.

// Cache efficiency
// Quicksort works in contiguous memory (arrays), which is cache-friendly. Merge Sort frequently copies elements to temporary arrays → more cache misses.

// Average-case speed
// Quicksort has a smaller constant factor in practice. On average, Quicksort is faster than Merge Sort for in-memory arrays.

// Quicksort is usually faster, in-place, and cache-friendly, which is why it is the preferred sorting algorithm for arrays in practice.

// 2️⃣ Why Merge Sort is preferred over Quicksort in Linked Lists
// Key reasons:

// Linked lists cannot support random access efficiently
// Quicksort relies on indexing (nums[i], nums[j]) to swap elements.In a linked list, accessing the i-th element is O(n) → slows Quicksort dramatically.

// Merge operation is natural.
// In Merge Sort, you can split a linked list into two halves using slow/fast pointers. Merging two sorted linked lists can be done in O(1) extra space using pointer manipulations — no copying of nodes required.

// No extra memory needed
// Unlike arrays, Merge Sort on linked lists does not require O(n) extra memory, because nodes can be rearranged by changing next pointers.
// Quicksort would need extra work or is inefficient due to random access.

// Stable sorting
// Merge Sort is stable by default, which is often desirable for linked lists containing records.

// Merge Sort is preferred because it avoids random access, can merge in-place with pointers, and provides guaranteed O(n log n) performance.
