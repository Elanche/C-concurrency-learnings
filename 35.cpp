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

void fun2(future<int>& fu){
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
    future<int> fu=pr.get_future();
    
    thread t1(fun1, ref(pr));
    thread t2(fun2, ref(fu));
    thread t3(fun2, ref(fu));
    //future becomes invalid once .get function is called, so we cannot call future.call() method
    //more than once.
    //for this, we can use if(future.valid()) function, but here i have shown the example where
    //we are having race condition between 2 threads, both threads are entering the if condition 
    //but after entering, one thread calls future.get() and it becomes invalis, so now if other thread also 
    //calls and execption happens
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
