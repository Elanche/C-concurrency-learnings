#include <iostream>
#include<thread>
#include<chrono>

using namespace std;

class thread_guard{
    thread& t;
    
    public:
    explicit thread_guard(thread &_t):t{_t}{}
    thread_guard(const thread_guard& t)=delete;
    thread_guard& operator=(const thread_guard& t)=delete;
    
    ~thread_guard(){
        if(t.joinable()){
            t.join();
        }
    }
};

void fun(){
    cout<<"foo function"<<endl;
}

void samp(){
    throw runtime_error("runtime err..");
}

int main(){
    thread t1(fun);
    thread_guard tg(t1);
    try{
        samp();
    }
    catch(...){
        
    }
    
    return 0;
}
