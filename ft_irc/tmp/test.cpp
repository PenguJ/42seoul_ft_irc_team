#include <iostream>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

typedef struct test
{
    std::string str;
    int a;
}   s_test;

void initPairToVec(int a, int b, std::vector<std::pair<int, int>>* vec)
{
    std::pair<int, int> p;

    p.first = a;
    p.second = b;
    vec->push_back(p);
}

int main()
{
// ㅎ해결 vector ㅇ장애
    // std::vector<int> vec;

    // vec.reserve(50);

    // for (int i = 0; i < 10; ++i)
    //     vec.push_back(i);
    
    // for (int i = 0; i < 10; ++i)
    //     std::cout<<vec[i]<<" ";
    // std::cout<<std::endl;

    // std::vector<int>::iterator iter = vec.begin();

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
    //         std::cout<<*iter<<" ";
    //         ++iter;
    //     }
    // }
    // std::cout<<std::endl;
    // std::cout<<std::endl;
    // return (0);

// pair test
    // std::vector<std::pair<int, int>> vec;

    // initPairToVec(1, 2, &vec);

    // std::cout<<vec[0].first<<std::endl;
    // std::cout<<vec[0].second<<std::endl;

// reverse iter test
    // std::vector<int> vec;

    // for (int i = 0; i < 10; ++i)
    // {
    //     vec.push_back(i);
    // }
    // for (int i = 0; i < 10; ++i)
    //     std::cout<<vec[i]<<" ";
    // std::cout<<std::endl;

    // std::vector<int>::reverse_iterator riter = vec.rbegin();
    // for(; riter != vec.rend(); ++riter)
    // {
    //     std::cout<<*riter<<" ";
    // }
    // std::cout<<std::endl;

    std::map<std::string, int> m;

    m["A"] = 10;
    m["B"] = 20;

    std::cout<<m["A"]<<std::endl;


}