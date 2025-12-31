// Anagram -> An anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
// using all the original letters exactly once.


// Approach 1: Sorting
// T.C:0(n * log n)
class Solution {
public:
    bool isAnagram(string s, string t) {
        sort(s.begin(), s.end());
        sort(t.begin(), t.end());
        return s == t;
    }
};

// Approach 2:
// T.C;0(n), S.C:0(1)
class Solution {               
public:
    bool isAnagram(string s, string t) {
        if(s.length() != t.length()){
            return false;
        }
        int arr[26] = {0};
        for(int i=0; i<s.length(); i++){
            arr[s[i]-'a']++;
            arr[t[i]-'a']--;
        }
        for(int i=0; i<26; i++){
            if(arr[i] != 0){
                return false;
            }
        }
        return true;
    }
};
