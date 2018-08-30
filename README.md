# XRange

一个表达区间概念的类，可用于基本数值类型和具有随机访问迭代器的序列类型，区间取值为[begin,end]而不是stl中常用的[begin,end)

### 说明
```
//简单的Range类
#include <iostream>
#include "Range.hpp"

int main(int argc,char *argv[]){
	//3 5 7
	for(auto i:Range<int>(3,8,2))
		std::cout<<i<<' ';
	std::cout<<std::endl;
	//c b a
	for(auto i:Range<signed char>('c','a',-1))
		std::cout<<i<<' ';
	std::cout<<std::endl;
	//g e c a
    std::vector<char> vc = {'a','b','c','d','e','f','g'};
    for(auto i:Range<decltype(vc.begin())>(vc.end() - 1,vc.begin(),-2))
        std::cout<<i<<' ';
    std::cout<<std::endl;
	return 0;
}
```
