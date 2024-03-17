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
        unique_lock<mutex> lk1(fromAcc.m, std::defer_lock);
        unique_lock<mutex> lk2(toAcc.m, defer_lock);
        lock(lk1, lk2);
        fromAcc.balance=fromAcc.balance-amt;
        toAcc.balance=toAcc.balance+amt;
        cout<<"from acc "<<fromAcc.balance<<" to acc "<<toAcc.balance<<endl;
    }
};

int main(){
    Account acc;
    Account James("James", 1000);
    Account Peter("Peter", 1000);
    //in the same code, we saw deadlock when using lock_guard, to avoid that we are using unique_lock using try function and providing all mutexes to it
    thread t1(&Account::transfer, &acc, ref(James), ref(Peter), 100);
    thread t2(&Account::transfer, &acc, ref(Peter), ref(James), 100);
    t1.join();
    t2.join();
    return 0;
}
