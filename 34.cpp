#include <iostream>
#include<future>
#include<thread>
#include<chrono>
#include<stdexcept>
#include<cmath>
using namespace std;

void fun1(promise<int>& pr){
    int x;
    cin>>x;
    try{
        if(x<1){
            throw invalid_argument("Invalid input passed");
            
        }
        int sqr=std::sqrt(x);
        pr.set_value(sqr);
    }
    catch(exception&){
        pr.set_exception(std::current_exception());
    }
}

int main()
{
    promise<int> pr;
    future<int> fu=pr.get_future();
    
    thread t(fun1, ref(pr));
    try{
        cout<<fu.get();
    }
    catch(exception& e){
        cout<<e.what();
    }
    t.join();
    return 0;
}
