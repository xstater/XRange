#ifndef _XRANGE_
#define _XRANGE_

template<class Type>
class Range{
	public:
		class iterator{
			public:
				iterator(Type begin,Type step)
					:m_now(begin),m_step(step){}
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
					return m_now != itr.m_now;
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
			//some exceptions here
		}
		Range(Type val_end)
			:m_val_start(0),
			 m_val_end(val_end),
			 m_val_step(val_end>0?1:-1){}
		Range(const Range &) = default;
		//Range(Range&&) = default;
		~Range() = default;
		
		iterator begin()noexcept{
			return iterator(m_val_start,m_val_step);
		}
		iterator end()noexcept{
			return iterator(m_val_end + m_val_step,m_val_step);
		}
	protected:
	private:
		Type m_val_start,m_val_end,m_val_step;
};

#endif
