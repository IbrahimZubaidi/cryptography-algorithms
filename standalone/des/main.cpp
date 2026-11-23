#include"des.h"

// DES
int main()
{
    string plaintext, ciphertext, text, key;
    cout << "Input text: ", getline(cin, text);
    // cout << "Input key: ", getline(cin, key);
    key = desk();
    plaintext = ciphertext = text;
    while(true)
    {
        int choice;
        cout << "1.Encrypt" << endl;
        cout << "2.Decrypt" << endl;
        cout << "3.Exit" << endl;
        cout << "Enter choice: ", cin >> choice;
        if (choice == 1)
        {
            pad(plaintext, 8);
            ciphertext = "";
            int n = plaintext.length(), m = key.length();
            string p = "", k = "";
            for(int i = 0; i < n; i++)
            {
                p += plaintext[i];
                k += key[i % m];
                if ((i + 1) % 8 == 0)
                {
                    ciphertext += bi_to_str(dese(str_to_bi(p), str_to_bi(k)));
                    p = "", k = "";
                } 
                
            }
            cout << ciphertext << endl;
        }
        else if (choice == 2)
        {
            pad(ciphertext, 8);
            plaintext = "";
            int n = ciphertext.length(), m = key.length();
            string c = "", k = "";
            for(int i = 0; i < n; i++)
            {
                c += ciphertext[i];
                k += key[i % m];
                if ((i + 1) % 8 == 0)
                {
                    plaintext += bi_to_str(desd(str_to_bi(c), str_to_bi(k)));
                    c = "", k = "";
                } 
                
            }
            cout << plaintext<< endl;
        }
        else
        {
            return 0;
        }
    }
}