#include<iostream>
#include <thread>

using namespace std;

class A{
    public:
    void operator()(){
        cout<<"this thread is function object"<<this_thread::get_id()<<endl;
    }
};

class B{
    public:
    void fun(){
        cout<<"this thread is function member"<<this_thread::get_id()<<endl;
    }
};

void fun(){
    cout<<"this thread is fun"<<this_thread::get_id()<<endl;
}

int main(){
    thread t1(&fun);
    A a;
    thread t2(a);
    thread t3([](){
        cout<<"this thread is lambda"<<this_thread::get_id()<<endl;
    });
    cout<<"this thread is main"<<this_thread::get_id()<<endl;
    B b;
    thread t4(&B::fun, b);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
