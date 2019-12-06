#ifndef _XRANGE_REPEAT_H_
#define _XRANGE_REPEAT_H_

#include <limits>
#include "Range.h"

namespace xrange{
    template <class Number>
    class RepeatIterator{
    public:
        using value_type = Number;
        using reference = Number &;
        using const_reference = const Number &;
        using pointer = Number *;
        using const_pointer = const Number *;
        using difference_type = size_t;
    
    
        explicit RepeatIterator(Number val,difference_type itr)
            :m_val(val),m_itr(itr){}
        ~RepeatIterator() = default;
        
        RepeatIterator &operator++()noexcept{
            ++m_itr;
            return *this;
        }
        const RepeatIterator operator++(int)noexcept{
            auto tmp = *this;
            ++m_itr;
            return tmp;
        }

        RepeatIterator &operator--()noexcept{
            --m_itr;
            return *this;
        }
        const RepeatIterator operator--(int)noexcept{
            auto tmp = *this;
            --m_itr;
            return tmp;
        }

        RepeatIterator operator+(difference_type value)const noexcept{
            return RepeatIterator(m_val,m_itr + value);
        }
        RepeatIterator &operator+=(difference_type value)noexcept{
            m_itr += value;
            return *this;
        }
        RepeatIterator operator-(difference_type value)const noexcept{
            return RepeatIterator(m_val,m_itr - value);
        }
        RepeatIterator &operator-=(difference_type value)noexcept{
            m_itr -= value;
            return *this;
        }

        Number operator*()const noexcept{
            return m_val;
        }

        bool operator==(const RepeatIterator &rhs)const noexcept{
            return m_itr == rhs.m_itr;
        }
        bool operator!=(const RepeatIterator &rhs)const noexcept{
            return m_itr != rhs.m_itr;
        }
        bool operator<(const RepeatIterator &rhs)const noexcept{
            return m_itr < rhs.m_itr;
        }
        bool operator>(const RepeatIterator &rhs)const noexcept{
            return m_itr > rhs.m_itr;
        }
        bool operator<=(const RepeatIterator &rhs)const noexcept{
            return m_itr <= rhs.m_itr;
        }
        bool operator>=(const RepeatIterator &rhs)const noexcept{
            return m_itr >= rhs.m_itr;
        }
    protected:
    private:
        Number m_val;
        difference_type m_itr;
    };
    
    template <class Number>
    auto repeat(Number val)
        -> Range<RepeatIterator<Number>>{
        return Range<RepeatIterator<Number>>(
            RepeatIterator<Number>(val,std::numeric_limits<size_t>::min()),
            RepeatIterator<Number>(val,std::numeric_limits<size_t>::max())
        );    
    }
}

#endif //_XRANGE_REPEAT_H_
