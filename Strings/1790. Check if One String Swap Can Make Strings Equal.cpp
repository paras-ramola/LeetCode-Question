
//Approach 1:

class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {

        // If lengths differ, it's impossible to make them equal by one swap
        if (s1.size() != s2.size()) {
            return false;
        }

        int mismatchCount = 0; // Count how many characters differ
        char firstMismatchS1,
            firstMismatchS2; // Store first mismatch characters

        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] != s2[i]) {
                mismatchCount++;

                // More than 2 mismatches → cannot fix with one swap
                if (mismatchCount > 2) {
                    return false;
                }

                // When we find the second mismatch, check if swapping can fix
                // it
                if (mismatchCount == 2) {
                    if (s1[i] != firstMismatchS2 || s2[i] != firstMismatchS1) {
                        return false; // Swap doesn’t match
                    }
                }

                // Store the first mismatch characters for later comparison
                if (mismatchCount == 1) {
                    firstMismatchS1 = s1[i];
                    firstMismatchS2 = s2[i];
                }
            }
        }

        // If exactly one mismatch, cannot be fixed by swapping
        // If 0 or 2 mismatches, it's fine
        return mismatchCount != 1;
    }
};

//Approach 2:

class Solution {
public:
    bool areAlmostEqual(string str1, string str2) {
        // If lengths are not equal, strings can’t be made equal with one swap
        if (str1.size() != str2.size()) {
            return false;
        }

        vector<int> mismatchIndices; // Store indices where characters differ

        // Find all positions where characters in str1 and str2 don't match
        for (int i = 0; i < str1.size(); i++) {
            if (str1[i] != str2[i]) {
                mismatchIndices.push_back(i);
            }

            // If more than 2 mismatches, cannot fix with a single swap
            if (mismatchIndices.size() > 2) {
                return false;
            }
        }

        // Case 1: No mismatches → strings are already equal
        if (mismatchIndices.size() == 0) {
            return true;
        }

        // Case 2: Exactly two mismatches → try swapping the mismatched characters
        if (mismatchIndices.size() == 2) {
            swap(str1[mismatchIndices[0]], str1[mismatchIndices[1]]);
        }

        // After swap, check if strings are now equal
        return str1 == str2;
    }
};
