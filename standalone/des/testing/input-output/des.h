#include"../../../shared/math.h"

// Initial permutation table (IP)
const int initial_permutation[64] = 
{
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Inverse initial permutation (IP-1)
const int inverse_initial_permutation[64] = 
{
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Expansion permutation table (E)
const int expansion_permutation[48] = 
{
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// permutation table (P)
const int p_permutation[32] = 
{
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// Permuted choice one (PC_1)
const int permuted_choice_one[56] = 
{
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Permuted choice two (PC_2)
const int permuted_choice_two[48] = 
{
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

// Secuedual of left shift.
const int secudual_of_left_shift[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// S-boxes
const int s_boxes[8][4][16] = 
{
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

// DES key.
string desk (int n = 8)
{
    vector<long long> d(n, 0);
    srand(time(nullptr));
    for (int i = 0; i < n; i++)
    {
        d[i] = rand();
    }
    return dec_to_str(d);
}

// Initial permutation (IP).
vector<bool> ip (vector<bool> b)
{
    vector<bool> permutated(64, 0);
    for (int i = 0; i < 64; i++)
    {
        permutated[i] = b[initial_permutation[i] - 1];
    }
    
    return permutated;
}

// Inverse initial permutation (IP-1).
vector<bool> iip (vector<bool> b)
{
    vector<bool> permutated(64, 0);
    for (int i = 0; i < 64; i++)
    {
        permutated[i] = b[inverse_initial_permutation[i] - 1];
    }

    return permutated;
}

// Permutation choice one (PC_1).
vector<bool> pc1 (vector<bool> k)
{
    vector<bool> permutated(56, 0);
    for(int i = 0; i < 56; i++)
    {
        permutated[i] = k[permuted_choice_one[i] - 1];
    }

    return permutated;
}

// Permutation choice two (PC_2).
vector<bool> pc2 (vector<bool> k)
{
    vector<bool> permutated(48, 0);
    for(int i = 0; i < 48; i++)
    {
        permutated[i] = k[permuted_choice_two[i] - 1];
    }

    return permutated;
}

// Left shift (s).
vector<bool> s (vector<bool> k, int n)
{
    int m = k.size();
    for(int i = 0; i < n; i++)
    {
        bool k0 = k[0];
        for(int j = 0; j < m - 1; j++)
        {
            k[j] = k[j+1];
        }
        k[m - 1] = k0;
    }

    return k;
}

// Expansion/Permutation (E table).
vector<bool> e_table (vector<bool> r)
{
    vector<bool> expanded(48, 0);
    for(int i = 0; i < 48; i++)
    {
        expanded[i] = r[expansion_permutation[i] - 1];
    }

    return expanded;
}

// Substitution/Choice (S-box).
vector<bool> s_box (vector<bool> x)
{
    // Split the XOR output to 8 sections, each section is 6-bits. 
    vector<vector<bool>> si(8, vector<bool>(6, 0));
    for (int i = 0; i < 48; i+=6)
    {
        for (int j = 0; j < 6; j++)
        {
            si[i/6][j] = x[i + j];
        }
    }

    // Substitute each one of the 8 sections getting an output of 4-bits. 
    vector<vector<bool>> so(8, vector<bool>(8, 0));
    for(int i = 0; i < 8; i++)
    {
        int r = bi_to_dec(vector<bool>{si[i][0], si[i][5]});
        int c = bi_to_dec(vector<bool>{si[i][1], si[i][2], si[i][3], si[i][4]});
        so[i] = dec_to_bi(s_boxes[i][r][c]);
    }

    // Combine the the 8 sections. 
    vector<bool> s(32, 0);
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            s[4 * i + j] = so[i][4 + j];
        }
    }

    return s;
}

// Permutation (P).
vector<bool> p (vector<bool> r)
{
    vector<bool> permuted(32, 0);
    for(int i = 0; i < 32; i++)
    {
        permuted[i] = r[p_permutation[i] - 1];
    }

    return permuted;
}

// F function (F).
vector<bool> f (vector<bool> r, vector<bool> k)
{
    r = e_table(r);
    r = x_or(r, k);
    r = s_box(r);
    r = p(r);

    return r;
}

// Round.
vector<bool> desr (vector<bool> t, vector<bool> k)
{
    vector<bool> l(32, 0), r(32, 0);
    for (int i = 0; i < 64; i++)
    {
        if (i < 32) 
        {
            l[i] = t[i];
        }

        else 
        {
            r[i - 32] = t[i];
        }  
    }

    vector<bool> F = f(r, k);

    vector<bool> temp = r;
    r = x_or(l, F), l = temp;

    for (int i = 0; i < 64; i++)    
    {
        if (i < 32) 
        {
            t[i] = l[i];
        }

        else 
        {
            t[i] = r[i - 32];  
        }
    }

    return t;
}

// 32-bit swap.
vector<bool> bs (vector<bool> b)
{
    int n = b.size();
    vector<bool> temp(n/2, 0);
    for (int i = 0; i < n; i++)
    {
        if (i < n/2) 
        {
            temp[i] = b[i];
            b[i] = b[n/2 + i];
        }

        else 
        {
            b[i] = temp[i - n/2];  
        }
    }

    return b;
}

// DES encryption.
vector<bool> dese (vector<bool> plaintext, vector<bool> key)
{
    key = pc1(key); 

    // Generate all 16 keys.
    vector<vector<bool>> k(16, vector<bool>(48, 0));
    for(int i = 0; i < 16; i++)
    {
        // Split key in half.
        vector<bool> c(28), d(28);
        for (int j = 0; j < 56; j++)    
        {
            if (j < 28) c[j] = key[j];
            else d[j - 28] = key[j];  
        }
        
        // Perform left shift to each half based on the secudual.
        c = s(c, secudual_of_left_shift[i]), d = s(d, secudual_of_left_shift[i]);

        // Combine the two halves.
        for (int j = 0; j < 56; j++)
        {
            if (j < 28) 
            {
                key[j] = c[j];
            }

            else 
            {
                key[j] = d[j - 28];
            }
        }

        // Perform permutation choice two.
        k[i] = pc2(key);
    }

    plaintext = ip(plaintext);
    
    // Perform the 16 encryption rounds.
    for (int i = 0; i < 16; i++)
    {   
        plaintext = desr(plaintext, k[i]);
    }

    // Perform 32-bit swap.
    plaintext = bs(plaintext);

    // Perform inverse initial permutation.
    plaintext = iip(plaintext);

    return plaintext;
}

// DES decryption.
vector<bool> desd (vector<bool> ciphertext, vector<bool> key)
{
    ciphertext = ip(ciphertext), key = pc1(key); 

    // Generate all 16 keys.
    vector<vector<bool>> k(16, vector<bool>(48, 0));
    for(int i = 0; i < 16; i++)
    {   
        // Split key in half.
        vector<bool> c(28), d(28);
        for (int j = 0; j < 56; j++)    
        {
            if (j < 28) 
            {
                c[j] = key[j];
            }
            else 
            {
                d[j - 28] = key[j];  
            }
        }

        // Perform left shift to each half based on the secudual.
        c = s(c, secudual_of_left_shift[i]), d = s(d, secudual_of_left_shift[i]);

        // Combine the two halves.
        for (int j = 0; j < 56; j++)
        {
            if (j < 28) 
            {
                key[j] = c[j];
            }

            else 
            {
                key[j] = d[j - 28];
            }
        }

        // Perform permutation choice two.
        k[i] = pc2(key);
    }

    // Perform the 16 decryption rounds.
    for (int i = 16; i > 0; i--)
    {   
        ciphertext = desr(ciphertext, k[i-1]);
    }

    // Perform 32-bit swap.
    ciphertext = bs(ciphertext);

    // Perform inverse initial permutation.
    ciphertext = iip(ciphertext);

    return ciphertext;
}