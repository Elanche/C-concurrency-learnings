#include <iostream>
#include<future>
#include<thread>
#include<chrono>

using namespace std;

void fun(promise<int>& pr){
    pr.set_value(10);
}

int main()
{
    promise<int> pr;
    future<int> fu=pr.get_future();
    
    thread t(fun, ref(pr));
    cout<<fu.get();
    
    t.join();
    return 0;
}
