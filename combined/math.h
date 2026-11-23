#include<bitset>
#include<cmath>
#include<ctime>
#include<cstring>
#include<iostream>
#include<math.h>
#include<string>
#include<sstream>
#include<vector>

#include"utilities.h"

using namespace std;

// Decimal to binary.
vector<bool> dec_to_bi(int n)
{
    if (n == 0)
    {
        return vector<bool>(8,0);
    }

    vector<bool> b = {};
    int nb, v;
    bool negative = n < 0;

    if (negative)
    {
        n = -n;
    }

    nb = log2(n) + 1;
    while(nb % 8 != 0)
    {
        nb += 1;
    }

    if(negative)
    {
        n = pow(2, nb) - n;
    }

    v = log2(n);
    for (int i = nb - 1; i >= 0; i--)
    {
        if (i == v)
        {
            n -= pow(2, v);
            v = log2(n);
            b.push_back(1);
            continue;
        }
        b.push_back(0);
    }

    return b;
}

// Binary to decimal.
long long bi_to_dec(vector<bool> bi)
{
    int nb = bi.size();
    long long n = 0;
    for (int i = nb - 1; i >= 0; i--)
    {
        n += pow(2, i) * bi[nb - i - 1];
    }

    return n;
}

// String to int stream.
vector<long long> str_to_dec(string s)
{
    int i = 0;
    vector<long long> n;
    while(s[i])
    {
        n.push_back(s[i]);
        i++;
    }

    return n;
}

// Int stream to string.
string dec_to_str(vector<long long> n)
{
    int i = 0, m = n.size();
    string s = "";
    while(i < m)
    {
        s += n[i];
        i++;
    }

    return s;
}

// String to binary stream.
vector<bool> str_to_bi (string s)
{
    int n = s.length();
    vector<bool> bi = {};
    for (int i = 0; i < n; i ++)
    {
        vector<bool> lbi = dec_to_bi(s[i]);
        int m = lbi.size();
        for (int i = 0; (i + m) % 8 != 0; i++)
        {
            bi.push_back(0);
        }

        for (int j = 0; j < m; j++)
        {
            bi.push_back(lbi[j]);
        }
    }
    
    return bi;
}

// Binary stream to string.
string bi_to_str (vector<bool> bi)
{
    string s = "";
    int n = bi.size();
    for(int i = 0; i < n; i+=8)
    {
        vector<bool> lbi = {};
        for(int j = 0; j < 8; j++)
        {
            lbi.push_back(bi[i + j]);
        }
        s += bi_to_dec(lbi);
    }
    
    return s;
}

// Decimal to hex string.
string dec_to_hex(long long decimal) {
    stringstream ss;
    ss << hex << decimal;
    string s = ss.str();
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        if(isalpha(s[i]) && islower(s[i]))
        s[i] = toupper(s[i]);
    }
    if (n == 2)
    return s;
    return "0" + s;
}

// Hex string to decimal.
long long hex_to_dec(const string &hex) {
    long long decimal;
    stringstream ss;
    ss << std::hex << hex; 
    ss >> decimal;
    return decimal;
}

// Hex string to binary.
vector<bool> hex_to_bi(vector<string> s)
{
    int n = s.size();
    vector<long long> dec(n, 0);
    for (int i = 0; i < n; i++)
    {
        dec[i] = hex_to_dec(s[i]);
    }
    
    vector<vector<bool>> temp(n, vector<bool>(8, 0));
    for(int i = 0; i < n; i++)
    {
        temp[i] = dec_to_bi(dec[i]);
    }

    return combine(temp);
}

// Binary to jext string.
vector<string> bi_to_hex(vector<bool> bi)
{
    vector<vector<bool>> by = split(bi);
    int n = by.size();
    vector<string> s(n);
    for(int i = 0; i < n; i++)
    {
       
        s[i] = dec_to_hex(bi_to_dec(by[i]));
    }
   
    return s;
}

// XOR two binary values.
vector<bool> x_or (vector<bool> a, vector<bool> b)
{
    int n = min(a.size(), b.size()), m = a.size();
    for(int i = 0; i < n; i ++)
    {
        if (n > m) 
            b[i] = a[i] ^ b[i];
        else 
            a[i] = a[i] ^ b[i];
    }
    if (n > m) 
        return b;
    else
        return a;
}

// Multiply two binary values as plynomials.
vector<bool> mul_bi (vector<bool> temp, vector<bool> b) 
{
    vector<bool> result(16, 0), a(16, 0);

    int n = temp.size();
    for (int i = 0; i < n; i++)
    {
        a[15 - i] = temp[7 - i];
    }

    for (int i = b.size() - 1; i >= 0; i--) 
    {
        if (b[i] == 1) 
        {
            result = x_or(result, a);
        }
        shift_left(a, 1);
    }

    return result;
}

