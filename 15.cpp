#include <iostream>
#include<thread>
#include<vector>
#include<numeric>
#include<algorithm>

#define BLOCK_SIZE 1000
using namespace std;

template<typename ipIterator, typename T>
void myAccumulate(ipIterator start, ipIterator end, T& result){
    result=accumulate(start, end, result);
}

template<typename ipIterator, typename T>
T parallel_accumulate(ipIterator start, ipIterator end, T initVal){
    int total_size=distance(start, end);
    
    int threads_based_on_elements=total_size/(int)BLOCK_SIZE;
    
    if(threads_based_on_elements==0){
        ++threads_based_on_elements;
    }
    
    int thread_supported_on_hardware=thread::hardware_concurrency();
    
    int num_of_threads=min(thread_supported_on_hardware, threads_based_on_elements);
    
    int chunk_size=total_size/num_of_threads;
    
    vector<thread> threads(num_of_threads-1);
    vector<T> results(num_of_threads+1);
    auto begin=start, last=start+chunk_size;
    for(int i=0;i<num_of_threads-1;i++){
        thread t(myAccumulate<ipIterator, T>, begin, last, ref(results[i]));
        begin=last;
        //last=last+chunk_size;
        advance(last, chunk_size);
        threads[i]=move(t);
    }
    myAccumulate(begin, end, results[num_of_threads]);
    /*for(auto &t:threads){
        t.join();
    }*/
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));
    T sum=initVal;
    for(int i=0;i<=num_of_threads;i++){
        sum+=results[i];
    }
    return sum;
}

int main(){
    vector<int> v(101750);
    for(auto &i:v){
        i=1;
    }
    int sum=parallel_accumulate(v.begin(), v.end(), 0);
    cout<<sum<<endl;
    return 0;
}
