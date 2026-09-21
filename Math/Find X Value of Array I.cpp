Question:
// You have an array of positive integers.
//  You're allowed to:
// 1.Choose any subarray (i.e., chop off a prefix and a suffix).
// 2.Compute the product of that subarray.
// 3.Count how many subarrays give product % k == x, for every x from 0 to k-1.


//Approach 1:0(n^2) TLE

class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {

        int n = nums.size();

        vector<long long> store(k, 0); // yahan p rem ka count save hoga

        vector<long long> res;

        for (int i = 0; i < n; i++) {
            long long prod = 1;
            for (int j = i; j < n; j++) {

                prod *= nums[j];

                long long rem = prod % k;

                if (rem < k) {
                    store[rem]++;
                }

                if (rem == 0) {
                    prod = k;
                } else {
                    prod = rem;
                }
            }
        }

        for (int i = 0; i <= k - 1; i++) {
            res.push_back(store[i]);
        }

        return res;
    }
};




//Optimal Approach:
// Product bahut bada ho sakta hai (overflow), isliye hume actual product  store karne ki zaroorat nahi — 
// sirf remainder (mod k) track karna hai.
Kyuki: (a * b) % k = ((a % k) * (b % k)) % k
// Isi property ka use karke DP jaisa approach lagaya gaya hai.    //
 // Idea: har index pe, "prev" array batata hai ki previous index pe  end hone wale saare subarrs ka product-mod-k(REM) ka count kya tha,
 // Jab naya element aata hai, to:
    // 1) Ek naya subarray banta hai jo sirf current element ka hota hai
//  2) Purane saare subarrays ko current element se "extend" kiya jata hai


class Solution {
public:

    vector<long long> resultArray(vector<int>& nums, int k) {

        int n = nums.size();

        // res[r] = final answer -> total subarrays (poore array me se)
        // jinka product % k == r
        vector<long long> res(k, 0);

        // prev[r] = kitne subarrays hain jo "PREVIOUS index par khatam"
        // hote hain aur jinka product % k == r
        // Shuru me sab 0 hai kyunki abhi koi index process nahi hua
        vector<long long> prev(k, 0);

        // Array ke har element ko ek ek karke process karenge (left to right)
        for (int val : nums) {

            // curr[r] = kitne subarrays hain jo "CURRENT index par khatam"
            // hote hain aur jinka product % k == r
            // Har naye element ke liye ise fresh banate hain (sab 0 se)
            vector<long long> curr(k, 0);

            // ---- STEP 1: Sirf current element wala subarray ----
            // Yani subarray = [val] (length 1, sirf yehi ek element)
            // Iska remainder simple hai: val % k
            long long currRem = val % k;
            curr[currRem]++;   // is remainder ka count 1 badha do

            // ---- STEP 2: Purane (prev index tak ke) subarrays ko extend karo ----
            // Har possible remainder x (0 se k-1 tak) ke liye check karo
            for (int x = 0; x <= k - 1; x++) {

                // Agar prev index tak remainder x wale subarrays maujood hain
                // (yani prev[x] > 0), tabhi extend karne ka matlab hai
                if (prev[x] > 0) {

                    // Purane subarray ka product-mod-k tha "x"
                    // Ab usme current element (val) multiply karenge
                    // Naya remainder = (purana remainder * val) % k
                    // Property: (a*b) % k = ((a%k) * (b%k)) % k
                    long long rem = (x * (val % k)) % k;

                    // Jitne subarrays purane wale remainder x ke the,
                    // utne hi naye subarrays ab remainder "rem" ke ban jayenge
                    // (kyunki har purane subarray ko current element se
                    //  extend karke naya subarray current index tak bana)
                    curr[rem] += prev[x];
                }
            }

            // ---- STEP 3: curr ke sabhi counts ko final answer (res) me jod do ----
            // Kyunki curr[r] batata hai ki current index par khatam hone wale
            // kitne subarrays ka remainder r hai — ye sab final answer ka
            // part hain (chahe wo kisi bhi index se start hue ho)
            for (int x = 0; x <= k - 1; x++) {
                res[x] += curr[x];
            }

            // ---- STEP 4: prev ko update karo agle iteration ke liye ----
            // Ab "curr" hi agle element ke liye "prev" ban jayega, kyunki
            // agla element ke liye jo subarrays "extend" honge wo isi index
            // (current) tak khatam hone wale subarrays hain
            //
            // move() use karne se pura vector copy nahi hota, balki curr ke
            // andar ka data directly prev me "move" ho jata hai (efficient,
            // O(1) — koi extra copy overhead nahi)
            prev = move(curr);
        }

        // Sabhi elements process hone ke baad, res[] me final answer hai:
        // res[r] = total subarrays jinka product % k == r
        return res;
    }
};
