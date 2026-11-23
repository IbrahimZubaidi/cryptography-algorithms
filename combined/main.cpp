#include"interfaces.h"

int main(void)
{  

    while(true)
    {
        int choice;
        cout << "1.DES" << endl;
        cout << "2.AES" << endl;                          
        cout << "3.RSA" << endl;
        cout << "4.Diffie-Hellman" << endl;
        cout << "5.Elgamal" << endl;
        cout << "6.Digital-Signature" << endl;
        cout << "7.Elliptic-Curve" << endl;
        cout << "8.Exit" << endl;
        cout << "Enter choice: ", cin >> choice;
        if (choice == 8) break;
        else if (choice == 1) DES_interface();
        else if (choice == 2) AES_interface();
        else if (choice == 3) RSA_interface();
        else if (choice == 4) Diffie_Hellman_interface();
        else if (choice == 5) Elgamal_interface();
        else if (choice == 6) Digital_Singnature_interface();
        else if (choice == 7) Elliptic_Curve_interface();
    } 

    return 0;
}
