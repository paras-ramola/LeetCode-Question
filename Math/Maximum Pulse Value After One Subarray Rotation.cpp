class Solution {
public:
    long long maxValue(vector<int>& nums) {
        int n = nums.size();

        // ===== STEP 1: original pulse value nikaalo (bina kisi rotation ke) =====
        long long original_pulse = 0;

        for (int i = 0; i < n; i++) {
            // even index -> + sign, odd index -> - sign (pulse formula ke hisaab se)
            int x = (i % 2 == 0) ? nums[i] : -nums[i];
            original_pulse += x;
        }

        // ===== STEP 2: DP variables setup =====
        // odd  = kisi ODD length subarray ka minimum possible sum, jo index i par khatam ho raha ho
        // even = kisi EVEN length subarray ka minimum possible sum, jo index i par khatam ho raha ho
        // minEven = ab tak dekhe gaye saare "even" values mein sabse chhota (best) value
        long long odd = LLONG_MAX, even = LLONG_MAX, minEven = LLONG_MAX;

        // find the minimum sum even length subarr
        for (int i = 0; i < n; i++) {

            // current index ki signed value (same jaise upar x nikala tha)
            long long curr = (i % 2 == 0) ? nums[i] : -nums[i];

            // ---- newOdd nikaalo ----
            // option 1: yahin se ek naya subarray shuru karo, length = 1 (jo hamesha odd hoti hai)
            long long newOdd = curr;

            // option 2: agar pehle koi valid EVEN subarray tha, usko extend karo
            // (even + 1 element = length badh jaayegi -> odd ban jaayegi)
            // dono options mein se jo chhota (better/more negative) ho wo lo
            if (even != LLONG_MAX) {
                newOdd = min(newOdd, even + curr);
            }

            // ---- newEven nikaalo ----
            // even subarray banane ke liye kam se kam 2 elements chahiye,
            // isliye ye sirf i>0 (yani kam se kam doosra index) se hi possible hai
            long long newEven = LLONG_MAX;
            if (i > 0) {
                // pehle wale ODD subarray ko extend karo -> length badh jaayegi -> even ban jaayegi
                newEven = odd + curr;
            }

            // is index tak ka best (sabse chhota) even sum record kar lo
            minEven = min(minEven, newEven);

            // ---- agle iteration ke liye state update karo ----
            // (ye "purana" ban jaayega jab loop agla index process karega)
            odd = newOdd;
            even = newEven;
        }

        // agr koi minEven hi ni mila (matlab array itna chhota hai ki even-length subarray possible hi nahi -> n<2)
        // toh rotation possible hi nahi, seedha original pulse return kardo
        if (minEven == LLONG_MAX) {
            return original_pulse;
        }

        // ===== STEP 3: best rotation se kitna fayda (ya nuksaan) hoga, wo nikaalo =====
        // formula: jab ek even-length range rotate karte ho, uske saare elements ka sign flip ho jaata hai
        // isliye naya sum = -(purana sum), aur difference = -2 * (purana sum)
        long long diff = -2 * (minEven);

        // agar ye best rotation apply kar diya jaaye, toh pulse kya banega
        long long new_pulse = original_pulse + diff;

        // ===== STEP 4: final answer =====
        // agar minEven positive nikla, toh rotation se pulse ULTA kam ho sakta hai (diff negative)
        // isliye do options mein se best (max) choose karo:
        // 1) bilkul rotation mat karo (original_pulse)
        // 2) best rotation karo (new_pulse)
        // return karo maximum result
        return max(original_pulse, new_pulse);
    }
};
