#include <iostream>
#include<future>
#include<thread>

using namespace std;

int fun1(){
    cout<<"fun1 id "<<std::this_thread::get_id()<<endl;
    return 1;
}

int fun2(){
    cout<<"fun2 id "<<std::this_thread::get_id()<<endl;
    return 2;
}

int fun3(){
    cout<<"fun3 id "<<std::this_thread::get_id()<<endl;
    return 3;
}

int main(){
    cout<<"main thread id "<< this_thread::get_id() <<endl;
    future<int> f1=async(launch::async, fun1);
    future<int> f2=async(launch::deferred, fun2);
    future<int> f3=async(launch::async|launch::deferred, fun3);
    
    cout<<f1.get()<<endl;   //it will create async task in different thread
    cout<<f3.get()<<endl;   //if we give async|deferred, then compiler will decide which policy to launch async
    cout<<f2.get()<<endl;
    //if we give deferred as async launch policy, then it will called only if future.get() get called
    //and it will called in the same thread
    
    return 0;
}