long long mod (long long a, long long b)
{
    long long m;
    m = abs(a) % b;
    if (m && a < 0)
    m =  (b - m);
    // cout << a << " mod " << b << " = " << m << endl;
    return m;
}

// Fast Exponentiation.
long long pow_mod(long long a, long long b, long long m)
{
    vector<bool> bi, temp = dec_to_bi(b);

    int n = temp.size();
    bool cond = false;
    for(int i = 0; i < n; i++)
    {
        if (temp[i] == 1)
        {
            cond = true;
        }
        if (cond)
        {
            bi.push_back(temp[i]);
        }
    }

    int s = bi.size();
    long long c = a;
    for (int i = 1; i < s; i++)
    {
        c = c * c % m;
        if (bi[i] == 1)
        {
            c = c * a % m; 
        } 
    }

    return c;
}

// Euclidean Algorithm.
long long gcd(long long a, long long b)
{
    if (a < b)
    {
        swap(a, b);
    }
    
    for (long long r = a % b; r != 0; r = a % b)
    {
        a = b;
        b = r;
    }

    return b;
}

// Extended Euclidean Algorithm.
long long eea(long long a, long long b)
{
    if (a < b)
    {
        swap(a, b);
    }

    long long a0 = a, b0 = b;
    long long q, r, t, t1 = 0, t2 = 1;
    while (b != 0)
    {
        r = a % b;
        q = a / b; 
        t = t1 - t2 * q;
        a = b;
        b = r;
        t1 = t2, t2 = t;
    }

    if (t1 < 0)
    {
        t1 += a0;
    }

    if (b0 < 0)
    {
        t1 = -t1;
    }

    return t1;
}

vector<long long> point_doubling (vector<long long> p1, long long a, long long p)
{
    long long x1 = p1[0], y1 = p1[1];
    long long s, num = mod(ceil(3 * pow(x1, 2) + a), p), den = mod(ceil(2 * y1), p);
    
    if (den < 0)
    {
        den = -den;
        num = -num;
    }

    if (num / static_cast<long double>(den) == num / (den))
    s = mod(ceil(num / den), p);
    else
    s = mod(ceil(num * eea(den, p)), p);

    long long x3 = mod(ceil(pow(s, 2) - x1 - x1), p);
    long long y3 = mod(ceil(s * (x1 - x3) - y1), p);

    return vector<long long> {x3, y3};
}

vector<long long> point_addition (vector<long long> p1, vector<long long> p2, long long p)
{ 
    long long x1 = p1[0], y1 = p1[1], x2 = p2[0], y2 = p2[1];
    long long s, num = (y2 - y1), den = (x2 - x1);
    
    if (den == 0)
    {
        return vector<long long> {0, 0};
    }

    if (den < 0)
    {
        den = -den;
        num = -num;
    }

    if (num / static_cast<long double>(den) == num / den)
    s = mod(ceil(num / den), p);
    else
    s = mod(ceil(num  * eea(den, p)), p);
    
    long long x3 = mod(ceil(pow(s, 2) - x1 - x2), p);
    long long y3 = mod(ceil(s * (x1 - x3) - y1), p);

    return vector<long long> {x3, y3};
}

// Check if prime.
bool is_prime(long long n)
{
    int s = sqrt(n);
    for (int i = 2; i <= s; ++i) 
    {
        if (n % i == 0) 
        {
            return false;
        }
    }

    return true;
}

// Check if generator.
bool is_generator(long long n, long long p)
{
    if (n > p) 
    {
        return false;
    }

    for (int i = 1; i < p; i ++)
    {
        if (pow_mod(n, i, p) == n && i != 1)
        {
            return false;
        }
    }

    return true;
}

// Check if point on curve.
bool is_point(vector<long long> P, long long a, long long b, long long p)
{
    long long x = P[0], y = P[1];
    if (pow_mod(y, 2, p) != mod(ceil(pow(x, 3) + x * a + b), p))
    {
        return false;
    }
    
    return true;
}

// Check if a elliptic curve possible.
bool is_curve(long long a, long long b)
{
    if ((4 * pow(a, 3) + 27 * pow(b, 2)) == 0)
    {
        return false;
    }
    
    return true;
}

// Check point if generator.
bool is_point_generator(vector<long long> P, long long a, long long p)
{
    vector<long long> Q = point_doubling(P, a, p);
    for (int i = 0; i < p + 1; i++)
    {
        if (Q == P)
        {
            return false;
        }
        Q = point_addition(P, Q, p);
    }

    return true;
}

