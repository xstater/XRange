#ifndef _XRANGE_IOTA_H_
#define _XRANGE_IOTA_H_

#include <limits>
#include "Range.h"

namespace xrange{
    template <class Integeral>
    class IotaIterator{
    public:
        using value_type = Integeral;
        using reference = Integeral &;
        using const_reference = const Integeral &;
        using pointer = Integeral *;
        using const_pointer = const Integeral *;
        using difference_type = Integeral;
    
    
        explicit IotaIterator(Integeral val)
            :m_val(val){}
        ~IotaIterator() = default;
        
        IotaIterator &operator++()noexcept{
            ++m_val;
            return *this;
        }
        const IotaIterator operator++(int)noexcept{
            auto tmp = *this;
            ++m_val;
            return tmp;
        }

        IotaIterator &operator--()noexcept{
            --m_val;
            return *this;
        }
        const IotaIterator operator--(int)noexcept{
            auto tmp = *this;
            --m_val;
            return tmp;
        }

        IotaIterator operator+(Integeral value)const noexcept{
            return IotaIterator(m_val + value);
        }
        IotaIterator &operator+=(Integeral value)noexcept{
            m_val += value;
            return *this;
        }
        IotaIterator operator-(Integeral value)const noexcept{
            return IotaIterator(m_val - value);
        }
        IotaIterator &operator-=(Integeral value)noexcept{
            m_val -= value;
            return *this;
        }

        Integeral operator*()const noexcept{
            return m_val;
        }

        bool operator==(const IotaIterator &rhs)const noexcept{
            return m_val == rhs.m_val;
        }
        bool operator!=(const IotaIterator &rhs)const noexcept{
            return m_val != rhs.m_val;
        }
        bool operator<(const IotaIterator &rhs)const noexcept{
            return m_val < rhs.m_val;
        }
        bool operator>(const IotaIterator &rhs)const noexcept{
            return m_val > rhs.m_val;
        }
        bool operator<=(const IotaIterator &rhs)const noexcept{
            return m_val <= rhs.m_val;
        }
        bool operator>=(const IotaIterator &rhs)const noexcept{
            return m_val >= rhs.m_val;
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
