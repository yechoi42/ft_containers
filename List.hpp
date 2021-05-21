/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 13:20:05 by yechoi            #+#    #+#             */
/*   Updated: 2021/05/20 12:39:51 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include "Utility.hpp"

namespace ft
{
    /* http://cs.brown.edu/people/jwicks/libstdc++/html_user/stl__list_8h-source.html */

    template <typename T>
    struct ListNode
    {
        ListNode *m_prev;
        ListNode *m_next;
        T m_data;

        ListNode(ListNode *prev, ListNode *next)
            : m_prev(prev), m_next(next) {}
    };

    template <typename T>
    class ListIterator
    {
        public:
            typedef ft::BidirectionalIteratorTag iterator_category;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef ptrdiff_t difference_type;

            typedef ListIterator<T> Self;
            typedef ListNode node_type;
            typedef ListNode* node_pointer;

        private:
            node_pointer m_node;

        public:
            ListIterator()
                : m_node() {}
            
            ListIterator(const Self& other)
                : m_node(other.m_node) {}
            
            ~ListIterator() {}

            reference
            operator*() const
            {
                return (m_node->m_data);
            }

            pointer
            operator->() const
            {
                return (&m_node->m_data);
            }

            Self&
            operator++()
            {
                m_node = m_node->m_next;
                return (*this);
            }

            Self
            operator++(int)
            {
                Self tmp = *this;
                m_node = m_node->next;
                return (tmp);   
            }

            Self&
            operator--()
            {
                m_node = m_node->m_prev;
                return (*this);
            }

            Self
            operator--(int)
            {
                Self tmp = *this;
                m_node = m_node->m_prev;
                return (tmp);
            }

            bool
            operator==(const Self& x) const
            {
                return (m_node == x.m_node);
            }
            
            bool
            operator!=(const Self& x) const 
            {
                return (m_node != x.m_node);
            }
    };

    template <typename T>
    bool
    operator==(const ListIterator<T>& x, const ListIterator<T>& y)
    {
        return (x.m_node == y.m_node);
    }

    template <typename T>
    bool
    operator!=(const ListIterator<T>& x, const ListIterator<T>& y)
    {
        return (x.m_node != y.m_node);
    }

    template < typename T, typename Alloc = std::allocator<T> >
    class List
    {
        public:
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef value_type& reference;
            typedef const value_type& const_reference;
            typedef value_type* pointer;
            typedef const value_type* const_pointer;
            typedef ListIterator<T> iterator;
            typedef const ListIterator<T> const_iterator;
            typedef ReverseIterator<iterator> reverse_iterator;
            typedef ReverseIterator<const_iterator> const_reverse_iterator;

            typedef List<T, Alloc> Self;

        private:
            ListNode *m_head;
            ListNode *m_tail;
            size_type m_len;

        public:
            /* member functions */
            List()
                : m_len(0)
            {
                m_head = new ListNode(NULL, NULL);
                m_tail = m_head;
            }
            
            List(size_type count, const T& value = T())
                : m_len(0)
            {
                m_head = new ListNode(NULL, NULL);
                m_tail = m_head;
                insert(m_head, count, value);
            }

            template<typename InputIt>
            List(InputIt first, Input last)
                : m_len(0)
            {
                m_head = new ListNode(NULL, NULL);
                m_tail = m_head;
                insert(begin(), first, last);
            }

            List(const List& other)
                : m_len(0)
            {
                m_head = new ListNode(NULL, NULL);
                m_tail = m_head;
                insert(begin(), other.begin(), other.end());
            }

            ~List()
            {
                erase(begin(), end());
                delete (m_tail);
            }

            List&
            operator=(const List& other)
            {
                clear();
                insert(begin(), other.begin(), other.end());
                return (*this);
            }

            void
            assign(size_type count, const T& value)
            {
                clear();
                insert(begin(), count, value);
            }

			template<typename InputIt>
			void assign(Inputit first, InputIt last)
            {
                clear();
                insert(begin(), first, last);
            }

            /* element access */
            reference
            front()
            {
                return (m_head->m_data);
            }

            const_reference
            front() const
            {
                return (m_head->m_data);
            }

            reference
            back()
            {
                return (m_tail->m_data);
            }

            const_reference
            back()
            {
                return (m_tail->m_data);
            }

            /* iterators */
			iterator
			begin()
            {
                return (iterator(m_head));
            }  

			const_iterator
			begin() const
            {
                return (const_iterator(m_head));
            }

			iterator
			end()
			{
                return (iterator(m_tail));
			}

			const_iterator
			end() const
			{
                return (const_iterator(m_tail));
			}

			reverse_iterator
			rbegin()
			{
                return (reverse_iterator(m_tail));
			}

			const_reverse_iterator
			rbegin() const
			{
                return (const_reverse_iterator(m_tail));
			}

			reverse_iterator
			rend()
			{
                return (reverse_iterator(m_head));
			}

			const_reverse_iterator
			rend() const
			{
                return (const_reverse_iterator(m_head));
			}

            /* capacity */
            bool
            empty() const
            {
                return (m_len == 0);
            }

            size_type
            size() const
            {
                return (m_len);
            }

            size_type
            max_size() const
            {
                return (std::numeric_limits<difference_type>::max());
            }

            /* modifiers */
            void
            clear()
            {
                erase(begin(), end());
            }

            iterator
            insert(iterator pos, const T& value)
            {
                Node *node = new Node(pos.m_node->m_prev, pos.m_node);
                node->m_data = value;
                if (node->m_prev)
                    node->m_prev->m_next = node;
                else
                    m_head = node;
                node->m_next->m_prev = node;
                m_len++;
                return (iterator(node));
            }

            void
            insert(itereator pos, size_type count, const T& value)
            {
                Node *left_node = pos.m_node->m_prev;
                Node *right_node = node.m_node->m_next;

                Node *new_left_node = left_node;
                for (size_t i = 0; i < count; i++)
                {
                    Node *tmp = new Node(new_left_node, NULL);
                    tmp->m_data = value;

                    if (new_left_node)
                        new_left_node->m_next = tmp;
                    else
                        m_head = tmp;
                    m_len++;
                    new_left_node = tmp;
                }
                right_node->m_prev = new_left_node;
                if (new_left_node)
                    new_left_node->m_next = right_node;
            }

            template<typedef InputIt>
			void 
			insert(iterator pos, InputIt first, InputIt last)
			{
				Node *left_node = pos.m_node->m_prev;
                Node *right_node = pos.m_node->m_next;

                Node *new_left_node = left_node;
                for (InputIt it = first; it != last; ++it)
                {
                    Node *tmp = new Node(new_left_node, NULL);
                    tmp->m_data = value;
                    if (new_left_node)
                        new_left_node->m_next = tmp;
                    else
                        m_head = tmp;
                    m_len++;
                    new_left_node = tmp;
                }
                right_node->m_prev = new_left_node;
                if (new_left_node)
                    new_left_node->m_next = right_node;
			}            
            
            iterator
            erase(iterator pos)
            {
                iterator last = pos;
                ++last;
                return (erase(pos, last));
            }

            iterator
            erase(iterator first, iterator last)
            {
                Node *left_node = first.m_node->m_prev;
                Node *right_node = last.m_node;

                iterator it = first;
                while (it != last)
                {
                    iterator tmp = it;
                    delete tmp.m_node;
                    m_len--;
                    it++;
                }
                if (left_node)
                    left_node->m_next = right_node;
                else
                    m_head = right_node;
                right_node->m_prev = left_node;
                return (iterator(right_node));
            }

			void
			push_back(const T& value)
            {
                insert(end(), value);
            }

			void
			pop_back()
			{
                iterator it = end();
                --it;
                erase(it);
			}            

			void
			push_front(const T& value)
			{
                insert(begin(), value);
			}

            void
            pop_front()
            {
                erase(begin());
            }

			void
			resize(size_type count, T value = T() )
            {
                if (count >= m_len)
                    insert(end(), count - m_len, value);
                else
                {
                    iterator it = begin();
                    for (size_t i = 0; i < count; i++)
                        ++it;
                    erase(it, end());
                }
            }
            
			void
			swap(Self &other)
			{
                std::swap(m_head, x.m_head);
                std::swap(m_tail, x.m_tail);
                std::swap(m_len, x.m_len);
			}

            /* operations */
            void
            merge(Self &other)
            {

            }

            template <typedef Compare>
            void
            merge(Self& other, Compare comp)
            {

            }

            void 
            splice(const_iterator pos, Self& other)
            {
                splice(pos, other, other.begin(), other.end());
            }

            void 
            splice(const_iterator pos, Self& other, const_iterator it)
            {
                iterator next = it;
                ++next;
                splice(pos, other, it, next);
            }

            void 
            splice(const_iterator pos, Self& other, const_iterator first, const_iterator last)
            {
                Node *right_node = pos.m_node;
                Node *left_node = right_node->m_prev;

                Node *other_right_node = last.m_node;
                Node *other_left_node = first.m_node->m_prev;

                size_type count = 0;
                while (first != last)
                {
                    ++first;
                    ++count;
                }
                first.m_node->m_prev = left_node;
                last.m_node->m_prev->m_next = right_node;
                other_left_node->m_next = m_last;
                other_right_node->m_prev = other_left_node;
                m_len += count;
                other.m_len -= count;
            }

            void
            remove(const T& value)
            {
                for (iterator it = begin(); it != end(); )
                {
                    if (it.m_node->m_value == value)
                        it = erase(it);
                    else
                        ++it;
                }
            }

            template<typedef UnaryPredicate>
            void
            remove_if(UnaryPredicate p)
            {
                for (iterator it = begin(); it != end(); )
                {
                    if (p(*it))
                        it = erase(it);
                    else
                        ++it;
                }
            }

            void
            reverse()
            {
                iterator it = begin();
                iterator begin = it;
                while (it != end())
                {
                    if (it.m_node->m_next == end())
                    {
                        iterator tmp = it;
                        tmp.m_node->m_next = tmp.m_node->m_prev;
                        tmp.m_node->m_prev = NULL;
                        m_head = tmp.m_node;
                    }
                    else
                    {
                        std::swap(it.m_node->m_prev, it.m_node->m_next);
                    }
                    ++it; 
                }
                m_tail->prev = begin.m_node;
                begin.m_node->next = m_tail; 
            }

            void
            unique()
            {
                if (begin() == end())
                    return ;
                iterator cur = this->begin();
                iterator next = prev;
                ++next;
                while (next != end())
                {
                    if (*cur == *next)
                        erase(next);
                    else
                    {
                        cur = next;
                        ++next;
                    }
                }
            }

            template <typedef BinaryPredicate>
            void
            unique(BinaryPredicate p)
            {
                if (begin() == end())
                    return ;
                iterator cur = this->begin();
                iterator next = prev;
                ++next;
                while (next != end())
                {
                    if (p(*cur, *next))
                        erase(next);
                    else
                    {
                        cur = next;
                        ++next;                        
                    }
                }
            }

            void
            sort()
            {

            }

            template <typedef Compare>
            void
            sort(Compare comp)
            {

            }
    };

	/* non-member functions */
	template< class T, class Alloc >
	bool operator==(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
        if (lhs.size() != rhs.size())
            return (false);
        return (equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool operator!=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
        return (!(lhs == rhs));
	}

	template< class T, class Alloc >
	bool operator<(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool operator<=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
        return (!(lhs > rhs));
	}

	template< class T, class Alloc >
	bool operator>(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template< class T, class Alloc >
	bool operator>=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
        return (!(lhs < rhs));
	}

	template< class T, class Alloc >
	void swap(List<T,Alloc>& lhs, List<T,Alloc>& rhs)
	{
		
	}
}

#endif