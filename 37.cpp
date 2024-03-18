#include <iostream>
#include<future>
#include<thread>
#include<chrono>
#include<memory>
using namespace std;

template<typename T>
class ThreadSafeQue{
    struct Node{
        T data;
        unique_ptr<Node> next;

        Node(T value):data{std::move(value)}{}
    };
    
    Node* tail;
    unique_ptr<Node> head;
    mutex headMutex;
    mutex tailMutex;
    condition_variable cv;
    
    public:
    ThreadSafeQue(): head{new Node}, tail(head.get()){}
    
    void push(T value){
        unique_ptr<Node> new_dummy=make_unique<Node>();
        {
            lock_guard<mutex> lk(tailMutex);
            tail->data=move(value);
            const Node* new_tail=new_dummy.get();
            tail->next=move(new_dummy);
            tail=new_dummy.get();
        }
        cv.notify_one();
    }
    
    bool empty(){
        lock_guard<mutex> lk(tailMutex);
        if(head.get()==tail){
            return make_shared<Node>();
        }
    }
    
    unique_ptr<Node> pop(){
        lock_guard<mutex> lk(headMutex);
        if(empty()){
            return make_unique<Node>();
        }
        unique_ptr<Node> old_head=move(head);
        head=move(old_head->next);
        return old_head;
    }
};

int main()
{
    //thread safe queue implementation with maximum concurrency level
    return 0;
}
