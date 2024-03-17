#include <iostream>
#include<thread>

using namespace std;

//atomic<int> i=0;
thread_local atomic<int> i=0;

void a(){
    i++;
    cout<<i;
}

int main(){
    thread t1(a);
    thread t2(a);
    thread t3(a);
    
    t1.join();
    t2.join();
    t3.join();
}
