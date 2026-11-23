#include"elliptic_curve.h"

// Elliptic curve key exchange protocol.
int main(void)
{  
    long long a, b, p;
    long long KprA, KprB;
    vector<long long> P, KpubA, KpubB, TAB;
    
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

    return 0;
}
