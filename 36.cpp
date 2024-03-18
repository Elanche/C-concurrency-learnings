#include <iostream>
#include<future>
#include<thread>
#include<chrono>
#include<stdexcept>
#include<cmath>
using namespace std;

void fun1(promise<int>& pr){
    pr.set_value(100);
}

void fun2(shared_future<int>& fu){
    if(fu.valid()){
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout<<fu.get()<<endl;
    }
    else{
        cout<<"future is invalid\n";
    }
}

int main()
{
    promise<int> pr;
    shared_future<int> fu=pr.get_future();
    
    thread t1(fun1, ref(pr));
    thread t2(fun2, ref(fu));
    thread t3(fun2, ref(fu));
    //if more than one thread accessing future, to avoid exception in future, we can use shared_future object.
    //this can be access .get() method many number of times, wont cause any exception
    //in same code, instead of future, i used shared_future object...
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
