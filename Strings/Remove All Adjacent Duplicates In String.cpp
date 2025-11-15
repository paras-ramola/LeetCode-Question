
// Approach 1:
class Solution {
public:
    string removeDuplicates(string s) {
        string ans;

        for (int i = 0; i < s.size(); i++) {
            //if same adj elment is present already
            if (!ans.empty() && ans.back() == s[i]) {
                ans.pop_back();
            } else {
                ans.push_back(s[i]);
            }
        }

        return ans;
    }
};


// Approach 2:

class Solution {
public:
    string removeDuplicates(string s) {

        int i = 0;

        while (i < s.size()) {

            if (s[i] == s[i + 1]) {
                s.erase(i, 2);
                i = 0;
            } else {
                i++;
            }
        }

        return s;
    }
};
