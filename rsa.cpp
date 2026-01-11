#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    while (b != 0)
    {
        int r = b;
        b = a % b;
        a = r;
    }
    return a;
}

long exp(long a, long b, long n)
{
    long res = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
            res = (res * a) % n;
        a = (a * a) % n;
        b /= 2;
    }
    return res;
}

int main()
{
    int p, q;
    cout << "Enter 2 prime nos p & q: ";
    cin >> p >> q;

    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e;

    cout << "Enter public key e (1 < e < phi) & gcd(e, phi) = 1: ";
    cin >> e;

    int d = 0;
    for (int i = 1; i < phi; i++)
    {
        if ((e * i) % phi == 1)
        {
            d = i;
            break;
        }
    }

    cout << "Public Key: (" << e << ", " << n << ")\n";
    cout << "Private Key: (" << d << ", " << n << ")\n";

    long msg;
    cout << "Enter msg to encrypt: ";
    cin >> msg;

    long enc = exp(msg, e, n);
    long dec = exp(enc, d, n);

    cout << "Encrypted msg: " << enc << endl;
    cout << "Decrypted msg: " << dec << endl;

    return 0;
}