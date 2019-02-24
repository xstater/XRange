#ifndef _X_RANGE_H_
#define _X_RANGE_H_

#include <iterator>

namespace xrange{

    template <class Type>
    class NumberRange{
    public:
        using value_type = Type;
        using difference_type = Type;

        class iterator{
        public:
            iterator(Type val,Type step)
                    :m_val(val),
                     m_step(step){ }

            iterator(const iterator &) = default;

            iterator(iterator &&) noexcept = default;

            ~iterator() = default;

            Type operator*() const noexcept{
                return m_val;
            }

            iterator &operator++() noexcept{
                m_val += m_step;
                return *this;
            }

            iterator operator++(int) noexcept{
                iterator itr = *this;
                m_val += m_step;
                return itr;
            }

            iterator &operator--() noexcept{
                m_val -= m_step;
                return *this;
            }

            iterator operator--(int) noexcept{
                iterator itr = *this;
                m_val -= m_step;
                return itr;
            }

            bool operator!=(const iterator &itr) const noexcept{
                return m_val != itr.m_val;
            }

            bool operator==(const iterator &itr) const noexcept{
                return m_val == itr.m_val;
            }

            bool operator<=(const iterator &itr) const noexcept{
                return m_val <= itr.m_val;
            }

            bool operator>=(const iterator &itr) const noexcept{
                return m_val >= itr.m_val;
            }

            bool operator<(const iterator &itr) const noexcept{
                return m_val < itr.m_val;
            }

            bool operator>(const iterator &itr) const noexcept{
                return m_val > itr.m_val;
            }

        protected:
        private:
            Type m_val,m_step;
        };

        NumberRange(Type begin,Type end,Type step = 0)
                :m_begin(begin),
                 m_end(end),
                 m_step(step){
            if(m_step == 0){
                if(end >= begin){
                    m_step = 1;
                }else{
                    m_step = -1;
                }
            }
        }

        NumberRange(const NumberRange &) = default;

        NumberRange(NumberRange &&) = default;

        ~NumberRange() = default;

        NumberRange &operator=(const NumberRange &) = default;

        NumberRange &operator=(NumberRange &&) = default;

        iterator begin() noexcept{
            return iterator(m_begin,m_step);
        }

        iterator end() noexcept{
            return iterator(m_end,m_step);
        }

    protected:
    private:
        Type m_begin,m_end,m_step;
    };

    template <class Iterator>
    class ContainerRange{
    public:
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using reference = typename std::iterator_traits<Iterator>::reference;
        using pointer = typename std::iterator_traits<Iterator>::pointer;
        using iterator = Iterator;

        ContainerRange(iterator begin,iterator end)
                :m_begin(begin),
                 m_end(end){ }

        ContainerRange(const ContainerRange &) = default;

        ContainerRange(ContainerRange &&) noexcept = default;

        ~ContainerRange() = default;

        ContainerRange &operator=(const ContainerRange &) = default;

        ContainerRange &operator=(ContainerRange &&) = default;

        difference_type size() const noexcept{
            return m_end - m_begin;
        }

        bool empty() const noexcept{
            return size() == 0;
        }

        reference front() noexcept{
            return *m_begin;
        }

        reference back() noexcept{
            return *std::prev(m_end);
        }

        pointer data() noexcept{
            return &(*m_begin);
        }

        void expand_left(difference_type size = 1){
            m_begin = std::prev(m_begin,size);
        }

        void remove_left(difference_type size = 1){
            m_begin = std::next(m_begin,size);
        }

        void expand_right(difference_type size = 1){
            m_end = std::next(m_end,size);
        }

        void remove_right(difference_type size = 1){
            m_end = std::prev(m_end,size);
        }

        reference operator[](difference_type index) noexcept{
            return m_begin[index];
        }

        iterator begin() noexcept{
            return m_begin;
        }

        iterator end() noexcept{
            return m_end;
        }

    protected:
    private:
        iterator m_begin;
        iterator m_end;
    };

    template <class Iterator>
    class Range : public ContainerRange<Iterator>{
    public:
        using value_type = typename std::iterator_traits<Iterator>::value_type;
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using iterator = Iterator;

        Range(iterator begin,iterator end)
                :ContainerRange<Iterator>(begin,end){ }

        ~Range() = default;

    };

#define EXPAND(type) \
template <> \
class Range<type> : public NumberRange<type>{ \
public: \
    Range(type begin,type end,type step = 0) \
        :NumberRange(begin,end,step){} \
    ~Range() = default; \
}; \


    EXPAND(char)

    EXPAND(signed char)

    EXPAND(unsigned char)

    EXPAND(signed short int)

    EXPAND(unsigned short int)

    EXPAND(signed int)

    EXPAND(unsigned int)

    EXPAND(signed long int)

    EXPAND(unsigned long int)

    EXPAND(signed long long int)

    EXPAND(unsigned long long int)

#undef EXPAND

    template <class Container>
    auto make_range(Container &&container)
    -> ContainerRange<decltype(container.begin())>{
        return ContainerRange<decltype(container.begin())>(container.begin(),container.end());
    }

    template <class Container>
    auto make_crange(Container &&container)
    -> ContainerRange<decltype(container.cbegin())>{
        return ContainerRange<decltype(container.cbegin())>(container.cbegin(),container.cend());
    }

    template <class Container>
    auto make_rrange(Container &&container)
    -> ContainerRange<decltype(container.rbegin())>{
        return ContainerRange<decltype(container.rbegin())>(container.rbegin(),container.rend());
    }

    template <class Container>
    auto make_crrange(Container &&container)
    -> ContainerRange<decltype(container.crbegin())>{
        return ContainerRange<decltype(container.crbegin())>(container.crbegin(),container.crend());
    }

}

#endif
