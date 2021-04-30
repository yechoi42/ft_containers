/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:49:49 by yechoi            #+#    #+#             */
/*   Updated: 2021/04/30 20:08:53 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "Utility.hpp"

#define DEQUE_BUF_SIZE 512
#define DEQUE_BUF_SIZE_FOR(T) \
    (sizeof(T) < DEQUE_BUF_SIZE ? size_T(DEQUE_BUF_SIZE / sizeof(T)) : size_(1))

namespace ft
{
    template <typename T>
    class DequeIterator
    {
        public:
            typedef ft::RandomAccessIteratorTag iterator_category;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef DequeIterator Self;

            typedef T** map_pointer;

            pointer m_cur;
            pointer m_first;
            pointer m_last;
            map_pointer m_node;

        private:
            static size_t buffer_size()
            {
                return (DEQUE_BUF_SIZE_FOR(T));
            }
            void set_node(map_pointer node)
            {
                m_node = node;
                m_first = *node;
                m_last = *node + difference_type(buffer_size());
            }
            DequeIterator(pointer x, map_ponter y)
                : m_cur(x), m_first(*y), m_last(*y + buffer_size()), m_node(y) {} 

        public:
            DequeIterator()
                : m_cur(), m_first(), m_last(), m_node() {}

            DequeIterator(const Self &other)
                : m_cur(other.m_cur), m_first(other.m_first), m_last(other.m_last), m_node(other.m_node) {}

            ~DequeIterator() {}

            Self &operator=(const Self &other)
            {
                m_cur = other.m_cur;
                m_first = other.m_first;
                m_last = other.m_last;
                m_node = other.m_node;
                return (*this);
            }

            reference operator*() const
            {
                return (*m_cur);
            }

            pointer operator->() const
            {
                return (m_cur);
            }

            Self &operator++()
            {
                ++m_cur;
                if (m_cur == m_last)
                {
                    set_node(m_node + 1);
                    m_cur = m_first;
                }
                return (*this);
            }
    };
}


#endif