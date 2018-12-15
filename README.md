# XRange

代表一个区间[begin,end)

### Examples
```
#include <iostream>
#include <vector>
#include "Range.hpp"
using namespace std;
int main(){
    //3 5 7
    for(auto i:Range<int>(3,9,2))
        std::cout<<i<<' ';
    std::cout<<std::endl;
    //c b a
    for(auto i:Range<signed char>('c','a' - 1))
        std::cout<<i<<' ';
    std::cout<<std::endl;
    //f e d c a
    std::vector<char> vc = {'a','b','c','d','e','f','g'};
    for(auto i:Range<decltype(vc.rbegin())>(vc.rbegin() + 1,vc.rend() - 1))
        std::cout<<i<<' ';
    std::cout<<std::endl;
    //e d
    auto range = Range<decltype(vc.rbegin())>(vc.rbegin() + 1,vc.rend() - 1);
    for(auto i:Range<int>(1,3))//1 2
        std::cout<<range[i]<<' ';//operator[]
    std::cout<<std::endl;
}
```
