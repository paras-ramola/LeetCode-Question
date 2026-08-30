//Approach 1  : Backtracking 
// make all valid combination for len(2*n) and push only valid ones

//T.C:
// final len of combination ->2*n 
// for every place there are two option -> '(', ')'
// so => 0(2^(2n))
//isValid function takes len of string time ->0(2n)
//T.C: 0(2n * 2^(2n))


//S.C:
//Max depth ->len of combination ->0(2n)
// S.C:0(2n)


class Solution {
public:

    vector<string> res;
    // Checks whether a given parentheses string is valid
    bool isValid(string str) {

        int cnt = 0;

        for (auto ch : str) {
            if (ch == '(') {
                cnt++;
            }
            else {
                cnt--;
            }
            if (cnt < 0) {
                return false;
            }
        }
        return cnt == 0;
    }


    void solve(int n, string curr) {

        // Every valid answer must contain exactly n pairs,
        // so its total length must be 2*n.
        if (curr.size() == 2 * n) {

            // Check whether the generated string is valid.
            if (isValid(curr)) {
                res.push_back(curr);
            }

            return;
        }


        // OPTION 1: Add '('
        curr.push_back('(');
        solve(n, curr);
        // Backtrack: Remove the '(' so that we can try another option.
        curr.pop_back();

        // OPTION 2: Add ')'
        curr.push_back(')');
        solve(n, curr);
        // Backtrack:  Remove the ')' before returning.
        curr.pop_back();
    }


    vector<string> generateParenthesis(int n) {

        string curr = "";

        // Start building the string from empty.
        solve(n, curr);

        return res;
    }
};




// Approach 2 : Optimized Backtracking

// T.C:
// Here we cant say : O(2^(2n))
// Why?   Because in our optimized backtracking, every position does NOT always have 2 choices.
// Rule:
//   add '('  →  when open < n
//   add ')'  →  when close < open

// ===================== CATALAN NUMBER =====================

// The number of VALID parentheses combinations
// for n pairs is given by the nth Catalan number:
//
//        1       (2n)!
// Cn =  ----- * ---------
//       n + 1    n! * n!
//
// Or:
//
// Cn = 1/(n+1) * (2n choose n)
//
// Examples:
// n = 1 -> 1
// n = 2 -> 2
// n = 3 -> 5
// n = 4 -> 14
// n = 5 -> 42
//
// Our recursion generates these valid combinations.
//
// Each valid combination has length 2*n.
// Therefore, we need O(n) work per valid combination.
//
// So:
// Time Complexity = O(Cn * n),  where Cn = nth Catalan number.
//
// Equivalently: Time Complexity = O(n * (2n choose n))

// S.C:
// Max depth ->len of combination ->0(2n)
//  S.C:0(2n)

class Solution {
public:

    vector<string> res;

    void solve(int n, int open, int close, string curr) {

        // Every valid answer must contain exactly n pairs,
        // so its total length must be 2*n.
        if (curr.size() == 2 * n) {
            res.push_back(curr);
            return;
        }

        // OPTION 1: Add '('
        // We can add '(' only if we haven't used all n opening brackets.
        if (open < n) {

            curr.push_back('(');
            solve(n, open + 1, close, curr);
            // Backtrack: Remove '(' before trying the next option.
            curr.pop_back();
        }

        // OPTION 2: Add ')'
        // We can add ')' only when there is an  unmatched '(' available.
        if (close < open) {

            curr.push_back(')');
            solve(n, open, close + 1, curr);
            // Backtrack: Remove ')' before returning.
            curr.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {

        string curr = "";
        solve(n, 0, 0, curr);

        return res;
    }
};
