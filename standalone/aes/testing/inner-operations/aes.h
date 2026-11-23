#include"../../../shared/math.h"

// Substitution box.
const int sbox[16][16] = 
{
    {99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254, 215, 171, 118},
    {202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175, 156, 164, 114, 192},
    {183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229, 241, 113, 216, 49, 21},
    {4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128, 226, 235, 39, 178, 117},
    {9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214, 179, 41, 227, 47, 132},
    {83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190, 57, 74, 76, 88, 207},
    {208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2, 127, 80, 60, 159, 168},
    {81, 163, 64, 143, 146, 157, 56, 245, 188, 182, 218, 33, 16, 255, 243, 210},
    {205, 12, 19, 236, 95, 151, 68, 23, 196, 167, 126, 61, 100, 93, 25, 115},
    {96, 129, 79, 220, 34, 42, 144, 136, 70, 238, 184, 20, 222, 94, 11, 219},
    {224, 50, 58, 10, 73, 6, 36, 92, 194, 211, 172, 98, 145, 149, 228, 121},
    {231, 200, 55, 109, 141, 213, 78, 169, 108, 86, 244, 234, 101, 122, 174, 8},
    {186, 120, 37, 46, 28, 166, 180, 198, 232, 221, 116, 31, 75, 189, 139, 138},
    {112, 62, 181, 102, 72, 3, 246, 14, 97, 53, 87, 185, 134, 193, 29, 158},
    {225, 248, 152, 17, 105, 217, 142, 148, 155, 30, 135, 233, 206, 85, 40, 223},
    {140, 161, 137, 13, 191, 230, 66, 104, 65, 153, 45, 15, 176, 84, 187, 22}
};

// Inverse substitution box.
const int inv_sbox[16][16] = 
{
    {82, 9, 106, 213, 48, 54, 165, 56, 191, 64, 163, 158, 129, 243, 215, 251},
    {124, 227, 57, 130, 155, 47, 255, 135, 52, 142, 67, 68, 196, 222, 233, 203},
    {84, 123, 148, 50, 166, 194, 35, 61, 238, 76, 149, 11, 66, 250, 195, 78},
    {8, 46, 161, 102, 40, 217, 36, 178, 118, 91, 162, 73, 109, 139, 209, 37},
    {114, 248, 246, 100, 134, 104, 152, 22, 212, 164, 92, 204, 93, 101, 182, 146},
    {108, 112, 72, 80, 253, 237, 185, 218, 94, 21, 70, 87, 167, 141, 157, 132},
    {144, 216, 171, 0, 140, 188, 211, 10, 247, 228, 88, 5, 184, 179, 69, 6},
    {208, 44, 30, 143, 202, 63, 15, 2, 193, 175, 189, 3, 1, 19, 138, 107},
    {58, 145, 17, 65, 79, 103, 220, 234, 151, 242, 207, 206, 240, 180, 230, 115},
    {150, 172, 116, 34, 231, 173, 53, 133, 226, 249, 55, 232, 28, 117, 223, 110},
    {71, 241, 26, 113, 29, 41, 197, 137, 111, 183, 98, 14, 170, 24, 190, 27},
    {252, 86, 62, 75, 198, 210, 121, 32, 154, 219, 192, 254, 120, 205, 90, 244},
    {31, 221, 168, 51, 136, 7, 199, 49, 177, 18, 16, 89, 39, 128, 236, 95},
    {96, 81, 127, 169, 25, 181, 74, 13, 45, 229, 122, 159, 147, 201, 156, 239},
    {160, 224, 59, 77, 174, 42, 245, 176, 200, 235, 187, 60, 131, 83, 153, 97},
    {23, 43, 4, 126, 186, 119, 214, 38, 225, 105, 20, 99, 85, 33, 12, 125}
};

// Round constant.
const int rc[10] = {1, 2, 4, 8, 16, 32, 64, 128, 27, 54};

// AES key.
string aesk (int n = 16)
{
    vector<long long> d(n, 0);
    srand(time(nullptr));
    for (int i = 0; i < n; i++)
    {
        d[i] = rand();
    }
    return dec_to_str(d);
}

// RotWord performs a one-byte circular left shift on a word. This means that an input word.
void rot_word (vector<bool> &w)
{
    vector<vector<bool>> bytes = split(w);
    vector<bool> first_byte = bytes[0];
    for (int i = 0; i < 3; i++)
    {
        bytes[i] = bytes[i + 1];
    }
    bytes[3] = first_byte;
    w = combine(bytes);
}

// SubWord performs a byte substitution on each byte of its input word, using the S-box.
void sub_word (vector<bool> &w)
{
    vector<vector<bool>> bytes = split(w);
    int n = bytes.size();
    for (int i = 0; i < n; i++)
    {
        vector<bool> byte = bytes[i];
        int r = bi_to_dec(vector<bool>{byte[0], byte[1], byte[2], byte[3]});
        int c = bi_to_dec(vector<bool>{byte[4], byte[5], byte[6], byte[7]});
        bytes[i] = dec_to_bi(sbox[r][c]);
    }

    w = combine(bytes);
}

