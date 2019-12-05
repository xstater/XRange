#ifndef _XRANGE_IOTA_H_
#define _XRANGE_IOTA_H_

#include <limits>
#include "Range.h"

namespace xrange{
    template <class Integeral>
    class IotaIterator{
    public:
        using _self = IotaIterator<Integeral>;
    
        IotaIterator(Integeral val)
            :m_val(val){}
        ~IotaIterator() = default;
        
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
        -> Range<IotaIterator<Integeral>>{
        return Range<IotaIterator<Integeral>>(
            IotaIterator<Integeral>(beg),
            IotaIterator<Integeral>(end)
        );
    }
    template <class Integeral>
    auto iota(Integeral beg)
        -> Range<IotaIterator<Integeral>>{
        return Range<IotaIterator<Integeral>>(
            IotaIterator<Integeral>(beg),
            IotaIterator<Integeral>(std::numeric_limits<Integeral>::max())
        );    
    }
}

#endif //_XRANGE_IOTA_H_
