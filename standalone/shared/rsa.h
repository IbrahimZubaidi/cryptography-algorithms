#include"../shared/math.h"

// Input RSA key.
void irsak (vector<long long> &pu, vector<long long> &pr)
{
    long long q, p, n, r, e, d;
    // Select values of p, q, two prime numbers
    cout << "Select value of (p) prime number: ", cin >> p; 
    while (!is_prime(p)) cout << "(p) must be prime number: ", cin >> p; // Prompt user for (p) if not prime.
    cout << "Select value of (q) prime number: ", cin >> q;
    while (!is_prime(q)) cout << "(q) must be prime number: ", cin >> q; // Prompt user for (q) if not prime.
    n = p * q; // Find value of n = p * q.
    r = (p - 1) * (q - 1); // Find value Ф = (p-1) * (q-1).
    cout << "Select (e) such that (e) Is relatively prime to (r) = " << r << " and less than (r): ", cin >> e; // Find value e, with gcd (Ф (n), e) = 1; 1< e < Ф (n).
    while (!(gcd(r, e) == 1) || !(1 < e && e < r) || !(e * eea(e, r) % r == 1)) cout << "(e) must be relatively prime to (r) = " << r << " and less than (r): ", cin >> e; // Prompt user for (e) if not relatively prime to (r) and less than (r).
    d = eea(e, r); // Find value of d ≡ e-1 mod Ф(n).
    pu = {e, n}, pr = {d, n};

    return;
}

// RSA key.
void rsak (vector<long long> &pu, vector<long long> &pr)
{
    srand(time(nullptr));
    long long q, p, n, r, e, d;
    // Select values of p, q, two prime numbers
    do { p = rand(); } while (!is_prime(p) || p < 0);
    do { q = rand(); } while (!is_prime(q) || q < 0);
    n = p * q; // Find value of n = p * q.
    r = (p - 1) * (q - 1); // Find value Ф = (p-1) * (q-1).
    do { e = rand(); } while (!(gcd(r, e) == 1) || !(1 < e && e < r) || !(e * eea(e, r) % r == 1)); // Find value e, with gcd (Ф (n), e) = 1; 1< e < Ф (n).
    d = eea(e, r); // Find value of d ≡ e-1 mod Ф(n).
    pu = {e, n}, pr = {d, n};

    return;
}

// RSA (encryption and Decryption).
vector<long long> rsa (vector<long long> t, vector<long long> p)
{
    vector<long long> text = {};
    int s = t.size();
    for (int i = 0; i < s; i++)
    {
        if (int(t[i]) >= p[1]) return {}; // Check if byte is decryptable.
        text.push_back(pow_mod(t[i], p[0], p[1]));
    }
    
    return text;
} 