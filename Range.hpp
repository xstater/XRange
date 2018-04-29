#ifndef _XRANGE_
#define _XRANGE_

#include <exception>
#include <stdexcept>

template<class Type>
class Range{
	public:
		class iterator{
			public:
				iterator(Type now,Type step)
					:m_now(now),m_step(step){}
				iterator(const iterator&) = default;
				//iterator(iterator&&) = default
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
					if(itr.m_step != 0)//not end iterator
						return m_now != itr.m_now;
					if(m_step > 0)
						return m_now <= *itr;
					else
						return m_now >= *itr;
				}
				bool operator==(const iterator &itr)const noexcept{
					return m_now == itr.m_now;
				}
			protected:
			private:
				Type m_now,m_step;
		};
	
		Range(Type val_start,Type val_end,Type val_step = 1)
			:m_val_start(val_start),
			 m_val_end(val_end),
			 m_val_step(val_step){
			if(val_step > 0 && val_start > val_end)
				throw std::logic_error("Range:Step error");
			if(val_step < 0 && val_start < val_end)
				throw std::logic_error("Range:Step error");
		}
		Range(const Range &) = default;
		Range(Range&&) = default;
		~Range() = default;
		
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

#endif
