#include <bits/stdc++.h>
using namespace std;

/* Function to perform CRC division */
string crcDivision(string data, string generator)
{
    int m = generator.size();

    for (int i = 0; i <= data.size() - m; i++) {
        if (data[i] == '1') {
            for (int j = 0; j < m; j++) {
                data[i + j] = (data[i + j] == generator[j]) ? '0' : '1';
            }
        }
    }
    return data;
}

int main()
{
    string msg, crc;
    cout << "Enter the msg : ";
    cin >> msg;
    cout << "Enter the crc generator : ";
    cin >> crc;

    int m = crc.size();

    /* Sender side */
    string code = msg;
    code.append(m - 1, '0');   // append m-1 zeros

    string temp = crcDivision(code, crc);
    string remainder = temp.substr(temp.size() - (m - 1));

    string transmitted = msg + remainder;

    cout << "Remainder : " << remainder << endl;
    cout << "Code transmitted : " << transmitted << endl;

    /* Receiver side */
    string receiver;
    cout << "Enter the message at receiver end : ";
    cin >> receiver;

    string recvTemp = crcDivision(receiver, crc);
    string recvRemainder = recvTemp.substr(recvTemp.size() - (m - 1));

    for (char c : recvRemainder) {
        if (c != '0') {
            cout << "Error found" << endl;
            return 0;
        }
    }

    cout << "No error found" << endl;
    return 0;
}
