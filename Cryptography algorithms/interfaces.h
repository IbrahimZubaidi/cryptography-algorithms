#include"elliptic_curve.h"

// DES
void DES_interface()
{
    cin.ignore();
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
        cout << "3.Return" << endl;
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
            return;
        }
    }
}

// AES
void AES_interface()
{   
    cin.ignore();
    string plaintext, ciphertext, text, key;
    cout << "Input text: ", getline(cin, text);
    // cout << "Input key: ", getline(cin, key);
    key = aesk();
    plaintext = ciphertext = text;
    while(true)
    {
        int choice;
        cout << "1.Encrypt" << endl;
        cout << "2.Decrypt" << endl;
        cout << "3.Return" << endl;
        cout << "Enter choice: ", cin >> choice;
        if (choice == 1)
        {
            pad(plaintext, 16);
            ciphertext = "";
            int n = plaintext.length(), m = key.length();
            string p = "", k = "";
            for(int i = 0; i < n; i++)
            {
                p += plaintext[i];
                k += key[i % m];
                if ((i + 1) % 16 == 0)
                {
                    ciphertext += bi_to_str(aese(str_to_bi(p), str_to_bi(k)));
                    p = "", k = "";
                } 
                
            }
            cout << ciphertext << endl;
        }
        else if (choice == 2)
        {
            pad(ciphertext, 16);
            plaintext = "";
            int n = ciphertext.length(), m = key.length();
            string c = "", k = "";
            for(int i = 0; i < n; i++)
            {
                c += ciphertext[i];
                k += key[i % m];
                if ((i + 1) % 16 == 0)
                {
                    plaintext += bi_to_str(aesd(str_to_bi(c), str_to_bi(k)));
                    c = "", k = "";
                } 
                
            }
            cout << plaintext<< endl;
        }
        else
        {
            return;
        }
    }
}

// RSA
void RSA_interface()
{
    string text;
    vector<long long> m, c;
    vector<long long> pu, pr;
    // irsak(pu, pr);
    rsak(pu, pr);
    cin.ignore();
    cout << "Input text: ", getline(cin, text);
    m = c = str_to_dec(text);
    while(true)
    {
        int choice;
        cout << "1.Encrypt" << endl;
        cout << "2.Decrypt" << endl;
        cout << "3.Return" << endl;
        cout << "Enter choice: ", cin >> choice;
        if (choice == 1)
        {
            c = rsa(m, pu);
            if (c.empty())
            {
                cout << "Error, key too small!" << endl;
                continue;
            }
            cout << dec_to_str(c) << endl;
        }
        else if (choice == 2)
        {
            m = rsa(c, pr);
            cout << dec_to_str(m) << endl;
        }
        else
        {
            return;
        }
    }
}

// DHKE
void Diffie_Hellman_interface()
{
    long long p, a;
    long long KpubA, KprA, KpubB, KprB;
    // isp(p, a);
    sp(p, a);
    // cout << "Alice" << endl;
    // ikep(KpubA, KprA, p, a);
    kep(KpubA, KprA, p, a);
    // cout << "Bob" << endl;
    // ikep(KpubB, KprB, p, a);
    kep(KpubB, KprB, p, a);
    
    cout << "Alice computes KAB = " << diffie_hellman (KprA, KpubB, p) << endl;
    cout << "Bob computes KAB = " << diffie_hellman (KprB, KpubA, p) << endl;
}

// ELGAMAL
void Elgamal_interface()
{
    string text;
    vector<long long> m, c;
    vector<long long> pu, pr;
    // iek(pu, pr);
    ek(pu, pr);
    cin.ignore();
    cout << "Input text: ", getline(cin, text);
    m = c = str_to_dec(text);
    while(true)
    {
        int choice;
        cout << "1.Encrypt" << endl;
        cout << "2.Decrypt" << endl;
        cout << "3.Return" << endl;
        cout << "Enter choice: ", cin >> choice;
        if (choice == 1)
        {
            c = elgamale(m, pu);
            if (c.empty())
            {
                cout << "Error, key too small!" << endl;
                continue;
            }
            pr[2] = c.front();
            c.erase(c.begin());
            cout << dec_to_str(c) << endl;
        }
        else if (choice == 2)
        {
            m = elgamald(c, pr);
            cout << dec_to_str(m) << endl;
        }
        else
        {
            return;
        }
    }
}

// Digital Signature
void Digital_Singnature_interface()
{
    string message;
    vector<long long> m;
    vector<long long> pu, pr;
    vector<vector<long long>> signed_message;
    // irsak(pu, pr);
    rsak(pu, pr);
    cin.ignore();
    cout << "Input text: ", getline(cin, message);
    m = str_to_dec(message);
    while(true)
    {
        int choice;
        cout << "1.Signe" << endl;
        cout << "2.verify" << endl;
        cout << "3.Return" << endl;
        cout << "Enter choice: ", cin >> choice;
        if (choice == 1)
        {
            signed_message = dsg(m, pr);
            if (signed_message[1].empty())
            {
                cout << "Error, key too small!" << endl;
                continue;
            }
            cout << dec_to_str(signed_message[0]) << "\nSignature: " << dec_to_str(signed_message[1]) << endl;
        }
        else if (choice == 2)
        {
            if (dsv(signed_message, pu)) cout << "Message verified!" << endl;
            else cout << "Message not verified!" << endl;
        }
        else
        {
            return;
        }
    }
}

// Elliptic curve key exchange protocol.
void Elliptic_Curve_interface()
{
    long long a, b, p;
    vector<long long> P, KpubA, KpubB, TAB;
    long long KprA, KprB;
    ecsp(P, a, b, p);
    // iecsp(P, a, b, p);
    eckep(P, KpubA, KprA, a, p);
    // cout << "Alice" << endl;
    // ieckep(P, KpubA, KprA, a, p);
    eckep(P, KpubB, KprB, a, p);
    // cout << "Bob" << endl;
    // ieckep(P, KpubB, KprB, a, p);

    TAB = elliptic_curve(KprA, KpubB, a, p);
    cout << "Alice computes TAB = (" << TAB[0] << ", " << TAB[1] <<")" << endl;
    TAB = elliptic_curve(KprB, KpubA, a, p);
    cout << "Bob computes TAB = (" << TAB[0] << ", " << TAB[1] <<")" << endl;
}