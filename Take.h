#ifndef _XRANGE_TAKE_H_
#define _XRANGE_TAKE_H_

#include <iterator>
#include "Range.h"

namespace xrange{
    template <class Iterator>
    class TakeIterator{
    public:
        using reference = typename std::iterator_traits<Iterator>::reference;
        
        TakeIterator(Iterator itr,size_type rem)
        ~TakeIterator() = default;
        
        TakeIterator &operator++()noexcept{
            ++m_itr;
            return *this;
        }
        
        reference operator*()noexcept{
            return *m_itr;
        }
    protected:
    private:
        Iterator m_itr;
    };
    
    
}

#endif //_XRANGE_TAKE_H_
