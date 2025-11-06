
// First Try :-> 3720. Lexicographically Smallest Permutation Greater Than Target


// Approach : BackTraking +Pruning
// T.C: Worst Case:(0(n/2)!)
// Practical :O(26 × n/2)
// Each recursive call only processes up to 26 choices, and depth is n/2.

// Approach Link: https://leetcode.com/problems/lexicographically-smallest-palindromic-permutation-greater-than-target/solutions/7319872/easy-to-understand-backtracking-cpp-begi-i98y

class Solution {
public:
    int n;          
    string ans;     
    string mid = ""; // middle char (if odd length)

    // Recursive helper to build the left half of the palindrome
    bool solve(vector<int>& cnt, string& target, string& path, bool& big) {
        // Base case: when we’ve built half of the palindrome
        if ((int)path.size() == n / 2) {
            string left = path;
            string right = path;
            reverse(right.begin(), right.end());
            
            // Build full palindrome
            string perm = left + mid + right;

            // Check if it’s greater than target
            if (perm > target) {
                ans = perm;
                return true;  // stop at first valid (smallest) palindrome
            }
            return false;
        }

        int i = path.size();        // current position
        char targetCh = target[i];  // corresponding target character

        // Try each possible letter from 'a' to 'z'
        for (int c = 0; c < 26; c++) {
            if (cnt[c] == 0)
                continue;  // skip unavailable letters

            char currCh = 'a' + c;

            // If not yet bigger than target, we can’t pick smaller char
            if (!big && currCh < targetCh)
                continue;

            // Choose current letter
            path.push_back(currCh);
            cnt[c]--;

            // Once we exceed target at any point, the rest can be smallest
            bool newBig = (big || currCh > targetCh);

            // Continue building
            if (solve(cnt, target, path, newBig))
                return true;
            // if not found a valid permutaion :Backtrack

            // Backtrack
            path.pop_back();
            cnt[c]++;
        }
        return false;
    }

    string lexPalindromicPermutation(string s, string target) {
        n = s.size();
        ans = "";
        mid = "";

        vector<int> cnt(26, 0);
        for (char ch : s)
            cnt[ch - 'a']++;

// We only need to construct half palindrome->other half is just reverse
// so decrease the cnt[char] by half
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 != 0) {//if odd char 
                if (mid.empty()) {
                    mid = char('a' + i); // one allowed middle char
                } else {
                    // More than one odd count → cannot form palindrome
                    return "";
                }
            }
            cnt[i] /= 2; // we only need half for the left side
        }

        bool big = false;
        string path;

        // Start recursive construction
        solve(cnt, target, path, big);

        return ans;
    }
};
