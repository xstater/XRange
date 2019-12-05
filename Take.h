#ifndef _XRANGE_TAKE_H_
#define _XRANGE_TAKE_H_

#include <iterator>
#include "Range.h"

namespace xrange{
    template <class Size = size_t>
    class TakeRange{
    public:
        TakeRange(Size count)
            :m_count(count){}
        ~TakeRange() = default;

        template <class RangeType>
        friend RangeType operator>>(RangeType range,TakeRange takeRange){
            return RangeType(range.begin(),range.begin() + takeRange.m_count);
        }
    protected:
    private:
        Size m_count;
    };

    template <class Size = size_t>
    TakeRange<Size> take(Size count){
        return TakeRange<Size>(count);
    }
}

#endif //_XRANGE_TAKE_H_
