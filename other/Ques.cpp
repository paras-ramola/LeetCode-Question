// Joseph is learning a digital logic subject which will be for his next
// semester. He usually tries to solve unit assignment problems before the lecture.
// Today he got one tricky question. The problem statement is “A positive integer
// has been given as an input. Convert decimal value to binary representation.
// Toggle all bits of it after the most significant bit including the most significant
// bit. Print the positive integer value after toggling all bits”
// .
// Constraints : 1<=N<=100
// Example 1 – Input : 10 -> Integer
// Output : 5 -> result- Integer


  // Approach 1
#include <cmath>
int main()
{
    int n;
    cin >> n;

    cout << "Input:" << n << endl;

    int num = 0;
    int power = 0;
    while (n > 0)
    {
        int lsb = n & 1;        // Extract LSB
        int bit = 1 - lsb;     // Toggle bit
        num += bit * pow(2, power); // Build new number
        n = n >> 1;            // Shift right
        power++;
    }
    cout << num << endl;
}

// Approach 2:


    while (n > 0)
    {
        int lsb = n & 1;          // extract bit
        int bit = 1 - lsb;       // toggle bit
        num |= (bit << power);   // set toggled bit
        n >>= 1;                 // shift right
        power++;
    }






// Q3) Find the string from a given input binary array, where a set of 4 binary
// digits represented a character from ‘a’ to ‘p’
// . For example:
// Input: 00110101
// Output: de


int main()
{
    // Input binary array
    // Every group of 4 bits represents one character
    vector<int> arr = {0, 0, 1, 1, 0, 1, 0, 1};

    // String to store final decoded characters
    string res = "";

    // Process the array in steps of 4 bits
    for (int i = 0; i < arr.size(); i += 4)
    {
        int num = 0;  // Decimal value of current 4-bit group

        // Convert 4 binary digits into a decimal number
        for (int j = 0; j < 4; j++)
        {
            // Left shift existing bits and add the next bit
            num = (num << 1) | arr[i + j];
        }

        // Map number (0–15) to characters 'a'–'p'
        char ch = 'a' + num;

        // Append character to result string
        res.push_back(ch);
    }

    // Print the final decoded string
    cout << res;
}
