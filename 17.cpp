#include <iostream>
#include<thread>
#include<mutex>
#include<list>

using namespace std;

list<int> l;
mutex m;

void get_size(){
    lock_guard<mutex> lg(m);
    //m.lock();
    cout<<"size is "<<l.size();
    //m.unlock();
}

void add(){
    //m.lock();
    lock_guard<mutex> lg(m);
    l.push_back(10);
    //m.unlock();
}

int main(){
    l.push_back(1);
    thread t1(get_size);
    thread t2(add);
    t1.join();
    t2.join();
}
