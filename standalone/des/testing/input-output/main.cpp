#include"des.h"

// DES
int main()
{
    vector<string> m, k;

    m = {"87", "87", "87", "87", "87", "87", "87", "87"}, k = {"0E", "32", "92", "32", "EA", "6D", "0D", "73"};
    print_binary(dese(hex_to_bi(m), hex_to_bi(k)));

    return 0;
}