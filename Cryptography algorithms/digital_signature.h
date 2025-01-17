#include"elgamal.h"

// Cryptographic hash function (SHA256).
string sha256(string s1)
{
    string s2;
    for (int i = 0; i < 10; i ++)
    {
        s2 += s1[i % s1.length()];
    }

    return s2;
}

// Digital signature generation algorithm (RSA, SHA256).
vector<vector<long long>> dsg (vector<long long> m, vector<long long> pr)
{
    string h = sha256(dec_to_str(m));
    vector<long long> e = rsa(str_to_dec(h), pr);
    vector<vector<long long>> s = {m, e};

    return s;
}

// Digital signature verification algorithm (RSA, SHA256).
bool dsv (vector<vector<long long>> s, vector<long long> pu)
{
    vector<long long> m = s[0], e = s[1];
    string dh = dec_to_str(rsa(e, pu)), ch = sha256(dec_to_str(m));
    
    return dh == ch;
}