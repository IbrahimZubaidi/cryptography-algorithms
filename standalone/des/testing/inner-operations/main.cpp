#include"des.h"

// DES
int main()
{
    vector<string> m, k;

    m = {"01", "23", "45", "67", "89", "AB", "CD", "EF"}, k = {"12", "34", "57", "79", "9B", "BC", "DF", "F1"};

    m = bi_to_hex(dese(hex_to_bi(m), hex_to_bi(k)));
    for(int i = 0; i < 8; i++)
    {
        cout << m[i];
    }
}