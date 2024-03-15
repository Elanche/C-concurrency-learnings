/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include<thread>
#include<chrono>

using namespace std;

void fun(){
    cout<<"inside fun "<<this_thread::get_id()<<endl;
}

int main(){
    thread t1(fun);
    thread t2=move(t1);
    thread t3;
    thread t4(fun);
    cout<<"thread 1 id "<<t1.get_id()<<endl;
    t2.join();
    cout<<"thread 2 id "<<t2.get_id()<<endl;
    cout<<"thread 3 id "<<t3.get_id()<<endl;
    cout<<"thread 4 id "<<t4.get_id()<<endl;
    t4.join();
    cout<<"number of cores available "<<thread::hardware_concurrency()<<endl;
    
    return 0;
}
