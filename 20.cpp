#include <iostream>
#include<thread>
#include<mutex>
#include<stack>
#include<memory>

using namespace std;

template<typename T>
class threadSafeStack{
    stack<shared_ptr<T>> protectedData;
    mutex m;
    
    int get_size(){
        lock_guard<mutex> lg(m);
        cout<<"size is "<<protectedData.size()<<endl;
        return protectedData.size();
    }
    
    bool empty_push(T data){
        lock_guard<mutex> lg(m);
        if(!protectedData.empty()){
            protectedData.push(make_shared(data));
            cout<<"added"<<endl;
            return true;
        }
        return false;
    }
    
    shared_ptr<T> empty_pop(){
        lock_guard<mutex> lg(m);
        if(!protectedData.empty()){
            auto element=protectedData.top();
            protectedData.pop();
            cout<<"removed"<<endl;
            return element;
        }
        return nullptr;
    }
    
    bool empty(){
        lock_guard<mutex> lg(m);
        return protectedData.empty();
    }
};

int main(){
    //here we implemented thread safe stack, we are having issue if we use empty, pop, push seperately, 
    //so we combined empty_push, here empty and push are combined
    //empty_pop, here empty and pop are combined 
    //we are using shared pointer to avoid exception, when returning data from pop function, 
    //some systems may be memory constraint applications, that time, we cant return data by value, 
    //it need ot call copy constructor, so to avoid that we can return pointer of created that structure
    //so we are using shared_ptr instead of raw pointer, incase we need to explicitly use delete,
    //so we are using shared_ptr here
    return 0;
}
