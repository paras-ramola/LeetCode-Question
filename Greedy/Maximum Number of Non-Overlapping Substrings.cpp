//Subaaray ->mtlb dp/reccursion  bahut km chances
//we can try sliding window/two pointer/greedy when subaary

//Appraoch:GREEDY

// Time Complexity: O(2n) ->Hr char ko do baar traverse kiya
// Space Complexity: O(1)  -> only 26 characters are used
class Solution {
public:

    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        vector<string> res; // Stores the final valid substrings


        vector<int> startIdx(26, -1);//first position where a  char appears
        vector<int> endIdx(26, -1);//last position where a  char appears

        // Find the first and last occurrence of every char
        for (int i = 0; i < n; i++) {
            int idx = s[i] - 'a';

            // First time we see this character -> store its start
            if (startIdx[idx] == -1) {
                startIdx[idx] = i;
            }

            // Keep updating -> finally becomes the last occurrence
            endIdx[idx] = i;
        }

        // Start position of the previously selected substring.
        // We use this to make sure the new substring does not overlap.
        int lastSubstrIdx = INT_MAX;

        // Traverse from RIGHT to LEFT.
        // This helps us find smaller valid substrings first.
        for (int i = n - 1; i >= 0; i--) {

            int idx = s[i] - 'a';

            // We only try to create a substring when we are
            // standing at the FIRST occurrence of a character.
            if (i == startIdx[idx]) {

                int start = startIdx[idx];
                int end = endIdx[idx];

                bool isValid = true;

                // Check every char inside [start, end].
                // If we find another char whose complete range
                // cannot fit inside our current substring,  then this substring is invalid.
                for (int j = start; j <= end; j++) {

                    int currStart = startIdx[s[j] - 'a'];
                    int currEnd = endIdx[s[j] - 'a'];

                    /*
                        Two things can make the substring invalid:

                        1. currStart < start
                           -> This char appeared BEFORE our start.
                           -> So we would need to extend the substr to the left.

                        2. currEnd > lastSubstrIdx
                           -> This char appears after the starting
                              point of the previously selected substr.
                           -> That would cause overlap.
                    */

                    if (currStart < start || currEnd > lastSubstrIdx) {
                        isValid = false;
                        break;
                    }

                    // If this char continues beyond our current end,
                    // extend the substring to include its last occurrence.
                    if (currEnd > end) {
                        end = currEnd;
                    }
                }

                // If every character completely fits inside the range,
                // we have found a valid substring.
                if (isValid) {

                    // Create substring from start to end
                    string temp = s.substr(start, end - start + 1);

                    // Add it to our answer
                    res.push_back(temp);

                    // Remember where this substring starts.
                    // Future substrings must come completely before this.
                    lastSubstrIdx = start;
                }
            }
        }

        return res;
    }
};

