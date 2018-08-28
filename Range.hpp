#ifndef _XRANGE_
#define _XRANGE_

#include <exception>
#include <stdexcept>

#define XRANGE_NUM_EXPAND(Type) \
    template<> \
    class Range<Type>:public NumberRange<Type>{ \
        public: \
            Range(Type val_start,Type val_end,Type val_step = 1) \
                :NumberRange(val_start,val_end,val_step){} \
            ~Range() = default; \
    }; \
    
template<class Type>
class NumberRange{
	public:
		class iterator{
			public:
				iterator(Type now,Type step)
					:m_now(now),m_step(step){}
				iterator(const iterator&) = default;
				iterator(iterator&&) = default;
				~iterator() = default;
				
				Type operator*()const noexcept{
					return m_now;
				}
				
				iterator &operator++()noexcept{
					m_now += m_step;
					return *this;
				}
				iterator operator++(int)noexcept{
					iterator itr = *this;
					m_now += m_step;
					return itr;
				}
				iterator &operator--()noexcept{
					m_now -= m_step;
					return *this;
				}
				iterator operator--(int)noexcept{
					iterator itr = *this;
					m_now -= m_step;
					return itr;
				}
				
				bool operator!=(const iterator &itr)const noexcept{
					if(itr.m_step != 0)
						return m_now != itr.m_now;
					if(m_step > 0)
						return m_now <= *itr;
					else
						return m_now >= *itr;
				}
				bool operator==(const iterator &itr)const noexcept{
					return m_now == itr.m_now;
				}
                bool operator<=(const iterator &itr)const noexcept{
                    return m_now <= itr.m_now;
				}
                bool operator>=(const iterator &itr)const noexcept{
                    return m_now >= itr.m_now;
				}
                bool operator<(const iterator &itr)const noexcept{
                    return m_now < itr.m_now;
				}
                bool operator>(const iterator &itr)const noexcept{
                    return m_now > itr.m_now;
				}
			protected:
			private:
				Type m_now,m_step;
		};
	
		NumberRange(Type val_start,Type val_end,Type val_step)
			:m_val_start(val_start),
			 m_val_end(val_end),
			 m_val_step(val_step){
			if(val_step > 0 && val_start > val_end)
				throw std::logic_error("Range:Step error");
			if(val_step < 0 && val_start < val_end)
				throw std::logic_error("Range:Step error");
		}
		NumberRange(const NumberRange &) = default;
		NumberRange(NumberRange&&) = default;
		~NumberRange() = default;
		
		iterator begin()noexcept{
			return iterator(m_val_start,m_val_step);
		}
		iterator end()noexcept{
			return iterator(m_val_end,0);
		}
	protected:
	private:
		Type m_val_start,m_val_end,m_val_step;
};


template<class Iterator>
class SequenceIteratorRange{
    public:
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using value_type = typename std::iterator_traits<Iterator>::value_type;
    
        class iterator{
            public:
                iterator(Iterator itr,difference_type step)
                    :m_itr(itr),
                     m_step(step){}
                iterator(const iterator &) = default;
                iterator(iterator &&) = default;
                ~iterator() = default;
                
                value_type &operator*()noexcept{
                    return *m_itr;
                }
                iterator &operator++()noexcept{
                    m_itr += m_step;
                    return *this;
                }
                iterator operator++(int)noexcept{
                    iterator itr = *this;
                    m_itr += m_step;
                    return itr;
                }
                iterator &operator--()noexcept{
                    m_itr -= m_step;
                    return *this;
                }
                iterator operator--(int)noexcept{
                    iterator itr = *this;
                    m_itr -= m_step;
                    return itr;
				}
                
                bool operator!=(const iterator &itr)const noexcept{
                    if(itr.m_step != 0)
                        return m_itr != itr.m_itr;
                    if(m_step > 0)
                        return m_itr <= itr.m_itr;
                    else
						return m_itr >= itr.m_itr;
                }
                bool operator==(const iterator &itr)const noexcept{
                    return m_itr == itr.m_itr;
				}
                bool operator<=(const iterator &itr)const noexcept{
                    return m_itr <= itr.m_itr;
                }
                bool operator>=(const iterator &itr)const noexcept{
                    return m_itr >= itr.m_itr;
                }
                bool operator<(const iterator &itr)const noexcept{
                    return m_itr < itr.m_itr;
                }
                bool operator>(const iterator &itr)const noexcept{
                    return m_itr > itr.m_itr;
                }
            protected:
            private:
                Iterator m_itr;
                difference_type m_step;
        };
        
        SequenceIteratorRange(Iterator _begin,
                              Iterator _end,
                              difference_type _step)
            :m_begin(_begin),
             m_end(_step>0 ? _end+1 : _end-1),
             m_step(_step){}
        SequenceIteratorRange(const SequenceIteratorRange &) = default;
        SequenceIteratorRange(SequenceIteratorRange &&) = default;
        ~SequenceIteratorRange() = default;
        
        iterator begin()noexcept{
            return iterator(m_begin,m_step);
        }
        iterator end()noexcept{
            return iterator(m_end,0);
        }
        
    protected:
    private:
        Iterator m_begin;
        Iterator m_end;
        difference_type m_step;
};


template<class Type>
class Range:public SequenceIteratorRange<Type>{
    public:
        using difference_type = typename std::iterator_traits<Type>::difference_type;
    
        Range(Type _begin,Type _end,difference_type _step = 1)
            :SequenceIteratorRange<Type>(_begin,_end,_step){}
        ~Range() = default;
};

XRANGE_NUM_EXPAND(char)
XRANGE_NUM_EXPAND(signed char)
XRANGE_NUM_EXPAND(unsigned char)

XRANGE_NUM_EXPAND(signed short int)
XRANGE_NUM_EXPAND(unsigned short int)

XRANGE_NUM_EXPAND(signed int)
XRANGE_NUM_EXPAND(unsigned int)

XRANGE_NUM_EXPAND(signed long int)
XRANGE_NUM_EXPAND(unsigned long int)

XRANGE_NUM_EXPAND(signed long long int)
XRANGE_NUM_EXPAND(unsigned long long int)

XRANGE_NUM_EXPAND(float)
XRANGE_NUM_EXPAND(double)
XRANGE_NUM_EXPAND(long double)


#endif
