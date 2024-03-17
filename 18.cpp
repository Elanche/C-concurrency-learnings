#include <iostream>
#include<thread>
#include<mutex>
#include<list>

using namespace std;

class threadSafeList{
    list<int> protectedData;
    mutex m;
    
    int get_size(){
        lock_guard<mutex> lg(m);
        cout<<"size is "<<protectedData.size()<<endl;
        return protectedData.size();
    }
    
    void add(){
        lock_guard<mutex> lg(m);
        protectedData.push_back(10);
        cout<<"added"<<endl;
    }
    
    void delet(){
        lock_guard<mutex> lg(m);
        protectedData.pop_back();
        cout<<"removed"<<endl;
    }
    
    list<int>* returnDataPtr(){
        lock_guard<mutex> lg(m);
        return &protectedData;        //point 1
    }
    
    template<typename funPtr>
    void extFun(funPtr function){
        lock_guard<mutex> lg(m);
        function(protectedData);      //point 2
    }
};

void malicious_code(list<int>* l){
    auto unprotectedData=l;
}

int main(){
    //problematic situations when using mutex
    //1. when you return protected data as a pointer or reference, if you return this, then even thought if you used mutex in your implementation class, whoever using this pointer may not use mutex, so it becomes thread unsafe
    //2. when you pass external function which you dont have control to your protected data, this function take can pointer to proptected data and do whatever it want, so now it become thread unsafe
    //even though you implemented a class which is thread safe, doing point 1 and point 2 make it thread unsafe...
    return 0;
}
