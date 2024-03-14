#include <iostream>
#include<thread>

using namespace std;

int main()
{
    thread t1;
    if(t1.joinable()){
        cout<<"t1 is joinable"<<endl;
        t1.join();
    }
    else{
        cout<<"t1 is not joinable"<<endl;
    }
    return 0;
}
