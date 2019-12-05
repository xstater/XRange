#ifndef _XRANGE_FILTER_H_
#define _XRANGE_FILTER_H_

#include "Range.h"

namespace xrange{
    template <class Iterator>
    class FilterIterator{
    public:
        using value_type = typename Iterator::value_type;
        using reference = typename Iterator::reference;
        using const_reference = typename Iterator::const_reference;
        using pointer = typename Iterator::pointer;
        using const_pointer = typename Iterator::const_pointer;
        using ArgType = typename Iterator::value_type;
        using difference_type = typename Iterator::difference_type;

        FilterIterator(std::function<bool(ArgType)> f,Iterator itr,Iterator end)
                :m_itr(itr),m_end(end),m_func(f){
            while(m_itr != m_end && !m_func(*m_itr)){
                ++m_itr;
            }
        }
        ~FilterIterator() = default;

        FilterIterator &operator=(const FilterIterator &) = default;

        value_type operator*()const noexcept{
            return *m_itr;
        }

        FilterIterator &operator++()noexcept{
            ++m_itr;
            while(m_itr != m_end && !m_func(*m_itr)){
                ++m_itr;
            }
            return *this;
        }
        const FilterIterator operator++(int)noexcept{
            auto tmp = *this;
            ++m_itr;
            while(m_itr != m_end && !m_func(*m_itr)){
                ++m_itr;
            }
            return tmp;
        }


        FilterIterator operator+(difference_type value)const noexcept{
            auto itr = *this;
            while(value-- != 0){
                ++itr;
            }
            return itr;
        }
        FilterIterator &operator+=(difference_type value)noexcept{
            while(value-- != 0){
                ++(*this);
            }
            return *this;
        }

        bool operator==(const FilterIterator &rhs)const noexcept{
            return m_itr == rhs.m_itr;
        }
        bool operator!=(const FilterIterator &rhs)const noexcept{
            return m_itr != rhs.m_itr;
        }
        bool operator<(const FilterIterator &rhs)const noexcept{
            return m_itr < rhs.m_itr;
        }
        bool operator>(const FilterIterator &rhs)const noexcept{
            return m_itr > rhs.m_itr;
        }
        bool operator<=(const FilterIterator &rhs)const noexcept{
            return m_itr <= rhs.m_itr;
        }
        bool operator>=(const FilterIterator &rhs)const noexcept{
            return m_itr >= rhs.m_itr;
        }

    protected:
    private:
        Iterator m_itr,m_end;
        std::function<bool(ArgType)> m_func;
    };

    template <class Func>
    class FilterRange{
    public:
        FilterRange(Func &&f)
                :m_func(std::forward<Func>(f)){}

        template <class RangeType>
        friend auto operator>>(RangeType range,FilterRange filterRange)
        -> Range<FilterIterator<typename RangeType::iterator>>{
            return Range<FilterIterator<typename RangeType::iterator>>(
                    FilterIterator<typename RangeType::iterator>(filterRange.m_func,range.begin(),range.end()),
                    FilterIterator<typename RangeType::iterator>(filterRange.m_func,range.end(),range.end())
            );
        }

    protected:
    private:
        Func m_func;
    };

    template <class Func>
    auto filter(Func &&f)
    -> FilterRange<Func>{
        return FilterRange<Func>(std::forward<Func>(f));
    }
}

#endif //_XRANGE_FILTER_H_