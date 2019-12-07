#ifndef _XRANGE_SPLIT_BY_H_
#define _XRANGE_SPLIT_BY_H_

#include "Range.h"

namespace xrange{
    template <class Iterator>
    class SplitByIterator{
    public:
        using value_type = Range<Iterator>;
        using Spliter = typename Iterator::value_type;
    
        SplitByIterator(Spliter spliter,Iterator itr,Iterator end)
            :m_spliter(spliter),m_itr(itr),m_next(itr),m_end(end){
            //find the spliter
            while(m_next != m_end && *m_next != m_spliter){
                ++m_next;
            }
        }
        ~SplitByIterator() = default;
        
        value_type operator*()const noexcept{
            return value_type(m_itr,m_next);
        }
        
        SplitByIterator &operator++()noexcept{
            if(m_next == m_end){
                m_itr = m_end;
                return *this;
            }
            ++m_next;
            m_itr = m_next;
            while(m_next != m_end && *m_next != m_spliter){
                ++m_next;
            }
            return *this;
        }
        const SplitByIterator operator++(int)noexcept{
            auto itr = *this;
            ++(*this);
            return itr;
        }
        
        bool operator==(const SplitByIterator &rhs)const noexcept{
            return m_itr == rhs.m_itr;
        }
        bool operator!=(const SplitByIterator &rhs)const noexcept{
            return m_itr != rhs.m_itr;
        }
        bool operator<(const SplitByIterator &rhs)const noexcept{
            return m_itr < rhs.m_itr;
        }
        bool operator>(const SplitByIterator &rhs)const noexcept{
            return m_itr > rhs.m_itr;
        }
        bool operator<=(const SplitByIterator &rhs)const noexcept{
            return m_itr <= rhs.m_itr;
        }
        bool operator>=(const SplitByIterator &rhs)const noexcept{
            return m_itr >= rhs.m_itr;
        }
    protected:
    private:
        Iterator m_itr,m_next,m_end;
        Spliter m_spliter;
    };
    
    template <class Spliter>
    class SplitByRange{
    public:
        SplitByRange(Spliter spliter)
                :m_spliter(spliter){}

        template <class RangeType>
        friend auto operator>>(RangeType range,SplitByRange splitRange)
        -> Range<SplitByIterator<typename RangeType::iterator>>{
            return Range<SplitByIterator<typename RangeType::iterator>>(
                    SplitByIterator<typename RangeType::iterator>(splitRange.m_spliter,range.begin(),range.end()),
                    SplitByIterator<typename RangeType::iterator>(splitRange.m_spliter,range.end(),range.end())
            );
        }

    protected:
    private:
        Spliter m_spliter;
    };

    template <class Spliter>
    auto splitBy(Spliter spliter)
    -> SplitByRange<Spliter>{
        return SplitByRange<Spliter>(spliter);
    }
    
}

#endif //_XRANGE_SPLIT_BY_H_
