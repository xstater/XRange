#ifndef _XRANGE_TAKE_H_
#define _XRANGE_TAKE_H_

#include <iterator>
#include "Range.h"

namespace xrange{
    class TakeRange{
    public:
        TakeRange(size_t count)
            :m_count(count){}
        ~TakeRange() = default;

        template <class RangeType>
        friend RangeType operator>>(RangeType range,TakeRange takeRange){
            return RangeType(range.begin(),range.begin() + takeRange.m_count);
        }
    protected:
    private:
        size_t m_count;
    };

    TakeRange take(size_t count){
        return TakeRange(count);
    }
}

#endif //_XRANGE_TAKE_H_
