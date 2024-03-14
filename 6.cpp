#include <iostream>
#include<thread>
#include<chrono>

using namespace std;

void fun(){
    throw runtime_error("sample err");
}

void samp(){
    cout<<"sample function"<<endl;
}
int main()
{
    thread t1(samp);
    try{
        fun();
        t1.join();
    }
    catch(...){
        t1.join();
    }
    return 0;
}
