// Approach 1:0(n)
// Check if a number is divisible by any number less than itself except '1'

bool isPrime(int n) {
    if (n <= 1)
        return false;
    // Check divisibility from 2 to n-1
    for (int i = 2; i < n; i++)
        {
            if (n % i == 0) return false;
        }

    return true;
}

// Approach 2: 
// T.C:0(sqrt(n))

//  If a number n is not prime, it must have a factor ≤ √n
// Why?
// Factors come in pairs
// Example: 36 = 6 × 6, 48 = 6 × 8
// If both factors were greater than √n, their product would exceed n
// So:  We only need to check from 2 to √n

bool isPrime(int n) {
    if (n <= 1) return false;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}
