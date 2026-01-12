#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

double calculateAvg(double prevAvg, int qSize, double wq) {
    return ((1 - wq) * prevAvg) + (wq * qSize);
}

int main() {
    srand(time(0));

    double wq, minTh, maxTh, maxP;
    int packets, qSize = 0;

    cout << "Enter number of incoming packets: ";
    cin >> packets;

    cout << "Enter wq (0.0 to 1.0): ";
    cin >> wq;

    cout << "Enter min threshold: ";
    cin >> minTh;

    cout << "Enter max threshold: ";
    cin >> maxTh;

    cout << "Enter max drop probability: ";
    cin >> maxP;

    double avg = 0;

    for (int i = 1; i <= packets; i++) {
        cin >> qSize;

        avg = calculateAvg(avg, qSize, wq);

        if (avg < minTh)
            cout << "ACCEPTED\n";
        else if (avg >= minTh && avg < maxTh) {
            double pb = maxP * (avg - minTh) / (maxTh - minTh);
            double rnd = (double)rand() / RAND_MAX;

            if (rnd < pb) cout << "DROPPED\n";
            else cout << "ACCEPTED\n";
        }
        else
            cout << "DROPPED\n";
    }
}

/*
Sample Input:
Enter number of incoming packets: 5
Enter wq (0.0 to 1.0): 0.5
Enter min threshold: 10
Enter max threshold: 20
Enter max drop probability: 0.5
15
5
25
10
12

Sample Output:
ACCEPTED
ACCEPTED
ACCEPTED (or DROPPED based on random probability)
ACCEPTED
ACCEPTED
*/