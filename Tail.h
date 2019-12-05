#ifndef _XRANGE_TAIL_H_
#define _XRANGE_TAIL_H_

#include "Range.h"

namespace xrange{
    class TailRange{
    public:
        TailRange() = default;
        ~TailRange() = default;

        template <class RangeType>
        friend RangeType operator>>(RangeType range,TailRange tailRange){
            return RangeType(range.begin() + 1,range.end());
        }
    protected:
    private:
    };

    TailRange tail(){
        return TailRange();
    }
}

#endif //_XRANGE_TAIL_H_