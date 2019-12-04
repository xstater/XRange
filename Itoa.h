#ifndef _XRANGE_ITOA_H_
#define _XRANGE_ITOA_H_

#include <limits>
#include "Range.h"

namespace xrange{
    template <class Integeral>
    class ItoaIterator{
    public:
        using _self = ItoaIterator<Integeral>;
    
        ItoaIterator(Integeral val)
            :m_val(val){}
        ~ItoaIterator() = default;
        
        _self &operator++()noexcept{
            ++m_val;
            return *this;
        }
        
        Integeral operator*()const noexcept{
            return m_val;
        }
        
        bool operator!=(const _self &rhs)const noexcept{
            return m_val != rhs.m_val;
        }
    protected:
    private:
        Integeral m_val;
    };
    
    template <class Integeral>
    auto iota(Integeral beg,Integeral end)
        -> Range<ItoaIterator<Integeral>>{
        return Range<ItoaIterator<Integeral>>(
            ItoaIterator<Integeral>(beg),
            ItoaIterator<Integeral>(end)
        );    
    }
    template <class Integeral>
    auto iota(Integeral beg)
        -> Range<ItoaIterator<Integeral>>{
        return Range<ItoaIterator<Integeral>>(
            ItoaIterator<Integeral>(beg),
            ItoaIterator<Integeral>(std::numeric_limits<Integeral>::max())
        );    
    }
}

#endif //_XRANGE_ITOA_H_
