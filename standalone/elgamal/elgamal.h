#include"../shared/math.h"

// Input Elgamal key.
void iek (vector<long long> &pu, vector<long long> &pr) 
{
    long long p, a, x, d, y = 0;
    cout << "Choose a random prime number (P): ", cin >> p; // Choose a random prime number namely (P) as public value.
    while (!is_prime(p)) cout << "(P) must be a prime number try again: ", cin >> p; // prompt user for p if not prime.
    cout << "Choose a number (a), such that (a) is less than (P), must be generator -------(a) <= Z*" << p << ": ", cin >> a; // Choose a number (a), such that (a) is less than (P), must be generator (a) ∈ ℤ∗Ρ∗ as public value.
    while (!(1 < a && a <= p - 2) || !(is_generator(a, p))) cout << "(a) must be generator ------(a) <= Z*" << p << " try again: ", cin >> a; // prompt user for a if not a generator of p.
    cout << "Choose a random number (x), such that 1 < x <= " << p - 2 << ": ", cin >> x; // Choose a random number (x), such that 1 < x ≤ P – 2 as a private key.
    while (!(1 < x && x <= p - 2)) cout << "(x) must be 1 < x <= " << p - 2 << " try again: ", cin >> x; // prompt user for x if not 1 < x ≤ p – 2.
    d = pow_mod(a, x, p); // Compute (d) such that d = ax mod P, such that d is public value.
    pu = {p, a, d}, pr = {p, x, y};

    return;
}

// Elgamal key.
void ek (vector<long long> &pu, vector<long long> &pr)
{
    srand(time(nullptr));
    long long p, a, x, d, y = 0;
    do { p = rand(); } while (!is_prime(p) || p < 2); // Generate a random prime number namely (P) as public value.
    do { a = rand(); } while (!(1 < a && a <= p - 2) || !(is_generator(a, p))); // Generate a number (a), such that (a) is less than (P), must be generator (a) ∈ ℤ∗Ρ∗ as public value.
    do { x = rand(); } while (!(1 < x && x <= p - 2)); // Generate a random number (x), such that 1 < x ≤ P – 2 as a private key.
    d = pow_mod(a, x, p); // Generate (d) such that d = ax mod P, such that d is public value.
    pu = {p, a, d}, pr = {p, x, y};

    return;
}

// Elgamal encryption.
vector<long long> elgamale (vector<long long> m, vector<long long> pu)
{
    // Obtain the public keys (P, a, d) from A.
    srand(time(nullptr));
    int n = m.size();
    long long p = pu[0], a = pu[1], d = pu[2], k; 
    vector<long long> c(n + 1, 0);

    do { k = rand(); } while (!(1 < k && k < p - 1)); // Choose a key (k) as random integer such that 1 < k ≤ P – 2, as ephemeral key.
    // cout << "Choose a key (k) as random integer such that 1 < k <= " << p - 2 << ": ", cin >> k; 
    // while (!(1 < k && k <= p - 2)) cout << "(k) must be 1 < x <= " << p - 2 << " try again: ", cin >> k; // prompt user for x if not 1 < x ≤ p – 2.

    c[0] = pow_mod(a, k, p); // Compute (Y), such that Y = a pow k mod P. as a mask key.

    long long dk = pow_mod(d, k, p);
    for (int i = 0; i < n; i++)
    {
        if (!(1 < m[i] && m[i] <= p - 2)) return {};
        // Determine the message (m) to be encrypted, such that 0 < m ≤ P – 1, such that m ∈ ℤ∗Ρ.
        // Compute (Z), such that Z = d pow K × m mod P.
        c[i + 1] = mod(dk * m[i], p);
    }

    return c;
}

// Elgamal decryption.
vector<long long> elgamald (vector<long long> c, vector<long long> &pr)
{
    // Obtain the ciphertext C from B.
    int n = c.size();
    long long p = pr[0], x = pr[1], y = pr[2], y_ = 0;
    vector<long long> m(n, 0);

    y_ = pow_mod(y, p-1-x, p); // Compute Y_ such that, Y_ = Y pow P−1−X mod P.
    for (int i = 0; i < n; i++)
    {
        m[i] = mod(y_ * c[i], p); // Recover the message. Such that m = Y_ × Z mod P.
    }
    
    return m;
}