#include"digital_signature.h"

// Input Elliptic curve setup protocol.
void iecsp (vector<long long> &P, long long &a, long long &b, long long &p)
{
    long long x, y;
    cout << "Choose a prime (p): ", cin >> p; // Choose a large prime (p).
    while(!is_prime(p)) cout << "(p) must be prime: ", cin >> p; // Prompt user for (p) if not prime.
    cout << "Choose the curve coefficients (a, b) with (4a^3 + 27b^2 != 0): ", cin >> a, cin >> b; // Choose the curve coefficient (a).
    while(!is_curve(a, b)) cout << "(a) and (b) don't mee the condition (4a^3 + 27b^2 != 0): ", cin >> a, cin >> b; // Prompt user for (a) and (b) if don't meet the condition (4a^3 + 27b^2 != 0).
    cout << "Choose a primitive element (P) = (xP, yP): ", cin >> x, cin >> y, P = {x, y}; // Choose a primitive element (P) = (xP, yP).
    while(!is_point_generator(P, a, p) || !is_point(P, a, b, p)) cout << "(P) must be generator point on the curve: ", cin >> x, cin >> y, P = {x, y}; // Prompt user for (P) if not on curve or generator.
    
    return; // publish a, b, p, and P.
}

// Input Elliptic curve key exchange protocol.
void ieckep (vector<long long> P, vector<long long> &Kpub, long long &Kpr, long long a, long long p)
{
    long long x;
    vector<long long> X = P;
    cout << "Choose an integer (x): ", cin >> x; // Choose an integer (x).
    // Compute X = KpubX.
    for(int i = 0; i < x - 1; i++)
    {
        if (X == vector<long long>{0, 0})
        {   
            X = P;
        }
        else if(X == P)
        {
            X = point_doubling(X, a, p);
        }
        else
        {
            X = point_addition(P, X, p);
        }
    } 
    Kpub = X, Kpr = x;

    return;
}

// Elliptic curve setup protocol.
void ecsp (vector<long long> &P, long long &a, long long &b, long long &p)
{
    srand(time(nullptr));
    long long x, y;
    do { p = rand(); } while (!is_prime(p)); // Generate a prime (p).
    do { a = rand(), b = rand(); } while (!is_curve(a, b)); // Generate the curve coefficient (a, b).
    do { x = rand(), y = rand(), P = {x, y}; } while (!(1 < x && x < p) || !(1 < y && y < p) || !is_point_generator(P, a, p) || !is_point(P, a, b, p)); // Generate a primitive element (P) = (xP, yP).

    return; // publish p and a.
}

// Elliptic curve key exchange protocol.
void eckep (vector<long long> P, vector<long long> &Kpub, long long &Kpr, long long a, long long p)
{
    srand(time(nullptr));
    long long x = rand(); // Generate an integer (x).
    // Compute X = KpubX.
    vector<long long> X = P;
    for(int i = 0; i < x - 1; i++)
    {
        if (X == vector<long long>{0, 0})
        {   
            X = P;
        }
        else if(X == P)
        {
            X = point_doubling(X, a, p);
        }
        else
        {
            X = point_addition(P, X, p);
        }
    }  
    Kpub = X, Kpr = x;

    return;
}

// Elliptic curve diffie-hellman key exchange.
vector<long long> elliptic_curve(long long KprX, vector<long long> KpubY, long long a, long long p)
{
    vector<long long> TAB = KpubY;
    for(int i = 0; i < KprX - 1; i++)
    {
        if (TAB == vector<long long>{0, 0})
        {   
            TAB = KpubY;
        }
        else if(TAB == KpubY)
        {
            TAB = point_doubling(TAB, a, p);
        }
        else
        {
            TAB = point_addition(KpubY, TAB, p);
        }
    } 

    return TAB;
}