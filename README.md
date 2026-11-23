# Encryption

C++ implementations of classic cryptography algorithms, written from scratch for a university cryptography course. No crypto libraries are used.

| Algorithm | Type | Standalone version | Report |
|---|---|---|---|
| DES | Symmetric block cipher | `standalone/des` (with tests) | `docs/des.pdf` |
| AES | Symmetric block cipher | `standalone/aes` (with tests) | `docs/aes.pdf` |
| RSA | Public-key encryption | `standalone/rsa` | `docs/rsa.pdf` |
| Digital signature | RSA-based signing | `standalone/digital-signature` | `docs/digital-signature.pdf` |
| Diffie-Hellman | Key exchange | `standalone/diffie-hellman` | `docs/diffie-hellman-and-elgamal.pdf` |
| ElGamal | Public-key encryption | `standalone/elgamal` | `docs/diffie-hellman-and-elgamal.pdf` |
| Elliptic curve | Elliptic-curve cryptography | `standalone/elliptic-curve` | `docs/elliptic-curve.pdf` |

## Layout

- `combined/`: the final version. One program with all algorithms behind a shared interface (`interfaces.h`).
- `standalone/`: the first version of each algorithm as its own program. `standalone/shared/` holds the helper files they all use (`math.h`, `utilities.h`, `rsa.h`).
- `standalone/aes/testing` and `standalone/des/testing`: programs that check the inner operations and the input/output against reference values.
- `docs/`: the report for each algorithm, plus reference material used for testing.

## Build and run

Any C++17 compiler works. For example, with g++:

```
cd combined
g++ -std=c++17 main.cpp -o main
./main
```

The same command works inside any `standalone/...` folder.

## Note

These are learning implementations. Do not use them to protect real data.
