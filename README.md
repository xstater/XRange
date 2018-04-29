#XRange

一个简单的Range类

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
}
```
