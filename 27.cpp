#include <iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>
#include<queue>

#define TOTAL_DIST 15

using namespace std;

template<typename T>
class threadSafeQueue{
    queue<shared_ptr<T>> que;
    mutex m;
    condition_variable cv;
    
    public:
    void push(T& element){
        lock_guard<mutex> lk(m);
        que.push(make_shared<T>(element));
        cv.notify_one();
    }
    
    int size(){
        lock_guard<mutex> lk(m);
        return que.size();
    }
    
    bool empty(){
        lock_guard<mutex> lk(m);
        return que.empty();
    }
    
    shared_ptr<T> pop_wait(){
        unique_lock<mutex> lk(m);
        cv.wait(lk, [this](){ return !que.empty();});
        auto front_element=que.front();
        que.pop();
        return front_element;
    }
    
    shared_ptr<T> pop(){
        lock_guard<mutex> lk(m);
        if(que.empty()){
            return make_shared<T>();
        }
        else{
            auto front_element=que.front();
            que.pop();
            return front_element;
        }
    }
};
int main(){
    //here for condition variable, i have used notify_one, so if many threads called pop_wait function, all threads will 
    //wait at this cv.wait(), and when notify_one is called, any thread randomly will be selected and continue
    //if notify_all is used, all threads will be notified but only one thread at a time will run as lock will be acquired 
    //by one thread, so other threads wont acquire lock and continously check to acquire lock, and if lock is acqiuired, 
    //then it will check for the condition, if it fails, then again, it will go to sleep.
    return 0;
}
