#include"aes.h"

// AES
int main()
{   
    string message, key;
    message = "Two One Nine Two";
    key = "Thats my Kung Fu";

    vector<bool> m, k;
    m = str_to_bi(message);
    k = str_to_bi(key);

    m = aese(m, k);
    cout << endl;

    vector<string> hex = bi_to_hex(m);
    int n = hex.size();
    cout << "\t\tAES Final Output" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << hex[i] << " ";
    }
    cout << endl;

    return 0;
}