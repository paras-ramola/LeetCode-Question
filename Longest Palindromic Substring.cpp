class Solution {
public:


Approach 1 : Iteration
// Time Complexity: O(n^3)
// Outer loop runs O(n) times.
// For each i, the inner loop can run O(n) times.
// For every (i, j), the while loop can take O(n) time  to check whether the substr is a palindrome.
// Therefore: O(n) * O(n) * O(n) = O(n^3)

// Space Complexity: O(n)


    string longestPalindrome(string s) {

        int n = s.size();

        // If string has only one character, it is already a palindrome
        if (n == 1) {
            return s;
        }

        string ans = "";

        // Choose starting index of substring
        for (int i = 0; i < n; i++) {

            // Choose ending index, starting from the largest
            for (int j = n - 1; j >= i; j--) {

                // Two pointers: one from start and one from end
                int x = i;
                int y = j;

                // Length of current substring
                int charLen = j - i + 1;

                // Check if the substring is a palindrome
                while (x < y && s[x] == s[y]) {
                    x++;
                    y--;
                }

                // x >= y means the substring is a palindrome
                // Check if it is longer than our current answer
                if (x >= y && ans.size() < charLen) {

                    // Store the current palindrome
                    ans = s.substr(i, charLen);

                    // Since j starts from the largest,
                    // this is the longest palindrome for this i
                    break;
                }
            }
        }

        return ans;
    }
};


Approach 2: Reccusrion
  class Solution {
public:
    //RECCURSION

    //check string(i,j) is valid
    bool checkPalin(int i, int j, string& s) {
        if (i >= j)//reached end
            return true;

        if (s[i] == s[j]) {
            return checkPalin(i+1, j-1, s);
        }

        return false;
    }
    string longestPalindrome(string s) {
        int n = s.size();

        int maxLen = INT_MIN;

        string ans = "";

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (checkPalin(i, j, s)) {//if the substr(i,j) is a valid palindrome
                    if (maxLen < (j - i + 1)) {//check if its len is new  max
                        ans = s.substr(i, (j - i + 1));//store the new largest valid substr
                        maxLen = (j - i + 1);//update the maxLen
                    }
                }
            }
        }
        return ans;
    }
};




Apprach 3 : Memoiztion


  class Solution {
public:
    // Time Complexity: O(n^2)
    // There are O(n^2) possible substrings.
    // Each isPalin(i, j) state is calculated only once bcz of memoization.
    //
    // Space Complexity: O(n^2)
    // DP table t[1001][1001] stores results for all pairs (i, j).
    // Recursion stack can take O(n) space.

    int t[1001][1001];
    bool isPalin(string& str, int i, int j) {

        if (i >= j) {
            return true;
        }
        if (t[i][j] != -1) {
            return t[i][j];
        }
        if (str[i] != str[j]) {
            return t[i][j] = false;
        }

        //check the remaining inner substr
        return t[i][j] = isPalin(str, i + 1, j - 1);
    }
    string longestPalindrome(string s) {

        int n = s.size();

        memset(t, -1, sizeof(t));
        if (n == 1) {
            return s;
        }

        int maxLen = 0;
        int sp = -1;

        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                //Len of curr substr
                int strLen = j - i + 1;
                if (isPalin(s, i, j) && maxLen <= strLen) {
                    maxLen = strLen;
                    sp = i;
                }
            }
        }

        return s.substr(sp, maxLen);
    }
};

Approach 3:Bottom Up

class Solution {
public:
    // BOTTOM-UP

    string longestPalindrome(string s) {
        int n = s.size();

        bool t[n + 1][n + 1]; // static 2D array

        memset(t, false, sizeof(t)); // intialize the 2D arr 't' with 'false'

        int maxLen = INT_MIN;

        string ans = "";

        // check for every len at index i = valid or not

        for (int Len = 1; Len <= n; Len++) {
            for (int i = 0; (i + Len - 1) < n; i++) {
                int j = (i + Len - 1);
                if (Len == 1) {//single char is a valid Palindrome
                    t[i][j] = true;
                    maxLen = Len;
                    ans = s.substr(i, Len);
                } else if (Len == 2) {
                    if (s[i] == s[j]) {//if both chars match
                        t[i][j] = true;
                        if (maxLen < Len) {//if new  longest palindromic substr is found
                            maxLen = Len;
                            ans = s.substr(i, Len);
                        }
                    }
                } else {//if Len>2
                    if (s[i] == s[j] && t[i + 1][j - 1] == true) {
                        t[i][j] = true;
                        if (maxLen < Len) {//if new  longest palindromic substr is found
                            maxLen = Len;
                            ans = s.substr(i, Len);
                        }
                    }
                }
            }
        }

        return ans;
    }
};
