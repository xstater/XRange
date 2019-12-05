#ifndef _XRANGE_DROP_H_
#define _XRANGE_DROP_H_

#include "Range.h"

namespace xrange{
    class DropRange{
    public:
        DropRange(size_t count)
                :m_count(count){}
        ~DropRange() = default;

        template <class RangeType>
        friend RangeType operator>>(RangeType range,DropRange dropRange){
            return RangeType(range.begin() + dropRange.m_count,range.end());
        }
    protected:
    private:
        size_t m_count;
    };

    DropRange drop(size_t count){
        return DropRange(count);
    }
}

#endif //_XRANGE_DROP_H_