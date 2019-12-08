#ifndef _XRANGE_MAP_H_
#define _XRANGE_MAP_H_

#include <functional>
#include "Range.h"
#include "return_type.h"

namespace xrange{
    template <class ReturnType,class Iterator>
    class MapIterator{
    public:
        using value_type = ReturnType;
        using reference = ReturnType &;
        using const_reference = const ReturnType &;
        using pointer = ReturnType *;
        using const_pointer = const ReturnType *;
        using ArgType = typename Iterator::value_type;
        using difference_type = typename Iterator::difference_type;
        
        MapIterator(std::function<ReturnType(ArgType)> f,Iterator itr)
            :m_itr(itr),m_func(f){}
        ~MapIterator() = default;
        
        ReturnType operator*()const noexcept{
            return m_func(*m_itr);
        }
        
        MapIterator &operator++()noexcept{
            ++m_itr;
            return *this;
        }
        const MapIterator operator++(int)noexcept{
            auto tmp = *this;
            ++m_itr;
            return tmp;
        }

        MapIterator &operator--()noexcept{
            --m_itr;
            return *this;
        }
        const MapIterator operator--(int)noexcept{
            auto tmp = *this;
            --m_itr;
            return tmp;
        }

        MapIterator operator+(difference_type value)const noexcept{
            return MapIterator(m_func,m_itr + value);
        }
        MapIterator &operator+=(difference_type value)noexcept{
            m_itr += value;
            return *this;
        }
        MapIterator operator-(difference_type value)const noexcept{
            return MapIterator(m_func,m_itr - value);
        }
        MapIterator &operator-=(difference_type value)noexcept{
            m_itr -= value;
            return *this;
        }

        bool operator==(const MapIterator &rhs)const noexcept{
            return m_itr == rhs.m_itr;
        }
        bool operator!=(const MapIterator &rhs)const noexcept{
            return m_itr != rhs.m_itr;
        }
        bool operator<(const MapIterator &rhs)const noexcept{
            return m_itr < rhs.m_itr;
        }
        bool operator>(const MapIterator &rhs)const noexcept{
            return m_itr > rhs.m_itr;
        }
        bool operator<=(const MapIterator &rhs)const noexcept{
            return m_itr <= rhs.m_itr;
        }
        bool operator>=(const MapIterator &rhs)const noexcept{
            return m_itr >= rhs.m_itr;
        }
        
    protected:
    private:
        Iterator m_itr;
        std::function<ReturnType(ArgType)> m_func;
    };
    
    template <class Func>
    class MapRange{
    public:
        using raw_func = std::decay_t<Func>;

        MapRange(Func &&f)
            :m_func(std::forward<Func>(f)){}
        
        template <class RangeType>
        friend auto operator>>(RangeType range,MapRange mapRange)
            -> Range<MapIterator<return_type_t<raw_func>,typename RangeType::iterator>>{
            return Range<MapIterator<return_type_t<raw_func>,typename RangeType::iterator>>(
                MapIterator<return_type_t<raw_func>,typename RangeType::iterator>(mapRange.m_func,range.begin()),
                MapIterator<return_type_t<raw_func>,typename RangeType::iterator>(mapRange.m_func,range.end())
            );
        }
        
    protected:
    private:
        Func m_func;
    };
    
    template <class Func>
    auto map(Func &&f)
        -> MapRange<Func>{
        return MapRange<Func>(std::forward<Func>(f));
    }
}

#endif //_XRANGE_MAP_H_
