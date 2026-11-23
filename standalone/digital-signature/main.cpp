#include"digital_signature.h"

// Digital Signature
int main()
{
    string message;
    vector<long long> m;
    vector<long long> pu, pr;
    vector<vector<long long>> signed_message;
    rsak(pu, pr);
    // irsak(pu, pr);
    // cin.ignore();
    cout << "Input text: ", getline(cin, message);
    m = str_to_dec(message);
    while(true)
    {
        int choice;
        cout << "1.Signe" << endl;
        cout << "2.verify" << endl;
        cout << "3.Exit" << endl;
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
            return 0;
        }
    }
}