// g function (g).
vector<bool> g (vector<bool> w, int j)
{
    // RotWord performs a one-byte circular left shift on a word.
    rot_word(w);

    // SubWord performs a byte substitution on each byte of its input word, using the S-box.
    sub_word(w);
    
    // XOR first byte with 
    w = x_or(w, dec_to_bi(rc[j]));
    
    return w;
}

// Key expansion.
vector<vector<bool>> key_expansion (vector<bool> key)
{
    int key_size = key.size();
    int no_words = key_size / 32;
    int no_rounds = no_words + 6;
    
    vector<vector<bool>> k(no_rounds + 1, vector<bool>(key_size)); 
    vector<vector<bool>> w(no_words, vector<bool>(32)); 

    // Split key to n words.
    for (int i = 0; i < no_words; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            w[i][j] = key[32 * i + j];
        }
    }

    // Key expansion algorithm.
    for(int i = 0; i <= no_rounds ; i++)
    {
        k[i] = combine(w);
        for (int j = 0; j < no_words; j++)
        {
            // Simple XOR using the symbol g to represent that complex function.
            if (j == 0) 
            {
                w[j] = x_or(w[j], g(w[no_words - 1], i));
            }
            
            // Simple XOR with output of the previous word.
            else
            {
                w[j] = x_or(w[j], w[j - 1]);
            } 
        }
    }

    return k;
}

// Initial transformation.
void initial_transformation (vector<bool> &input_state, vector<bool> key)
{
    input_state = x_or(input_state, key);
}

// Substitute bytes.
void substitute_bytes (vector<bool> &b)
{
    vector<vector<bool>> bytes = split(b);
    for (int i = 0; i < 16; i++)
    {
        vector<bool> byte = bytes[i];
        int r = bi_to_dec(vector<bool>{byte[0], byte[1], byte[2], byte[3]});
        int c = bi_to_dec(vector<bool>{byte[4], byte[5], byte[6], byte[7]});
        bytes[i] = dec_to_bi(sbox[r][c]);
    }
    
    b = combine(bytes);
}

// Inverse substitute bytes.
void inverse_substitute_bytes (vector<bool> &b)
{
    vector<vector<bool>> bytes = split(b);
    int n = bytes.size();
    for (int i = 0; i < n; i++)
    {
        vector<bool> byte = bytes[i];
        int r = bi_to_dec(vector<bool>{byte[0], byte[1], byte[2], byte[3]});
        int c = bi_to_dec(vector<bool>{byte[4], byte[5], byte[6], byte[7]});
        bytes[i] = dec_to_bi(inv_sbox[r][c]);
    }
    
    b = combine(bytes);
}

// Shift rows.
void shift_rows (vector<bool> &b)
{
    vector<vector<bool>> temp = split(b), bytes = split(b);
    for (int i = 0; i < 16; i+=4)
    {
        for (int j = 0; j < 16; j+=5)
        {
            bytes[(j / 4) + i] = temp[(i + j) % 16];
        }
    }

    b = combine(bytes);
}

// Inverse shift rows.
void inverse_shift_rows (vector<bool> &b)
{
    vector<vector<bool>> temp = split(b), bytes = split(b);
    for (int i = 0; i < 16; i+=4)
    {
        for (int j = 0; j < 16; j+=5)
        {
            bytes[(i + j) % 16] = temp[(j / 4) + i];
        }
    }

    b = combine(bytes);
}

// Mix columns.
void mix_columns (vector<bool> &w)
{
    vector<int> pm = {2, 1, 1, 3, 3, 2, 1, 1, 1, 3, 2, 1, 1, 1, 3, 2};
    vector<vector<bool>> b1 = split(w);
    vector<vector<bool>> b2(16, vector<bool>(8));
    for (int i = 0; i < 16; i++)
    {
        b2[i] = dec_to_bi(pm[i]);
    }
    
    vector<vector<vector<bool>>> m1 (4, vector<vector<bool>>(4, vector<bool>(8))), m2(4, vector<vector<bool>>(4, vector<bool>(8)));
    for (int i = 0; i < 16; i++)
    {
        m1[i / 4][i % 4] = b1[i];
        m2[i / 4][i % 4] = b2[i];
    }

    vector<vector<bool>> d(16, vector<bool>(8, 0));
    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 4; ++j) 
        {
            vector<bool> sum = {0, 0, 0, 0, 0, 0, 0, 0};
            vector<vector<bool>> gf = {{0, 0, 0, 1, 1, 0, 1, 1}, {0, 0, 1, 1, 0, 1, 1, 0}, {0, 1, 1, 0, 1, 1, 0, 0}, {1, 1, 0, 1, 1, 0, 0, 0}};
            for (int k = 0; k < 4; k++)
            {
                vector<bool> mul;
                vector<bool> v1 = m1[i][k], v2 = m2[k][j];

                mul = mul_bi(v1, v2);
                    
                if (mul.size() > 8)
                {
                    vector<bool> gf2(8, 0);
                    for (int i = 0; i < 4; i++)
                    {
                        if (mul[7 - i] == 1)
                        {
                            gf2 = x_or(gf2, gf[i]);
                        }
                    }
                    mul.erase(mul.begin(), mul.begin() + 8);
                    mul = x_or(gf2, mul);
                }
                
                sum = x_or(sum, mul);
            }
            d[(i * 4) + j] = sum;
        }
    }

    w =  combine(d);   
}

