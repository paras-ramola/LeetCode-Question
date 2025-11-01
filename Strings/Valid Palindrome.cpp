// Approach 1
// T.C:0(n),S.C:0(1)

class Solution {
public:
    bool isPalindrome(string s) {
        
        int start =0;
        int end = s.size() - 1;
        while(start <= end) {
            if(!isalnum(s[start])) {start++; continue;}
            if(!isalnum(s[end])) {end--; continue;}
            if(tolower(s[start]) != tolower(s[end])) return false;

            else{
                start++;
                end--;
            }
        }

        return true;
        
    }
};

//Approach 2:Using rev
// T.C:0(n),S.C:0(n)
class Solution {
public:
    bool isPalindrome(string s) {

   
        string temp;

        for(int i=0;i<s.size();i++){
            if(isalnum(s[i])){

                temp.push_back(tolower(s[i]));
            }
        }
        
        string rev=temp;
        reverse(rev.begin(),rev.end());

        return rev==temp;
    }
};
// Approach 3:Using stack

//Approach :Reccursion
// T.C:0(n),S.C:0(n)

class Solution {
public:
    bool check(string& s, int start, int end) {
        if (start >= end) {
            return true;
        }
        while (start < end && !isalnum(s[start]))
            start++;
        while (start < end && !isalnum(s[end]))
            end--;

        if (start < end && tolower(s[start]) != tolower(s[end])) {
            return false;
        }

        return check(s, start + 1, end - 1);
    }
    bool isPalindrome(string s) { return check(s, 0, s.size() - 1); }
};
