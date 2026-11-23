#include"rsa.h"

// Input setup protocol.
void isp (long long &p, long long &a)
{
    cout << "Choose a large prime (p): ", cin >> p; // Choose a large prime (p).
    while(!is_prime(p)) cout << "(p) must be prime: ", cin >> p; // prompt user for (p) if not prime.
    cout << "Choose an integer (a) <= {2,3,...,p-2}: ", cin >> a; // Choose an integer (a) <= {2,3,...,p-2}.
    while (!(1 < a && a <= (p - 2))) cout << "(a) must be <= {2,3,...,p-2}: ", cin >> a; // prompt user for (a) if (a) not <= {2,3,...,p-2}.

    return; // publish p and a.
}

// Input key exchange protocol.
void ikep (long long &Kpub, long long &Kpr, long long p, long long a)
{
    long long x, X;
    cout << "Choose an integer (x) <= {2,3,...,p-2}: ", cin >> x; // Choose an integer (x) <= {2,3,...,p-2}.
    while (!(1 < x && x <= (p - 2))) cout << "(x) must be <= {2,3,...,p-2}: ", cin >> x; // prompt user for (x) if (x) not <= {2,3,...,p-2}.
    X = pow_mod(a, x, p); // Compute X = KpubX.
    Kpub = X, Kpr = x;

    return;
}

// Setup protocol.
void sp (long long &a, long long &p)
{
    srand(time(nullptr));
    do { p = rand(); } while (!is_prime(p)); // Generate a large prime (p).
    do { a = rand(); } while (!(1 < a && a <= p - 2)); // Generate an integer (a) <= {2,3,...,p-2}

    return; // publish p and a.
}

// Key exchange protocol.
void kep (long long &Kpub, long long &Kpr, long long a, long long p)
{
    srand(time(nullptr));
    long long x, X;
    do { x = rand(); } while (!(1 < x && x <= p - 2)); // Generate an integer (x) <= {2,3,...,p-2}.
    X = pow_mod(a, x, p); // Compute X = KpubX.
    Kpub = X, Kpr = x;
    
    return;
}

// diffie hellman (encryption and decryption).
long long diffie_hellman(long long KprX, long long KpubY, long long p)
{
    return pow_mod(KpubY, KprX, p);
}