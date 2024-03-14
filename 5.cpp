#include <iostream>
#include<thread>
#include<chrono>

using namespace std;

void fun(){
    cout<<"fun from t1 "<<endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout<<"after sleep from t1 "<<endl;
}

int main()
{
    thread t1(fun);
    cout<<"before join"<<endl;
    t1.detach();
    cout<<"after join"<<endl;
    return 0;
}
