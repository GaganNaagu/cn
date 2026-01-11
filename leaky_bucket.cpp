#include<iostream>
using namespace std;

int main(){
    int no_of_queries = 4;
    int bucket_size = 10;
    int input_packet_size;
    int output_packet_size = 1;
    int stored_buffer_size = 0;
    int size_left;

    for(int i=0; i<no_of_queries; i++){

        cout<<"Input Packet Size: ";
        cin>>input_packet_size;

        size_left = bucket_size - stored_buffer_size;

        if (input_packet_size <= size_left){
            stored_buffer_size += input_packet_size;
        }
        else{
            cout << "Packet Dropped" <<endl;
        }

        cout << "Stored Buffer Size: " << stored_buffer_size <<endl;

        // Fix: Only decrement if there is something in the buffer
        if(stored_buffer_size > 0)
            stored_buffer_size -= output_packet_size;
    }
    return 0;
}

/*
Example Input/Output:
Input Packet Size: 4
Stored Buffer Size: 4
Input Packet Size: 4
Stored Buffer Size: 7
Input Packet Size: 3
Stored Buffer Size: 9
Input Packet Size: 3
Packet Dropped
Stored Buffer Size: 8
*/
