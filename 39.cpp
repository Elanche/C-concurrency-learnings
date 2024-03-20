#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void fun(std::stop_token token){
    while(1){
        cout<<"hii"<<endl;
        if(token.stop_requested()){
            cout<<"stop requested\n";
            return;
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void fun1(){
    while(1){
        cout<<"hi from non -interruptible\n";
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main(){
    jthread t(fun);
    jthread t1(fun1);
  
  // example of jthread - this has 2 features compared to standard C++ thread
    //1. we dont need to call join, thread life management is taken care automatically, but detach we need to call explicitly
    //2. in standard thread, we dont have any mechanism to interrupt thread, but here in jthread we have the option to interrupt using stop_token object
    //we can add condition indie thread if(token.stop_requested()) to check if any interrupt triggered and outside the thread, we can call t.request_stop() to trigger interrupt.
  
    this_thread::sleep_for(chrono::milliseconds(3000));
    t.request_stop();
    t1.request_stop();
    return 0;
}
