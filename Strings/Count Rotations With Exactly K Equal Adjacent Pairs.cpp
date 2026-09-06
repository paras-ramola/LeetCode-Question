// APPROACH:
        // String ko ek circle (gol chakkar) ki tarah socho, jisme
        // last character wapas first character se connected hai.
        // 
        // Har rotation basically circle ko kisi ek jagah se "cut" 
        // karke seedha (linear) banane jaisa hai. Isliye humein 
        // actually saari rotations generate karne ki zaroorat nahi.
        //
        // 'total' = circle mein kitne adjacent pairs equal hain
        //           (last-first wala circular pair bhi count hota hai)
        //
        // Jab hum circle ko kisi ek point se cut karte hain, do 
        // cases ban sakte hain:
        //   1. Cut equal characters ke beech hua -> ek equal pair 
        //      "toot" gaya -> naye rotation ka score = total - 1
        //   2. Cut unequal characters ke beech hua -> kuch nahi 
        //      badla -> naye rotation ka score = total (as it is)
        //
        // Total 'n' possible cut points hain (n rotations ke liye).
        // Unme se 'total' cut points aise hain jahan pair equal hai,
        // aur baaki 'n - total' cut points aise hain jahan pair 
        // unequal hai.
        //
        // Isliye:
        //   agar k == total       -> answer = n - total  
        //                             (jitne unequal cut points hain)
        //   agar k == total - 1   -> answer = total  
        //                             (jitne equal cut points hain)
        //   otherwise              -> answer = 0 (aisa koi rotation nahi banega)



class Solution {
public:
    int countRotations(string s, int k) {

        int n = s.size();
        int total = 0;

        // Step 1: Normal adjacent pairs count karo (i aur i+1 ke beech)
        for (int i = 0; i < n; i++) {
            if (i + 1 < n && s[i] == s[i + 1]) {
                total++;
            }
        }

        // Step 2: Circular pair bhi count karo (last aur first character)
        // Kyunki circle mein ye do bhi "adjacent" maane jaate hain
        if (s[0] == s[n - 1]) {
            total++;
        }

        // Step 3: Ab bas k ko total se compare karke direct answer nikalo
        // Case 1: k == total -> unequal cut points wali rotations chahiye
        if (k == total) {
            return n - total;
        }

        // Case 2: k == total - 1 -> equal cut points wali rotations chahiye
        if (k == total - 1) {
            return total;
        }

        // Case 3: koi aur value possible hi nahi (score sirf total ya 
        // total-1 ho sakta hai), toh answer 0
        return 0;
    }
};
