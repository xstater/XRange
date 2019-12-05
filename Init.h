#ifndef _XRANGE_INIT_H_
#define _XRANGE_INIT_H_

#include "Init.h"

namespace xrange{
    class InitRange{
    public:
        InitRange() = default;
        ~InitRange() = default;

        template <class RangeType>
        friend RangeType operator>>(RangeType range,InitRange Init){
            return RangeType(range.begin(),range.end() - 1);
        }
    protected:
    private:
    };

    InitRange init(){
        return InitRange();
    }
}

#endif //_XRANGE_INIT_H_