// # Longest Subarray With Restricted Pair Sums — Samjhte hain step by step

 Intuition
// Sabse important cheez jo miss ho jaati hai: **`nums[i] >= 1`** (sab positive hain, constraint dekho: `1 <= nums[i] <= 500`).
// Iska matlab: agar `nums[i] + nums[j] == nums[k]`, toh chunki dono `nums[i]` aur `nums[j]` positive hain (kam se kam 1), isliye:
// ```
nums[k] > nums[i]   AND   nums[k] > nums[j]
// ```
// Yani **k hamesha "बड़ा" element hoga** — woh dusre do se strictly bada value rakhta hai.
// Toh problem effectively ye ban jaati hai: *"Ek window mein koi bhi teen elements (do chhote + ek unka sum) present nahi hone chahiye."*

## Kaunsa pattern lagega?

// Jab bhi hum "longest subarray jisme koi bad property na ho" dekhte hain, aur ye property **monotonic** hai (agar window invalid hai toh usko bada karne se woh invalid hi rahegi, kabhi valid nahi banegi), toh **Sliding Window (Two Pointer)** lagta hai.
// Yahan monotonicity check karo: agar `[l, r]` invalid hai (kisi bad triple `i,j,k` ki wajah se), toh `[l, r]` ka koi bhi superset (chhota `l` ya bada `r`) 
// bhi invalid hi rahega — kyunki wo bad triple ab bhi range ke andar hai. Isliye jaise-jaise `r` badhta hai, `l` sirf aage hi badhega, kabhi peeche nahi jaayega. **Classic two-pointer setup.**

How to check Voilation
// `nums[i]` sirf `1` se `500` tak hi ho sakta hai. Ye chhoti range hai — isse hum **frequency array** bana sakte hain: `freq[v]` = window mein value `v` kitni baar present hai.
// Jab hum ek naya element `x = nums[r]` window mein daalte hain, toh sirf **do tarah ke naye violations** ban sakte hain (kyunki purana window already valid tha):

**Case A — naya `x` khud `k` (sum) ban jaaye:**
// Kya window mein koi do existing values `a, b` hain jinka `a + b == x`?
- Agar `a != b`: dono ka `freq >= 1` chahiye
- Agar `a == b` (matlab `x` even hai): `freq[a] >= 2` chahiye (do alag indices chahiye)

**Case B — naya `x` khud `i` ya `j` ban jaaye:**
-Kya window mein koi existing value `v` hai aur koi existing value `w` hai jisse `x + v == w`?
// (x naya element + purana element = purana bada element)

// Dono checks `O(500)` mein ho jaate hain kyunki values ki range chhoti hai (1 se 500).

## Algorithm (poora flow)

// 1. `l = 0`, `freq[]` = sab zero, `ans = 0`
// 2. Har `r` ke liye:
//    - `x = nums[r]`
//    - Jab tak `x` ko current `freq` mein daalne se **violation (A ya B)** ho raha hai:
//      - `freq[nums[l]]--` (left se element nikaalo)
//      - `l++`
//    - Ab `x` safe hai, `freq[x]++`
//    - `ans = max(ans, r - l + 1)`
// 3. `ans` return karo

// Har violation-check `O(500)` leta hai, aur `l` total milaake sirf `n` baar hi aage badhta hai — isliye poora algorithm roughly `O(n * 500)` hai. `n <= 1000` ke liye ye bohot fast hai.

## Dry Run — Example 1: `nums = [2,3,5,3,2,1]`

// | r | x | Window before | Violation check | Action | Window after | Length |
// |---|---|---|---|---|---|---|
// | 0 | 2 | {} | koi nahi | insert | {2} → [0,0] | 1 |
// | 1 | 3 | {2} | koi nahi | insert | {2,3} → [0,1] | 2 |
// | 2 | 5 | {2,3} | **2+3=5 ❌** | l=0 hatao → {3} | recheck: safe → insert {3,5} | [1,2] → 2 |
// | 3 | 3 | {3,5} | koi nahi | insert | {3,3,5} → [1,3] | **3** |
// | 4 | 2 | {3,3,5} | **3+2=5 ❌** | l=1 hatao → {3,5}, still **3+2=5 ❌** → l=2 hatao → {3} | recheck: safe → insert {3,2} | [3,4] → 2 |
// | 5 | 1 | {3,2} | **2+1=3 ❌** | l=3 hatao → {2} | recheck: safe → insert {2,1} | [4,5] → 2 |

// Max length dekha gaya = **3** ✅ (matches `[3,5,3]`)

Example to try:
 //nums = [1,2,4,6], ouput=3
 //nums =  [19,28,30,19,12,5,11,22,17,1,21]  ,  Output->  6
 //nums = [1,1,2], Output = 2

Code:

class Solution {
public:
    int maxSubarrayLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> freq(501, 0);   // values 1..500
        int l = 0, ans = 0;

        for (int r = 0; r < n; r++) {
            int x = nums[r];

            while (causesViolation(freq, x)) {
                freq[nums[l]]--;
                l++;
            }

            freq[x]++;
            ans = max(ans, r - l + 1);
        }
        return ans;
    }

private:
    bool causesViolation(vector<int>& freq, int x) {
        // Case A: existing a + existing b == x  (x becomes 'k')
        for (int a = 1; a < x; a++) {
            int b = x - a;
            if (a == b) {
                if (freq[a] >= 2) return true;
            } else {
                if (freq[a] > 0 && freq[b] > 0) return true;
            }
        }

        // Case B: x + existing v == existing w  (x becomes 'i' or 'j')
        for (int v = 1; v <= 500; v++) {
            if (freq[v] == 0) continue;
            int w = v + x;
            if (w <= 500 && freq[w] > 0) return true;
        }

        return false;
    }
};

