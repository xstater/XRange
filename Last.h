#ifndef _XRANGE_LAST_H_
#define _XRANGE_LAST_H_

#include "Range.h"

namespace xrange{
    class LastRange{
    public:
        LastRange() = default;
        ~LastRange() = default;

        template <class RangeType>
        friend RangeType operator>>(RangeType range,LastRange takeRange){
            return RangeType(range.end() - 1,range.end());
        }
    protected:
    private:
    };

    LastRange last(){
        return LastRange();
    }
}


#endif //_XRANGE_LAST_H_