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
    
}

int main()
{
    thread t1(fun);
    thread t2=move(t1);
    
//    t2=t1; //we cannot assign thread to another thread, copy assignment is deleted
    thread  t3=move(t2);
    t1=thread(fun);//here no need to add move function, because rhs is r-value, so implicait move happens here
    t1.join();
//    t2.join();//we cannot join t2 as it is moved to another thread, so it is not valid thread, ownership is transferred 
    t3.join();
    return 0;
}
