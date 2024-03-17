#include <iostream>
#include<thread>
#include<mutex>

using namespace std;

mutex m1, m2;

void fun1(){
    m1.lock();
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout<<"Acquired m1, waiting for m2\n";
    m2.lock();
    m2.unlock();
    m1.unlock();
}

void fun2(){
    m2.lock();
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout<<"Acquired m2, waiting for m2\n";
    m1.lock();
    m1.unlock();
    m2.unlock();
}

int main(){
    thread t1(fun1);
    thread t2(fun2);
    //simple deadlock example, due to order of mutex locked, deadlock happens
    t1.join();
    t2.join();
    return 0;
}
