//Approach 1:sort in descending order k times and find the smallest elment
// T.C:0(K* log N)

//approach 2:using priority_queue to get max elment
//T.C: 0((n + k) log N)


class Solution {
public:
//using priority_queue
//take the max elment ->q.top() and insert ceil(q.top()/3)
    long long maxKelements(vector<int>& nums, int k) {

        priority_queue<long long> q;

//push into max-heap
        for (auto i : nums) {
            q.push(i);
        }

        long long sum = 0;

        //perform k times
        while (k--) {
            long long  largVal = q.top();
            q.pop();
            sum += largVal;//add the largeVal
            
            long long val = ceil(largVal / 3.0);
            q.push(val);
        }

        return sum;
    }
};
