#ifndef _XRANGE_RANGE_H_
#define _XRANGE_RANGE_H_

namespace xrange{
    template <class Iterator>
    class Range{
    public:
        Range(Iterator beg,Iterator end)
            :m_beg(beg),m_end(end){}
        ~Range() = default;
        
        bool empty()const noexcept{
            return m_beg == m_end;
        }
        
        Iterator begin()const noexcept{
            return m_beg;
        }
        Iterator end()const noexcept{
            return m_end;
        }
    protected:
    private:
        Iterator m_beg,m_end;
    };
}

#endif //_XRANGE_RANGE_H_
