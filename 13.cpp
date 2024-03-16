#include <iostream>
#include<thread>
#include<chrono>
#include<queue>

#define CLEAN 1
#define ENG_WORK 2
#define EXIT 100

using namespace std;

class Command;

queue<Command> cleaningQueue;
queue<Command> engWorkQueue;
    
class Command{
    int cmd;
    
    public:
    friend istream& operator>>(istream& is, Command& rhs){
        int temp_cmd;
        cin>>temp_cmd;
        rhs.cmd=temp_cmd;
        return cin;
    }
    
    bool operator!=(int exit_cmd){
        return cmd!=exit_cmd;
    }
    bool operator==(int cmpCmd){
        return cmd==cmpCmd;
    }
};

void doWork(queue<Command>& que, void (*workPtr)()){
    while(1){
        if(!que.empty()){
            if(que.front()==EXIT){
                return;
            }
            que.pop();
            workPtr();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
        else{
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
        
    }
}

void doClean(){
    cout<<"im cleaning"<<endl;
}

void doEngWork(){
    cout<<"im doing engine work"<<endl;
}

void cleanWork(){
    doWork(cleaningQueue, &doClean);
}

void engWork(){
    doWork(engWorkQueue, &doEngWork);
}

int main(){
    thread cleaning_thread(cleanWork);
    thread work_thread(engWork);
    Command inputCmd;
    do{
        cin>>inputCmd;
        if(inputCmd==CLEAN){
            cleaningQueue.push(inputCmd);
        }
        if(inputCmd==ENG_WORK){
            engWorkQueue.push(inputCmd);
        }
        if(inputCmd==EXIT){
            cleaningQueue.push(inputCmd);
            engWorkQueue.push(inputCmd);
        }
        this_thread::sleep_for(chrono::milliseconds(1000));
    }while(inputCmd!=EXIT);
    cleaning_thread.join();
    work_thread.join();
    return 0;
}
