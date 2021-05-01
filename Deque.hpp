/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:49:49 by yechoi            #+#    #+#             */
/*   Updated: 2021/05/01 17:36:54 by yechoi           ###   ########.fr       */
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

			Self&
			operator=(const Self &other)
			{
				m_cur = other.m_cur;
				m_first = other.m_first;
				m_last = other.m_last;
				m_node = other.m_node;
				return (*this);
			}

			reference
			operator*() const
			{
				return (*m_cur);
			}

			pointer
			operator->() const
			{
				return (m_cur);
			}

			Self&
			operator++()
			{
				++m_cur;
				if (m_cur == m_last)
				{
					set_node(m_node + 1);
					m_cur = m_first;
				}
				return (*this);
			}

			Self
			operator++(int)
			{
				Self tmp = *this;
				++*this;
				return (tmp);
			}

			Self&
			operator--()
			{
				if (m_cur == m_first)
				{
					set_node(m_node - 10;
					m_cur = m_last;
				}
				--m_cur;
				return (*this);
			}

			Self
			operator--(int)
			{
				Self tmp = *this;
				--*this;
				return (tmp);
			}

			// 다시 확인
			Self&
			operator+=(difference_type n)
			{
				const difference_type offset = n + m_cur - m_first;
				if (offset >= 0 && offset < difference_type(buffer_size()))
					m_cur += n;
				else
				{
					const difference_type node_offset = offset > 0 ?
						offset / difference_type(buffer_size())
						: -difference_type((-offset - 1) / buffer_size()) - 1;
					set_node(m_node + node_offset);
					m_cur = m_first + (offset - node_offset * difference_type(buffer_size()));
				}
				return (*this);
			}

			Self
			operator+(difference_type n)
			{
				Self tmp = *this;
				return (tmp += n);
			}

			Self&
			operator-=(difference_type n)
			{
				return (*this += -n);
			}

			Self
			operator-(difference_type n)
			{
				Self tmp = *this;
				return (tmp -= n);
			}

			reference
			operator[](difference_type n)
			{
				return *(*this + n)
			}

			void swap(Self &other)
			{
				std::swap(m_cur, other.m_cur);
				std::swap(m_first, other.m_first);
				std::swap(m_last, other.m_last);
				std::swap(m_node, other.m_node);
			}
	};

	template <typename T>
	bool operator==(const DequeIterator<T> &x, const DequeIterator<T> &y)
	{
		return (x.m_cur == y.m_cur);
	}
	
	template <typename T>
	bool operator!=(const DequeIterator<T> &x, const DequeIterator<T> &y)
	{
		return !(x == y);
	}

	template <typename T>
	bool operator<(const DequeIterator<T> &x, const DequeIterator<T> &y)
	{
		return (x.m_node == y.m_node ? x.m_cur < y.m_cur : x.m_node < y.m_node);
	}

	template <typename T>
	bool operator>(const DequeIterator<T> &x, const DequeIterator<T> &y)
	{
		return (y < x);
	}

	template <typename T>
	bool operator<=(const DequeIterator<T> &x, const DequeIterator<T> &y)
	{
		return (!(y < x));
	}

	template <typename T>
	bool operator>=(const DequeIterator<T> &x, const DequeIterator<T> &y)
	{
		return (!(x < y));
	}

	/* 뭐에 쓰는 거람... https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00533_source.html
	template<typename _Tp, typename _Ref, typename _Ptr>
		inline typename _Deque_iterator<_Tp, _Ref, _Ptr>::difference_type
		operator-(const _Deque_iterator<_Tp, _Ref, _Ptr>& __x,
				const _Deque_iterator<_Tp, _Ref, _Ptr>& __y) _GLIBCXX_NOEXCEPT
		{
		return typename _Deque_iterator<_Tp, _Ref, _Ptr>::difference_type
			(_Deque_iterator<_Tp, _Ref, _Ptr>::_S_buffer_size())
			* (__x._M_node - __y._M_node - 1) + (__x._M_cur - __x._M_first)
			+ (__y._M_last - __y._M_cur);
		}
	
	template<typename _Tp, typename _RefL, typename _PtrL,
				typename _RefR, typename _PtrR>
		inline typename _Deque_iterator<_Tp, _RefL, _PtrL>::difference_type
		operator-(const _Deque_iterator<_Tp, _RefL, _PtrL>& __x,
				const _Deque_iterator<_Tp, _RefR, _PtrR>& __y) _GLIBCXX_NOEXCEPT
		{
		return typename _Deque_iterator<_Tp, _RefL, _PtrL>::difference_type
			(_Deque_iterator<_Tp, _RefL, _PtrL>::_S_buffer_size())
			* (__x._M_node - __y._M_node - 1) + (__x._M_cur - __x._M_first)
			+ (__y._M_last - __y._M_cur);
		}
	
	template<typename _Tp, typename _Ref, typename _Ptr>
		inline _Deque_iterator<_Tp, _Ref, _Ptr>
		operator+(ptrdiff_t __n, const _Deque_iterator<_Tp, _Ref, _Ptr>& __x)
		_GLIBCXX_NOEXCEPT
		{ return __x + __n; }
	*/

	template <typename T>
	void swap(const DequeIterator<T> &x, const DequeIterator<T> &y)
	{
		x.swap(y);
	}

	template <typename T, typename Alloc = std::allocator<T> >
	class Deque
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef value_type* pointer;
			typedef const value_type* const_pointer;
			typedef DequeIterator<T> iterator;
			typedef DequeIterator<T> const_iterator;
			typedef ReverseIterator<iterator> rever

			

	};
}

#endif