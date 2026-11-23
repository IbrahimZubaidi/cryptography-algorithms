#include"elgamal.h"

// ELGAMAL
int main()
{
    string text;
    vector<long long> m, c;
    vector<long long> pu, pr;
    ek(pu, pr);
    // iek(pu, pr);
    // cin.ignore();
    cout << "Input text: ", getline(cin, text);
    m = c = str_to_dec(text);
    while(true)
    {
        int choice;
        cout << "1.Encrypt" << endl;
        cout << "2.Decrypt" << endl;
        cout << "3.Exit" << endl;
        cout << "Enter choice: ", cin >> choice;
        if (choice == 1)
        {
            c = elgamale(m, pu);
            if (c.empty())
            {
                cout << "Error, key too small!" << endl;
                return 1;
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
            return 0;
        }
    }
}