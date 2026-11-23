#include"diffie_hellman.h"

// DHKE
int main()
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

    return 0;
}