#include <iostream>
#include<thread>
#include<mutex>

using namespace std;
void y_operations(){cout<<"y";}
void x_operations(){cout<<"x";}

mutex m;

unique_lock<mutex> getLock(){
    unique_lock<mutex> lk(m);
    x_operations();
    return lk;
}

int main(){
    unique_lock<mutex> lk(getLock());
    //unique_lock is movable, not copy constructable or copy assignable
    //this is an example to show it is movable
    y_operations();
    return 0;
}
