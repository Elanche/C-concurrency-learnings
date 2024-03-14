#include <iostream>
#include<thread>
using namespace std;

void test(){
    cout<<"Hello from test()"<<endl;
}

void functionA(){
    thread threadC(test);
    cout<<"Hello from functionA()"<<endl;
    threadC.join();
}

void functionB(){
    cout<<"Hello from functionB()"<<endl;
}

int main()
{
    thread t1(functionA);
    thread t2(functionB);
    t1.join();
    t2.join();
    cout<<"Hello from main()"<<endl;
    return 0;
}