// Inverse mix columns.
void inverse_mix_columns (vector<bool> &w)
{
    vector<int> pm = {14, 9, 13, 11, 11, 14, 9, 13, 13, 11, 14, 9, 9, 13, 11, 14};
    vector<vector<bool>> b1 = split(w);
    vector<vector<bool>> b2(16, vector<bool>(8));
    for (int i = 0; i < 16; i++)
    {
        b2[i] = dec_to_bi(pm[i]);
    }
    
    vector<vector<vector<bool>>> m1 (4, vector<vector<bool>>(4, vector<bool>(8))), m2(4, vector<vector<bool>>(4, vector<bool>(8)));
    for (int i = 0; i < 16; i++)
    {
        m1[i / 4][i % 4] = b1[i];
        m2[i / 4][i % 4] = b2[i];
    }

    vector<vector<bool>> d(16, vector<bool>(8, 0));
    for (int i = 0; i < 4; ++i) 
    {
        for (int j = 0; j < 4; ++j) 
        {
            vector<vector<bool>> gf = {{0, 0, 0, 1, 1, 0, 1, 1}, {0, 0, 1, 1, 0, 1, 1, 0}, {0, 1, 1, 0, 1, 1, 0, 0}, {1, 1, 0, 1, 1, 0, 0, 0}};
            vector<bool> sum = {0, 0, 0, 0, 0, 0, 0, 0};
            for (int k = 0; k < 4; k++)
            {
                vector<bool> mul;
                vector<bool> v1 = m1[i][k], v2 = m2[k][j];
                
                mul = mul_bi(v1, v2);
                    
                if (mul.size() > 8)
                {
                    vector<bool> gf2(8, 0);
                    for (int i = 0; i < 4; i++)
                    {
                        if (mul[7 - i] == 1)
                        {
                            gf2 = x_or(gf2, gf[i]);
                        }
                    }
                    mul.erase(mul.begin(), mul.begin() + 8);
                    mul = x_or(gf2, mul);
                }
                
                sum = x_or(sum, mul);
            }
            d[(i * 4) + j] = sum;
        }
    }

    w =  combine(d);   
}

// Add round key.
void add_round_key (vector<bool> &b, vector<bool> k)
{
    b = x_or(b, k);
}

// AES encryption round.
vector<bool> aeser (vector<bool> b, vector<bool> k)
{
    // Uses an S-box to perform a byte-by-byte substitution of the block.
    substitute_bytes(b);

    // A simple permutation.
    shift_rows(b);

    //  A substitution that makes use of arithmetic over GF (2^8).
    mix_columns(b);

    // A simple bitwise XOR of the current block with a portion of the expanded key. c
    add_round_key(b, k);

    return b;
}

// AES decryption round.
vector<bool> aesdr (vector<bool> b, vector<bool> k)
{
    // A simple permutation.
    inverse_shift_rows(b);

    // Uses an S-box to perform a byte-by-byte substitution of the block.
    inverse_substitute_bytes(b);

    // A simple bitwise XOR of the current block with a portion of the expanded key. c
    add_round_key(b, k);

    // A substitution that makes use of arithmetic over GF (2^8).
    inverse_mix_columns(b);

    return b;
}

// AES encryption.
vector<bool> aese (vector<bool> plaintext, vector<bool> key)
{
    vector<vector<bool>> k = key_expansion(key);
    int n = k.size() - 1;

    initial_transformation(plaintext, k[0]);

    for (int i = 1; i < n; i++)
    {
        plaintext = aeser(plaintext, k[i]);
    }

    substitute_bytes(plaintext);
    shift_rows(plaintext);
    add_round_key(plaintext, k[n]);

    return plaintext;
}

// AES decryption.
vector<bool> aesd (vector<bool> ciphertext, vector<bool> key)
{
    vector<vector<bool>> k = key_expansion(key);
    int n = k.size() - 1;

    initial_transformation(ciphertext, k[n]);

    for (int i = 1; i < n; i++)
    {
        ciphertext = aesdr(ciphertext, k[n - i]);
    }

    inverse_shift_rows(ciphertext);
    inverse_substitute_bytes(ciphertext);
    add_round_key(ciphertext, k[0]);

    return ciphertext;
}