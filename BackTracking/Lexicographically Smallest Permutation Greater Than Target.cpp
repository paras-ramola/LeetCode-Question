
// INTUTION: Find all permutaion (using Backtracking) and return the valid one -> 0(n!) ->TLE



/
// Approach : Backtracking +prunning( to resuce T.C)
// T.C: In the worst case, we may explore all permutations, but pruning significantly reduces the search space.
// Practically, it is much faster than O(n!) because we skip branches that cannot exceed target.
// The exact worst-case is difficult to express, but the effective complexity is much less than O(n!).

Approach Link:( https://leetcode.com/problems/lexicographically-smallest-permutation-greater-than-target/solutions/7285227/backtracking-pruning-cpp-easy-to-underst-6522 )

class Solution {
public:
    int n;        
    string ans;     

    // Recursive function to build the permutation
    bool solve(vector<int>& cnt, string& target, string& path, bool& big) {
        // Base case: if we've built a full string
        if ((int)path.size() == n) {
            // If we've already become bigger than target somewhere
            if (big) {
                ans = path;  // Found the smallest valid permutation
                return true;
            }
            return false;
        }

        int i = path.size();       // curr idx we're filling
        char targetCh = target[i]; // Target char at this idx

        // Try all possible chars in lexicographical order
        for (int c = 0; c < 26; c++) {
            if (cnt[c] == 0) continue;  // Skip if this char is not available

            char currCh = 'a' + c;

            // If we haven't yet exceeded target, we must ensure current char >= target char
            if (!big && currCh < targetCh)
                continue;

            // Choose this character
            path.push_back(currCh);
            cnt[c]--;

            // newBig becomes true if we have already placed a bigger char earlier
            // or if the current char > target char
            bool newBig = (big || currCh > targetCh);

            // build the permutaion  further 
            if (solve(cnt, target, path, newBig))
                return true;  // Stop when the first valid result is found

                // if not found a valid permutaion:backtack

            // Backtrack: undo the choice
            path.pop_back();
            cnt[c]++;
        }

        // No valid permutation found for this configuration
        return false;
    }

    string lexGreaterPermutation(string s, string target) {
        n = s.size();
        ans = "";

        // Count frequency of each character in s
        vector<int> cnt(26, 0);
        for (char ch : s)
            cnt[ch - 'a']++;

        bool big = false;   // Whether we’ve already exceeded target
        string path = "";   // To build the result

        solve(cnt, target, path, big);
        return ans;         
    }
};
