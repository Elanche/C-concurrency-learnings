#include <iostream>
#include<future>
#include<chrono>

using namespace std;

int calculate(){
    //some large calculation haapening, so 3s sleep i added
    this_thread::sleep_for(chrono::milliseconds(3000));
    return 1000;
}

int main(){
    //simple future example with async method
    future<int> f=async(calculate);
    cout<<f.get();
    return 0;
}
