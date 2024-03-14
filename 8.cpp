/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include<thread>
#include<vector>
#include<chrono>

#define CLEAN 1
#define SPEED 2
#define STOP 3
#define EXIT 100 
using namespace std;

void clean(){
    cout<<"started cleaning"<<endl;
    cout<<"it will take 3 secs to clean"<<endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
}

void speed(){
    cout<<"Speeding"<<endl;
    cout<<"it will take 3 secs to speed"<<endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
}

void stop(){
    cout<<"Stopped"<<endl;
    cout<<"it will take 3 secs to stop"<<endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
}

int main()
{
    int order;
    vector<thread> v;
    do{
        cout<<"enter you command: ";
        cin>>order;
        switch(order){
            case CLEAN:{
                thread t(clean);
                v.push_back(move(t));
                break;
            }
            case SPEED:{
                thread t1(speed);
                t1.join();
                break;
            }
            case STOP:{
                thread t2(stop);
                t2.join();
                break;
            }
            case EXIT:{
                break;
            }
            default:
                cout<<"Invalid Order"<<endl;
        }
    }while(order!=EXIT);
    for(auto &t:v){
        t.join();
    }
    return 0;
}
