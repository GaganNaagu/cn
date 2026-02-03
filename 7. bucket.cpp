#include <bits/stdc++.h>
using namespace std;

void leakyBucket() {
    int bucketSize, outRate, n;
    cout << "Enter bucket size: ";
    cin >> bucketSize;
    cout << "Enter output rate: ";
    cin >> outRate;
    cout << "Enter number of incoming packets: ";
    cin >> n;

    int stored = 0, packet;
    while (n--) {
        cout << "Enter packet size: ";
        cin >> packet;

        if (stored + packet > bucketSize)
            cout << "Packet of size " << packet << " dropped!\n";
        else {
            stored += packet;
            cout << "Packet accepted, bucket filled: " << stored << endl;
        }

        stored -= outRate;
        if (stored < 0) stored = 0;
        cout << "After sending, bucket level: " << stored << "\n\n";
    }
}

void tokenBucket() {
    int bucketSize, tokenRate, n;
    cout << "Enter bucket size: ";
    cin >> bucketSize;
    cout << "Enter token generation rate: ";
    cin >> tokenRate;
    cout << "Enter number of requests: ";
    cin >> n;

    int tokens = 0, req;
    while (n--) {
        tokens += tokenRate;
        if (tokens > bucketSize) tokens = bucketSize;

        cout << "Enter request size: ";
        cin >> req;

        if (req <= tokens) {
            tokens -= req;
            cout << "Request allowed, tokens left: " << tokens << endl;
        } else
            cout << "Request of size " << req << " denied! (Insufficient tokens)\n";

        cout << endl;
    }
}

int main() {
    int choice;
    cout << "1. Leaky Bucket Algorithm\n";
    cout << "2. Token Bucket Algorithm\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: leakyBucket(); break;
        case 2: tokenBucket(); break;
        default: cout << "Invalid choice!\n";
    }

    return 0;
}

/*
Sample Input (Leaky Bucket):
Enter your choice: 1
Enter bucket size: 10
Enter output rate: 2
Enter number of incoming packets: 3
Enter packet size: 4
Enter packet size: 10
Enter packet size: 1

Sample Output:
Packet accepted, bucket filled: 4
After sending, bucket level: 2

Packet of size 10 dropped!
After sending, bucket level: 0

Packet accepted, bucket filled: 1
After sending, bucket level: 0


Sample Input (Token Bucket):
Enter your choice: 2
Enter bucket size: 10
Enter token generation rate: 2
Enter number of requests: 3
Enter request size: 1
Enter request size: 5
Enter request size: 12

Sample Output:
Request allowed, tokens left: 1

Request of size 5 denied! (Insufficient tokens)

Request of size 12 denied! (Insufficient tokens)
*/