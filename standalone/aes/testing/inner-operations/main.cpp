#include"aes.h"

// AES
int main()
{   
    vector<string> input, output, key;
    input = {"EA", "83", "5C", "F0", "04", "45", "33", "2D", "65", "5D", "98", "AD", "85", "96", "B0", "C5"};

    // Turn input to binary.
    vector<bool> m = hex_to_bi(input), k;
    
    // Substitute bytes.
    substitute_bytes(m);

    // Print input and output of substitute bytes.
    cout << "Substitute bytes:"<< endl;
    output = bi_to_hex(m);
    for (int i = 0; i < 16; i++)
    {
        int t = ((i * 4) + (i / 4)) % 16;
        cout << input[t] << " ";
        
        if ((i + 1) % 4 == 0)
        {
            cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << output[t] << " ";
            }
            cout << endl;
        }   
    }
    cout << endl;
    input = output;
    
    // Shift rows.
    shift_rows(m);

    // Print input and output of shift rows.
    cout << "Shift rows:"<< endl;
    output = bi_to_hex(m);
    for (int i = 0; i < 16; i++)
    {
        int t = ((i * 4) + (i / 4)) % 16;
        cout << input[t] << " ";
        
        if ((i + 1) % 4 == 0)
        {
            cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << output[t] << " ";
            }
            cout << endl;
        }   
    }
    cout << endl;
    input = output;

    // Mix columns.
    mix_columns(m);

    // Print input and output of mix columns.
    cout << "Mix columns:"<< endl;
    output = bi_to_hex(m);
    for (int i = 0; i < 16; i++)
    {
        int t = ((i * 4) + (i / 4)) % 16;
        cout << input[t] << " ";
        
        if ((i + 1) % 4 == 0)
        {
            cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << output[t] << " ";
            }
            cout << endl;
        }   
    }
    cout << endl;
    input = output;

    key = {"AC", "77", "66", "F3", "19", "FA", "DC", "21", "28", "D1", "29", "41", "57", "5C", "00", "6A"};
    k = hex_to_bi(key);

    // Add round key.
    add_round_key(m, k);

    // Print input and output of add round key.
    cout << "Add round key:"<< endl;
    output = bi_to_hex(m);
    for (int i = 0; i < 16; i++)
    {
        int t = ((i * 4) + (i / 4)) % 16;
        cout << input[t] << " ";
        
        if ((i + 1) % 4 == 0)
        {
            if (i == 11) cout << "(+) ";
            else cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << key[t] << " ";
            }

            if (i == 11) cout << " =  ";
            else cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << output[t] << " ";
            }
            cout << endl;
        }   
    }
    cout << endl;
    input = output;

    key = {"AC", "77", "66", "F3", "19", "FA", "DC", "21", "28", "D1", "29", "41", "57", "5C", "00", "6A"};
    k = hex_to_bi(key);

    // Add round key.
    add_round_key(m, k);

    // Print input and output of add round key.
    cout << "Add round key:"<< endl;
    output = bi_to_hex(m);
    for (int i = 0; i < 16; i++)
    {
        int t = ((i * 4) + (i / 4)) % 16;
        cout << input[t] << " ";
        
        if ((i + 1) % 4 == 0)
        {
            if (i == 11) cout << "(+) ";
            else cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << key[t] << " ";
            }
            
            if (i == 11) cout << " =  ";
            else cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << output[t] << " ";
            }
            cout << endl;
        }   
    }
    cout << endl;
    input = output;

    // Inverse mix columns.
    inverse_mix_columns(m);

    // Print input and output of inverse mix columns.
    cout << "Inverse mix columns:"<< endl;
    output = bi_to_hex(m);
    for (int i = 0; i < 16; i++)
    {
        int t = ((i * 4) + (i / 4)) % 16;
        cout << input[t] << " ";
        
        if ((i + 1) % 4 == 0)
        {
            cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << output[t] << " ";
            }
            cout << endl;
        }   
    }
    cout << endl;
    input = output;

    // Inverse shift rows.
    inverse_shift_rows(m);

    // Print input and output of inverse shift rows.
    cout << "Inverse shift rows:"<< endl;
    output = bi_to_hex(m);
    for (int i = 0; i < 16; i++)
    {
        int t = ((i * 4) + (i / 4)) % 16;
        cout << input[t] << " ";
        
        if ((i + 1) % 4 == 0)
        {
            cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << output[t] << " ";
            }
            cout << endl;
        }   
    }
    cout << endl;
    input = output;

    // Inverse substitute bytes.
    inverse_substitute_bytes(m);

    // Print input and output of inverse substitute bytes.
    cout << "Inverse substitute bytes:"<< endl;
    output = bi_to_hex(m);
    for (int i = 0; i < 16; i++)
    {
        int t = ((i * 4) + (i / 4)) % 16;
        cout << input[t] << " ";
        
        if ((i + 1) % 4 == 0)
        {
            cout << "    ";
            for (int j = 0; j < 4; j++)
            {
                int t = ((j * 4) + (i / 4)) % 16;
                cout << output[t] << " ";
            }
            cout << endl;
        }   
    }

    return 0;
}