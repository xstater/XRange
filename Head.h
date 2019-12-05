#ifndef _XRANGE_HEAD_H_
#define _XRANGE_HEAD_H_

#include "Range.h"

namespace xrange{
    class HeadRange{
    public:
        HeadRange() = default;
        ~HeadRange() = default;

        template <class RangeType>
        friend RangeType operator>>(RangeType range,HeadRange takeRange){
            return RangeType(range.begin(),range.begin() + 1);
        }
    protected:
    private:
    };

    HeadRange head(){
        return HeadRange();
    }
}

#endif //_XRANGE_HEAD_H_