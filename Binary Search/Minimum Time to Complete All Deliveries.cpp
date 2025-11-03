// Approach 1:Binary Search
// Time Complexity:0(1)

// gcd(a, b):	O(log(min(r1, r2)))->	very small (nearly constant).
// Binary Search	O(log(max_time)) ≈ 60 iterations	->≈ O(1) (constant in practice)

#define ll long long
class Solution {
public:
    // Variables to store deliveries and rest cycles
    ll d1, d2, r1, r2;

    // Function to calculate LCM (Least Common Multiple)
    ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }

    // Function to check if we can complete all deliveries in given 'time'
    bool canFinish(ll time) {
        // For delivery person 1:
        // In every 'r1' units of time, they take 1 unit of rest, so (time - time/r1)
        // gives working time
        ll t1 = time - time / r1;

        // For delivery person 2:
        ll t2 = time - time / r2;

        // For combined time:
        // Remove rest time when both rest together (LCM of r1 and r2)->No delivery can Happen
        ll t3 = time - time / lcm(r1, r2);

        // Check if both can complete their deliveries in 'time'
        // d1 <= t1 → person 1 can finish d1 deliveries
        // d2 <= t2 → person 2 can finish d2 deliveries
        // d1 + d2 <= t3 → combined total deliveries possible in time
        return d1 <= t1 && d2 <= t2 && d1 + d2 <= t3;
    }

    long long minimumTime(vector<int>& d, vector<int>& r) {

        // Extract input values
        d1 = d[0], d2 = d[1];
        r1 = r[0], r2 = r[1];

        // Binary search range for time
        ll start = 0, end = 2e18; // very large upper bound
        ll ans = -1;

        // Binary search to find minimum time required
        while (start <= end) {
            ll mid = start + (end - start) / 2;

            // If it’s possible to finish in 'mid' time,

            if (canFinish(mid)) {
                ans = mid;
                end = mid - 1; // try to find a smaller time
            }
            else {
                start = mid + 1; // Otherwise, we need more time
            }
        }
        return ans;
    }
};
