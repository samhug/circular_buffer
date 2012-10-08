#include <iostream>

#include "circular_buffer.h"

using namespace std;

int main(int argc, char* argv[]) {
    CircularBuffer<int> *buffer = new CircularBuffer <int> (5);
    int o;

    for (int i=0; i<=100; i++) {
        buffer->write(&i, 1);
        buffer->read(&o, 1);
	cout << o;
    }
    cout << endl;

    /*
    for (char i='a'; i<='z'; i++) {
        buffer->write(&i, 1);
    }
    for (char i='a'; i<='z'; i++) {
        buffer->read(&o, 1);
	cout << o;
    }
    cout << endl;
    */
}
