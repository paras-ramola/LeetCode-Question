Approach 1: Brute Force (Recursion + Set)
// Har character ke liye 2 choices hoti hain:
// Skip karo (mat lo) OR  Take karo (le lo)
So total choces =2^n
Problem: MLE
// Total subsequences of length n string = 2^n
// n upto 2000 ho sakta hai → 2^2000 subsequences store karna MLE (Memory Limit Exceeded) de dega
Time complexity: O(2^n), Space: O(2^n) — bahut zyada

// Sab possible subsequences generate karke set me daal do (set automatically duplicates hata dega).

// Code
// class Solution {
// public:
//     set<string> st;
//     void solve(string& s, int i, string temp) {
//         if (i == s.size()) {
//             if (!temp.empty()) st.insert(temp);
//             return;
//         }
//         solve(s, i + 1, temp);        // skip
//         temp.push_back(s[i]);
//         solve(s, i + 1, temp);        // take
//     }
//     int distinctSubseqII(string s) {
//         string temp = "";
//         solve(s, 0, temp);
//         return st.size();
//     }
// };

// Isliye brute force kaam nahi karega, hume formula-based DP chahiye.

Approach 2: DP + Formula (Optimized)
//NOTE:
// Agar string me koi character repeat na ho (sab unique), to
  total distinct subsequences = 2^n    (including{}).
                              =(2^n)-1 (excluding {})
  

// let's visualize this
//CASE 1: No duplicate in string 
// Isko samajhne ke liye dekho kaise subsequences double hote jaate hain:
//String :abc

Start:        {}                          → count = 1

i=0, 'a':     {}, {a}                     → count = 2
              (naya = purane sab + 'a' jodke)

i=1, 'b':     {}, {a}, {b}, {ab}          → count = 4
              (naya = purane sab + 'b' jodke)
  
i=2, 'c':     {}, {a}, {b}, {ab},
              {c}, {ac}, {bc}, {abc}      → count = 8

// Pattern dikha? Har naye character pe:
total(i) = 2 * total(i-1)

// Kyun? Kyunki naya character purane saare subsequences ke saath combine ho sakta hai, isliye count double ho jaata hai.

Base case: n = 0 (koi character nahi liya) → sirf {} hota hai → total = 1

//CASE: Duplicates in String
//Example: "baca"

{}                                          count=1
i=0 'b': {}, {b}                            count=2
i=1 'a': {}, {b}, {a}, {ba}                 count=4
i=2 'c': {}, {b}, {a}, {ba}, {c}, {bc}, {ac}, {bac}    count=8
i=3 'a'  {}, {b}, {a}, {ba},{c}, {bc}, {ac}, {bac}, {a}, {ba}, {aa}, {baa}, {ca}, {bca}, {aca}, {baca}      cnt={16} ->wrong
//{a}, {ba} ->repeated again 
  
i=3 'a': (2*8 = 16 milna chahiye tha, lekin...)
// Jab dusri baar 'a' aata hai, to wo wahi purane combinations phir se bana deta hai jo pehli baar 'a' ne banaye the:
  // Pehli baar 'a' ne banaya tha: {a}, {ba} (jab 'a' ko {} aur {b} ke saath combine kiya tha)
  // Dusri baar bhi 'a' wahi {a}, {ba} bana dega → DUPLICATE!

Duplicate hatane ka trick

// Jab bhi koi character doosri baar aaye, usse sirf unhi subsequences ke saath combine karo jo pichli baar ke baad bane the — 
// jo subsequences pichli baar ke sath use ho chuke the, unhe skip karo.

duplicate_count = solve(lastOccurrence_of_char - 1)
total = 2 * solve(i-1) - duplicate_count

// Yaha lastOccurrence(char) - 1 matlab: jab is character ko pehli baar dekha tha, uske just pehle wala total —
// wahi duplicates create hone ka reason hai.


  //when 'a' first time -> it combined with   i:0  {} {b}    
  //so we have to avoid it therefore 
  duplicate=solve(lastOccurenceof(a)-1)) //last bar 'a' 1 pe aya tha 
  =>solve(1-1)=solve(0) = 2 ({},{b}) //in do char ko frr se add ni krna to remove them
  total=total-duplicate

// Final DP Formula
int total= 2 * solve(i-1)
if(prev[i] != 0){     //char has appeared before 
  int duplicate = solve(prev[i]-1)
  total = total - duplicate
}

Answer = total-1   (empty {} ko final answer se minus karna)

// Yaha prev[i] = current character ko pichli baar kaha dekha tha (uska index)



//Time COmplexity: 0(n) ->each space visited once (stored in dp)
//Space Complexity: 0(n)

class Solution {
public:
    int MOD = 1e9 + 7;
    int dp[2001];
    vector<int> prev; // prev[i] = char at index i ko pehle kaha dekha tha

    int solve(int n) {
        if (n == 0) return dp[n] = 1;          // base case: empty subseq
        if (dp[n] != -1) return dp[n];          // already calculated

        int total = (2 * solve(n - 1)) % MOD;

        if (prev[n] != 0) {                     // agar ye char repeat hai
            int duplicates = solve(prev[n] - 1);
            total = (total - duplicates + MOD) % MOD;
        }
        return dp[n] = total;
    }

    int distinctSubseqII(string s) {
        int n = s.size();
        memset(dp, -1, sizeof(dp));
        prev.assign(n + 1, 0);

        vector<int> lastSeen(26, 0);
        for (int i = 1; i <= n; i++) {
            int idx = s[i - 1] - 'a';
            prev[i] = lastSeen[idx];   // pehle kaha dekha tha (0 agar pehli baar)
            lastSeen[idx] = i;         // ab update kardo
        }

        return (solve(n) - 1 + MOD) % MOD;   // -1 kiya kyunki {} nahi chahiye
    }
};


+MOD kyun likha?
// Kyunki total - duplicates negative ho sakta hai (mod arithmetic me), aur C++ me negative number ka % bhi negative aata hai. 
  // Isliye +MOD karke fir %MOD lagate hain taaki result hamesha positive rahe.


Appraoch 3:Bottom-Up / Tabulation
  // Yehi same logic hai, bas recursion ki jagah loop use kiya (fast + no stack overflow risk):
//yaad h we use n instead of i ealier it was because it make writing bottom up code easy - simply replace n with i below and solve with dp
class Solution {
public:
    int MOD = 1e9 + 7;

    int distinctSubseqII(string s) {
        int n = s.size();
        vector<int> prev(n + 1, 0);
        vector<int> lastSeen(26, 0);

        // step 1: har index ke liye "pichli baar ye char kaha tha" nikal lo
        for (int i = 1; i <= n; i++) {
            int idx = s[i - 1] - 'a';
            prev[i] = lastSeen[idx];
            lastSeen[idx] = i;
        }

        // step 2: dp table bottom-up bharo
        vector<int> dp(n + 1, 0);
        dp[0] = 1;   // {} empty subsequence

        for (int i = 1; i <= n; i++) {
            int total = 2 * dp[i - 1] % MOD;
            if (prev[i] != 0) {                 // duplicate hai
                int duplicate = dp[prev[i] - 1];
                total = (total - duplicate + MOD) % MOD;
            }
            dp[i] = total;
        }

        return (dp[n] - 1 + MOD) % MOD;   // {} hata do
    }
};
