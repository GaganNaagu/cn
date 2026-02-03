#include <bits/stdc++.h>
using namespace std;

// GCD function
long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long r = b;
        b = a % b;
        a = r;
    }
    return a;
}

// Modular Exponentiation
long long exp(long long a, long long b, long long n)
{
    long long res = 1;
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
    long long p, q;
    cout << "Enter 2 prime nos p & q: ";
    cin >> p >> q;

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e;

    cout << "Enter public key e (1 < e < phi) & gcd(e, phi) = 1: ";
    cin >> e;

    // Check if e is valid
    if (e >= phi || gcd(e, phi) != 1) {
        cout << "Invalid e! Try again." << endl;
        return 1;
    }

    long long d = 0;
    for (long long i = 1; i < phi; i++)
    {
        if ((e * i) % phi == 1)
        {
            d = i;
            break;
        }
    }

    cout << "Public Key: (" << e << ", " << n << ")\n";
    cout << "Private Key: (" << d << ", " << n << ")\n";

    long long msg;
    cout << "Enter msg to encrypt: ";
    cin >> msg;

    long long enc = exp(msg, e, n);
    long long dec = exp(enc, d, n);

    cout << "Encrypted msg: " << enc << endl;
    cout << "Decrypted msg: " << dec << endl;

    return 0;
}

/*
Example Input/Output:
Enter 2 prime nos p & q: 3 7
Enter public key e (1 < e < phi) & gcd(e, phi) = 1: 5
Public Key: (5, 21)
Private Key: (5, 21)
Enter msg to encrypt: 3
Encrypted msg: 12
Decrypted msg: 3
*/