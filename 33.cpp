#include <iostream>
#include<future>
#include<thread>
#include<chrono>

using namespace std;

void fun1(future<int>& fu){
    cout<<fu.get();
    
}

int main()
{
    promise<int> pr;
    future<int> fu=pr.get_future();
    
    thread t(fun1, ref(fu));
    
    //classic deadlock example, where im joining the thread before setting the value in promise
    //and the joinning thread having the get call for future, so im trying to get before setting
    //this is a classic deadlock situation and we need to be careful and avoid these situations
    t.join();
    pr.set_value(100);
    return 0;
}
