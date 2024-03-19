/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include<vector>
#include<execution>
#include<chrono>

using namespace std;

int main(){
    vector<int> v(1000000);
    for(int i=0;i<1000000;i++){
        v[i]=i;
    }
    
    auto start_time=chrono::high_resolution_clock::now();
    sort(v.begin(), v.end());
    auto end_time=chrono::high_resolution_clock::now();
    
    cout<<" "<<chrono::duration_cast<chrono::duration<double, milli>>(end_time - start_time).count()<<endl;

    //parallel stl, in same stl syntax, we can provide the execution policy as parameter as first argument
    start_time=chrono::high_resolution_clock::now();
    sort(execution::par, v.begin(), v.end());
    end_time=chrono::high_resolution_clock::now();
    
    cout<<" "<<chrono::duration_cast<chrono::duration<double, milli>>(end_time - start_time).count()<<endl;
    
    return 0;
}
