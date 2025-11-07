// Appraoch 1: Reccursion
// T.C:0(log n)


class Solution {
public:
    double solve(double x, long long n) {
        if (n == 0)
            return 1;
        if (n == 1)
            return x;

        double multiple = solve(x, n / 2); // reccursively find x power half of n

        double ans = multiple * multiple; // x^n= x^(n/2)*x^(n/2)

        if (n % 2 != 0) { // if odd
            ans *= x;     // multiply x
        }

        return ans;
    }
    double myPow(double x, int n) {
        long long exp = n;

        if (exp < 0) {
            x = 1 / x;
            exp = -exp;
        }

        return solve(x, exp);
    }
};


//Approach 2: Bitwise
// T.C:0(log n)

// Eg: if (x)^13 
// Binary of 13-> 1101    ,   x^13 = x^8*x^4*x^1

class Solution {
public:
//Time complexity 0(logn) ->because of pwr = pwr >> 1 divides pwr by 2

    double myPow(double x, int n) {

        double ans = 1.0;
        long long pwr = n; // Use long long to handle INT_MIN case safely

        if (pwr < 0) {
            x = 1 / x;  // covert(x)^-n to (1/x)^n
            pwr = -pwr; // make pwr positvie
        }

        while (pwr > 0) {
            if (pwr & 1) { // if odd
                ans = ans * x;
            }
            x = x * x;
            pwr = pwr >> 1; // shift right by 1 (divide by 2(floor division))
        }

        return ans;
    }
};


//why use lon long
// The value of INT_MIN = -2,147,483,648 (-2^31) but the positive side of int only goes up to 2,147,483,647.
// So, trying to make int =-INT_MIN overflows the range of int.





