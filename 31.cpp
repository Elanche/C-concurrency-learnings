#include <iostream>
//#include<packaged_task>
#include<future>
#include<thread>
#include<chrono>

using namespace std;

int add(int x, int y){
    cout<<"packaged_task thread id "<<this_thread::get_id()<<endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    return x+y;
}

int main()
{
    //packaged_task example
    //you need to provide the parameter and return type as template paramter list while declaring packaged_task
    //you need to provide the callable object as argument while constructing packaged_task
    //associate a future for packaged_task
    //unlinke async, packaged_task wont be called automatically during its construction, we need to explicitly call it
    //as soon as we call it, it will asynchronously which means it run on the same thread
    cout<<"main thread id "<<this_thread::get_id()<<endl;
    packaged_task<int(int, int)> add_task(add);
    future<int> f=add_task.get_future();
    thread t(move(add_task), 1, 2);
    //here im executing packaged_task in a seperate thread instead of same thread by passing it to std::thread
    t.detach();
    //you can either join or detach because once we call future.get() method, until it is 
    //set, the thread will wait will value is set inside future.
    cout<<f.get();
    return 0;
}
