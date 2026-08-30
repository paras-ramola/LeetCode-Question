// Rules: 
1.'.'->mathces any single char
2.'*'->matches zero or more char of preceding element
3.'*' cannot come without a preceding char. Eg: p= a*b ->correct , p=a**b -> wrong, p=*b ->wrong

// Edge Case Examples
//1. s = "ab", p = ".*"
  
// s[0] = 'a', p[0] = '.'
// '.' can match any character, so '.' matches 'a'.

//IMPORTANT - '*' is never taken alone ->always with preceeding char , here ->'.*'
  
// Now p[1] = '*'
// '*' means: repeat the previous character ('.') zero or more times.

// Since '.' can match any character,
// '.*' can match any sequence of characters.
// so here we take '.' as b and '.*' as b also
  //VALID

  //2. s = "aab", p = "c*a*b"
  //here 'c*' -> ""
  // a*b -> aab
  //valid


// Approach 1: Reccusion
  class Solution {
public:
    // T.C : 0(2^(m+n))
    // S.C : O(m + n)
    bool solve(int i, int j, string& s, string& p) {

        // If we have completely processed the pattern,
        // then string must also be completely processed.
        if (j == p.length()) {
            return i == s.length();
        }

        // Check whether current characters match.
        // '.' can match any single character.
        bool first_char_match = false;

        if (i < s.length()) {
            first_char_match = (s[i] == p[j] || p[j] == '.');
        }

        // Check if the NEXT character in pattern is '*'.
        // Example: a* -> '*' means we can use 'a' 0 or more times.
        // we take * with its preceeding char always
        if (j + 1 < p.length() && p[j + 1] == '*') {

            // OPTION 1: Don't use '*' : Skip "x*" completely.
            // Example:  p = "a*b"
            // We decide to use 'a' zero times,
            // so move past "a*" ->j+2 .
            bool not_take_astrik = solve(i, j + 2, s, p);

            // OPTION 2: Use '*'
            // If current character matches,
            // consume one character from s (i+1),
            // but stay at the same pattern position bcz we want to use the 'x*'
            // again . This allows '*' to match multiple characters.
            bool take_astrik = first_char_match && solve(i + 1, j, s, p);

            // Either option can give a valid match.
            return not_take_astrik || take_astrik;
        }

        // If current characters match and there is no '*',
        // move both pointers forward.
        // Match one character and move ahead.
        if (first_char_match) {
            return solve(i + 1, j + 1, s, p);
        }

        // Current characters don't match.
        return false;
    }

    bool isMatch(string s, string p) { return solve(0, 0, s, p); }
};



//Approach 2: Reccusion +Memoization


    //  T.C : 0(mn)->all possibel state stored in dp (m*n)
    //  S.C : O(mn)
class Solution {
public:


    vector<vector<int>> dp;
    bool solve(int i, int j, string& s, string& p) {

        if (j == p.length()) {
            return i == s.length();
        }

        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        bool first_char_match = false;

        if (i < s.length()) {
            first_char_match = (s[i] == p[j] || p[j] == '.');
        }

        if (j + 1 < p.length() && p[j + 1] == '*') {

            bool not_take_astrik = solve(i, j + 2, s, p);

            bool take_astrik = first_char_match && solve(i + 1, j, s, p);

            // Either option can give a valid match.
            return dp[i][j] = not_take_astrik || take_astrik;
        }

        if (first_char_match) {
            return dp[i][j] = solve(i + 1, j + 1, s, p);
        }

        return dp[i][j] = false;
    }

    bool isMatch(string s, string p) {
        dp.resize(s.size()+1, vector<int>(p.size()+1, -1));
        return solve(0, 0, s, p);
    }
};
