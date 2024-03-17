#include <iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<condition_variable>

#define TOTAL_DIST 15

using namespace std;

int distance_covered=0, my_distance=10;
mutex m;
condition_variable cv;

void driveBus(){
    while(distance_covered!=TOTAL_DIST){
        this_thread::sleep_for(chrono::milliseconds(1000));
        distance_covered++;
        cout<<"bus is running and reached this distance "<<distance_covered<<"\n";
        if(distance_covered==my_distance){
            this_thread::sleep_for(chrono::milliseconds(3000));
            cv.notify_one();
        }
    }
}

void be_awake_and_be_with_driver(){
    while(distance_covered<my_distance){
        
    }
    cout<<"i have reached by talking to driver\n";
}

void awakeByAlarm(){
    this_thread::sleep_for(chrono::milliseconds(10000));
    if(distance_covered<my_distance){
        cout<<"im awake by alram but before reaching my destination\n";
    }
    else if(distance_covered>my_distance){
        cout<<"im awake by alram but i missed my destination\n";
    }
    else{
        cout<<"im awake by alarm and reached my destination on time\n";
    }
}

void awakeCondVar(){
    unique_lock lk(m);
    cv.wait(lk, [](){return distance_covered==my_distance;});
    cout<<"i have reached by destination by condition variable\n";
}

int main(){
    thread driver(driveBus);
    thread Me_awake(be_awake_and_be_with_driver);
    thread Me_alarm(awakeByAlarm);
    thread Me_usingCondVariable(awakeCondVar);
    driver.join();
    Me_awake.join();
    Me_alarm.join();
    Me_usingCondVariable.join();
    return 0;
}
