#ifndef _XRAMGE_COPY_H_
#define _XRAMGE_COPY_H_

#include <vector>
#include "Range.h"

namespace xrange{
    template <class Sequence,class RangeType>
    void copy(Sequence &&seq,RangeType &&range){
        for(auto itr1 = seq.begin(),itr2 = range.begin();
            itr1 != seq.end() && itr2 != range.end();
            ++itr1,++itr2){
            *itr1 = *itr2;
        }
    }
}

#endif //_XRAMGE_COPY_H_