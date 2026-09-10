
Appraoch 1:  Recursion — TLE
// Time Complexity: O(2^(m+n)) worst case (har `*` par 2 choices — take/skip — banta hai ek binary tree)
// **Space:** `O(m+n)` recursion stack
// **Problem:** same `(i,j)` states baar baar solve ho rahe hain → overlapping subproblems → isliye TLE

class Solution {
public:
    bool solve(string& s, string& p, int i, int j) {
        // s poora consume ho gaya
        if (i == s.size()) {
            // p me bache hue sab '*' hone chahiye (kyunki * khaali bhi match karta hai)
            while (j < p.size() && p[j] == '*') j++;
            return j == p.size();
        }
        // s me characters bache hain but p khatam ho gaya -> match impossible
        if (j >= p.size()) return false;

        if (s[i] == p[j] || p[j] == '?') {
            // dono ek step aage badhao
            return solve(s, p, i + 1, j + 1);
        } else if (p[j] == '*') {
            // * ko ek character "le lo" (s aage badhao, * wahi rakho)
            bool take = solve(s, p, i + 1, j);
            // * ko "khaali" treat karo (s wahi rakho, p aage badhao)
            bool skip = solve(s, p, i, j + 1);
            return take || skip;
        }
        return false; // mismatch
    }

    bool isMatch(string s, string p) {
        return solve(s, p, 0, 0);
    }
};
```


Appraoch 2: Top-Down DP (Memoization)
  **Time Complexity:** `O(m*n)` — kyunki total distinct states `(i,j)` = `m*n`, har state O(1) me solve (recursive calls excluding)
**Space:** `O(m*n)` dp array + `O(m+n)` recursion stack

class Solution {
public:
    int dp[2001][2001]; // dp[i][j] = isMatch(s[i:], p[j:]) ka answer (-1 = not computed)

    bool solve(string &s, string &p, int i, int j) {
        if (i == s.size()) {
            while (j < p.size() && p[j] == '*') j++;
            return dp[i][j] = (j == p.size());
        }
        if (j == p.size()) return dp[i][j] = false;

        if (dp[i][j] != -1) return dp[i][j]; // already computed -> return cached

        if (s[i] == p[j] || p[j] == '?') {
            return dp[i][j] = solve(s, p, i + 1, j + 1);
        }
        if (p[j] == '*') {
            bool take = solve(s, p, i + 1, j);
            bool skip = solve(s, p, i, j + 1);
            return dp[i][j] = take || skip;
        }
        return dp[i][j] = false;
    }

    bool isMatch(string s, string p) {
        memset(dp, -1, sizeof(dp));
        return solve(s, p, 0, 0);
    }
};




---

## 3) Bottom-Up DP (Tabulation) —

// **Time Complexity:** `O(m*n)` — dono loops
// **Space Complexity:** `O(m*n)` for dp table (isko `O(n)` tak optimize kar sakte ho, kyunki `dp[i]` row sirf `dp[i-1]` row pe depend karti hai — 1D rolling array use karke)
// abse safe hai large inputs (m,n ~ 2000) ke liye kyunki recursion stack overflow ka risk nahi hota.


// dp array ka matlab
// dp[i][j] = true agar s ke pehle i characters (s[0..i-1])
//            match karte hain p ke pehle j characters (p[0..j-1]) se
// Yaani `dp[i][j]` "prefix s[0..i)" vs "prefix p[0..j)" ka match batata hai.

// Base cases (sबसे important part jo confusing lagta hai)
// dp[0][0] = true → Khaali string, khaali pattern → obviously match.

// **Pehli row: `dp[0][j]` (s khaali hai, p me kuch characters hain)**

for (int i = 1; i <= n; i++) {
    if (p[i - 1] == '*') {
        dp[0][i] = dp[0][i - 1];
    }
}

// → Agar s khaali hai, to p sirf tab match karega jab p ke saare characters `*` hon (kyunki `*` khaali sequence match kar sakta hai, 
// but `?` ya normal char nahi kar sakta).
// → Isliye: agar current char `*` hai AND uske pehle wala part (`dp[0][i-1]`) bhi match kar raha tha (sab `*` tha), to ye bhi match karega.
// → Jaise hi ek non-`*` character aata hai beech me, us point se aage sab `dp[0][j] = false` reh jaayega (default value already false hai, so kuch karna nahi padta).

// Pehla column: `dp[i][0]` (p khaali hai, s me characters hain)**
```cpp
for (int i = 1; i <= m; i++) {
    dp[i][0] = false;
}
// → Pattern khaali hai but string me characters bache hain → kabhi match nahi ho sakta.
// (Vector already `false` se initialize hai, ye loop technically redundant hai but clarity ke liye achha hai)

### Main transition (dono loops ke andar)

```cpp
for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
        // Case 1: current characters match, ya p me '?' hai
        if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
            // to answer depend karta hai dono se ek-ek peeche wale prefix par
            dp[i][j] = dp[i - 1][j - 1];//agr prev cahrs match krte h +plus curr match kr rhe h ->then true
        }

        // Case 2: current pattern char '*' hai
        if (p[j - 1] == '*') {
            // '*' ko ek s-character "consume" karne do (dp[i-1][j] -> * ne le liya, aage bhi try karega)
            // '*' ko khaali treat karo (dp[i][j-1] -> * ne kuch nahi liya, pattern aage badh gaya)
            dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
        }
    }
}
```

// **Har cell `dp[i][j]` khud se chote cells (`dp[i-1][j-1]`, `dp[i-1][j]`, `dp[i][j-1]`) se banta hai** —
// jo already table me pehle calculate ho chuke hain (kyunki hum i,j ko increasing order me chala rahe hain, i.e. "bottom-up").

