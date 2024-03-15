//demonstrating invalid use of passing reference to thread
#include <iostream>
#include<thread>
#include<chrono>

using namespace std;

void fun1(int& i) {
    while (1) {
        try {
            this_thread::sleep_for(chrono::milliseconds(1000));
            cout << i << endl;
        }
        catch (...) {
            throw std::runtime_error("invlaid access");
        }
    }
}

void fun() {
    int i = 9;
    thread t(fun1, ref(i));
    t.detach();
}

int main(){
    thread t(fun);
    this_thread::sleep_for(chrono::milliseconds(5000));
    t.join();
    this_thread::sleep_for(chrono::milliseconds(10000));
    return 0;
}
