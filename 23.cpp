#include <iostream>
#include<thread>
#include<chrono>

using namespace std;

thread t1, t2;

void fun1(){
    this_thread::sleep_for(chrono::milliseconds(2000));
    if(t2.joinable()){
        cout<<"joinable";
        t2.join();
    }
    else{
        cout<<"not joinable";
    }
}

void fun2(){
    this_thread::sleep_for(chrono::milliseconds(2000));
    if(t1.joinable()){
        cout<<"joinable";
        t1.join();
    }
    else{
        cout<<"not joinable";
    }
}

int main(){
    t1=move(thread(fun1));
    t2=move(thread(fun2));
    
    //deadlock using thread join, deadlock not only happens due to mutex, but also join like this
    //trying to join t1 in t2 & trying to join t2 in t1
    if(t1.joinable()){
        t1.join();
    }
    if(t2.joinable()){
        t2.join();
    }
    return 0;
}
