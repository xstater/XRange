#ifndef _XRANGE_ITERATE_H_
#define _XRANGE_ITERATE_H_

#include <functional>
#include "Range.h"

namespace xrange{
    template <class Function,class Number>
    class IterateIterator{
    public:
        using value_type = Number;
        using reference = Number &;
        using const_reference = const Number &;
        using pointer = Number *;
        using const_pointer = const Number *;
        using difference_type = size_t;

        IterateIterator(Function &&f,Number init,size_t count)
                :m_count(count),m_itr(init),m_func(std::forward<Function>(f)){}
        ~IterateIterator() = default;

        value_type operator*()const noexcept{
            return m_itr;
        }

        IterateIterator &operator++()noexcept{
            ++m_count;
            m_itr = m_func(m_itr);
            return *this;
        }
        const IterateIterator operator++(int)noexcept{
            auto tmp = *this;
            ++m_count;
            ++m_itr;
            return tmp;
        }

        IterateIterator operator+(difference_type value)const noexcept{
            auto itr = *this;
            for(;value != 0;--value){
                ++itr;
            }
            return itr;
        }
        IterateIterator &operator+=(difference_type value)noexcept{
            for(;value != 0;--value){
                ++m_count;
                m_itr = m_func(m_itr);
            }
            return *this;
        }

        bool operator==(const IterateIterator &rhs)const noexcept{
            return m_count == rhs.m_count;
        }
        bool operator!=(const IterateIterator &rhs)const noexcept{
            return m_count != rhs.m_count;
        }
    protected:
    private:
        size_t m_count;
        Number m_itr;
        Function m_func;
    };

    template <class Number,class Func>
    auto iterate(Func &&f,Number number = 0.0)
    -> Range<IterateIterator<std::decay_t<Func>,Number>>{
        using raw_func = std::decay_t<Func>;
        return Range<IterateIterator<raw_func,Number>>(
                IterateIterator<raw_func,Number>(
                        std::forward<raw_func>(f),
                        number,
                        std::numeric_limits<size_t>::min()),
                IterateIterator<raw_func,Number>(
                        std::forward<raw_func>(f),
                        number,
                        std::numeric_limits<size_t>::max())
            );
    }
}

#endif //_XRANGE_ITERATE_H_