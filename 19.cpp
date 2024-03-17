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
    
    bool empty(){
        lock_guard<mutex> lg(m);
        return protectedData.empty();
    }
};

int main(){
    //trivial thread safe list data structure, but here interface inherit race conditions exist
    //for example, 2 thread check if list is empty or not, then thread 1 do some and thread 2 do some operation
    // t1                                     t2
    //if(l.empty())                          if(l.empty())
    //      l.pop();                    list has only one element, so now it became empty, now t2 tries to pop again
    //                                              l.pop()
    //                                  here exception happens due to popping in empty list
    //there are many such scenarios exist, even though the data structure implemented thread safe inside, 
    //still threr are many interface inherit race conditions exist...
    return 0;
}
