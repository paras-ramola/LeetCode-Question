// Palindrome same number original & reverse


//Approach 1: Math approach (reverse the number)
// T.C: O(d) where d = number of digits= log₁₀(n)
// S.C:0(1)
class Solution {
public:
    bool isPalindrome(int x) {

        // Step 1: Negative numbers are never palindrome
        if (x < 0)
            return false;

        // Copy the number (to keep original safe)
        int original = x;
        long long reversed = 0;

        // Step 2: Reverse the number
        while (x > 0) {
            int lastDigit = x % 10;        // get last digit
            reversed = reversed * 10 + lastDigit; // add digit to reversed number
            x = x / 10;                    // remove last digit
        }

        // Step 3: Compare original and reversed
        return reversed == original;
    }
};

// Approach 2:
// T.C: O(d) where d = number of digits= log₁₀(n)
// S.C:0(1)
class Solution {
public:
    bool isPalindrome(int x) {

        // Step 1: Convert number to string
        string str = to_string(x);

        // Step 2: Make a copy and reverse it
        string rev = str;
        reverse(rev.begin(), rev.end());

        // Step 3: Compare original string with reversed string
        return str == rev;
    }
};

