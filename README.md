# XRange

代表一个区间[begin,end)

### Examples
```
#include <iostream>
#include <vector>
#include "XRange.h"
using namespace std;

bool isPrime(int x){
    if(1 <= x && x <= 3)return true;
    for(int i : xrange::iota(2,x-1)){
        if(x % i == 0)
            return false;
    }
    return true;
}

int main(){
    for(auto i : xrange::iota(3) >> xrange::map([](int x)->int{return x + 1;}) >> xrange::take(3) >> xrange::head()){
        cout << i << ' ';
    }
    cout << endl;
    for(auto i : xrange::iota(1)
              >> xrange::filter([](int x) -> bool{ return x % 3 == 0;})
              >> xrange::take(10)){
        cout << i << ' ';
    }
    cout << endl;
    auto primes = xrange::iota(1) >> xrange::filter(isPrime);
    for(auto i : primes >> xrange::take(100)){
        cout << i << ' ';
    }
    return 0;
}
```
