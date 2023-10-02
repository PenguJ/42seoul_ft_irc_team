#include <iostream>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

typedef struct test
{
    string str;
    int a;
}   s_test;

void initPairToVec(int a, int b, vector<pair<int, int>>* vec)
{
    pair<int, int> p;

    p.first = a;
    p.second = b;
    vec->push_back(p);
}

int main()
{
// ㅎ해결 vector ㅇ장애
    // vector<int> vec;

    // vec.reserve(50);

    // for (int i = 0; i < 10; ++i)
    //     vec.push_back(i);
    
    // for (int i = 0; i < 10; ++i)
    //     cout<<vec[i]<<" ";
    // cout<<endl;

    // vector<int>::iterator iter = vec.begin();

    // while (1)
    // {
    //     if (iter == vec.end())
    //         break ;
    //     else if (*iter == 4)
    //     {
    //         vec.erase(iter);
    //         continue ;
    //     }
    //     else
    //     {
    //         cout<<*iter<<" ";
    //         ++iter;
    //     }
    // }
    // cout<<endl;
    // cout<<endl;
    // return (0);

// pair test
    // vector<pair<int, int>> vec;

    // initPairToVec(1, 2, &vec);

    // cout<<vec[0].first<<endl;
    // cout<<vec[0].second<<endl;

// reverse iter test
    // vector<int> vec;

    // for (int i = 0; i < 10; ++i)
    // {
    //     vec.push_back(i);
    // }
    // for (int i = 0; i < 10; ++i)
    //     cout<<vec[i]<<" ";
    // cout<<endl;

    // vector<int>::reverse_iterator riter = vec.rbegin();
    // for(; riter != vec.rend(); ++riter)
    // {
    //     cout<<*riter<<" ";
    // }
    // cout<<endl;

    map<string, int> m;

    m["A"] = 10;
    m["B"] = 20;

    cout<<m["A"]<<endl;


}