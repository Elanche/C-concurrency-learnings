#include <iostream>
#include<thread>
#include<mutex>

using namespace std;

class Account{
    
    mutex m;
    string name;
    int balance;
    
    public:
    Account()=default;
    Account(string name, int balance): name{name}, balance{balance}{}
    void transfer(Account& fromAcc, Account& toAcc, int amt){
        lock_guard<mutex> lg1(fromAcc.m);
        fromAcc.balance=fromAcc.balance-amt;
        cout<<"acquired lock of "<<fromAcc.name<<"account, waiting for "<<toAcc.name<<"lock..."<<endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        lock_guard<mutex> lg2(toAcc.m);
        toAcc.balance=toAcc.balance+amt;
    }
    
};

int main(){
    Account acc;
    Account James("James", 1000);
    Account Peter("Peter", 1000);
    //simple example of deadlock situation, here 2 bank accts. are there, both James and Peter are tryig to transfer money at the same time, so here dead lock happens
    thread t1(&Account::transfer, &acc, ref(James), ref(Peter), 100);
    thread t2(&Account::transfer, &acc, ref(Peter), ref(James), 100);
    t1.join();
    t2.join();
    return 0;
}
