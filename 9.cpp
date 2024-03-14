#include <iostream>
#include<thread>
#include<chrono>

using namespace std;

void fun(int& i){
    
        cout<<"printing from fun before "<<i<<endl;
        this_thread::sleep_for(chrono::milliseconds(5000));
        cout<<"printing from fun before "<<i<<endl;
}

int main()
{
    int i=10;
    thread t(fun, ref(i));
    i=20;
    t.join();
    return 0;
}
