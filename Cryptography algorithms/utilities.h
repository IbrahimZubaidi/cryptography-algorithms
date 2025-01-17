#include<iostream>
#include<vector>

using namespace std;

// Print binary values.
void print_binary(vector<bool> b)
{
    int n = b.size();
    for(int i = 0; i < n; i++)
    {
        cout << b[i];
        if ((i + 1) % 8 == 0)
        cout << " ";
    }
    cout << endl;

    return;
}

// Split bits to bytes.
vector<vector<bool>> split (vector<bool> bits)
{
    int n = bits.size();
    vector<vector<bool>> bytes((n / 8), vector<bool>(8));
    for (int i = 0; i < n; i++)
    {  
        bytes[i / 8][i % 8] = bits[i];
    }
    
    return bytes;
}

// Combine bytes to bits.
vector<bool> combine (vector<vector<bool>> word)
{
    int n = word.size(), m = word[0].size();
    vector<bool> b(m * n, 0);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            b[m * i + j] = word[i][j];
        }
    }
    return b;
}

// Add padding to a string to ba a multiple of 64-bits.
void pad (string &s, int n)
{
    int i = s.length();
    while(i % n != 0)
    {
        s += '\x00';
        i += 1;
    }
}

// Left shift.
void shift_left (vector<bool> &b, int n)
{
    int m = b.size();
    for(int i = 0; i < n; i++)
    {
        bool b0 = b[0];
        for(int j = 0; j < m - 1; j++)
        {
            b[j] = b[j+1];
        }
        b[m - 1] = b0;
    }
}