#include <iostream>
#include<vector>
#include<numeric>
#include<algorithm>

using namespace std;

int main()
{
    vector<int> v={1, 2, 3, 4, 5, 6};
    int sum=accumulate(v.begin(), v.end(), 0);
    cout<<sum<<endl;

    vector<int> v1={1, 3, 4, 5};
    int prod=accumulate(v1.begin(), v1.end(), 1, multiplies<int>());
    cout<<prod<<endl;
    auto dash_acc_lambda=[](string str, int a){
        return str+"_"+to_string(a);
    };
    string dash_str="";
    dash_str=accumulate(v1.begin(), v1.end(), dash_str, dash_acc_lambda);
    cout<<dash_str<<endl;
    dash_str=accumulate(next(v1.begin()), v1.end(), to_string(v1[0]), dash_acc_lambda);
    cout<<dash_str;
    return 0;
}
