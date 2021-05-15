/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:49:49 by yechoi            #+#    #+#             */
/*   Updated: 2021/05/04 17:22:06 by yechoi           ###   ########.fr       */
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

	/* deque class (https://en.cppreference.com/w/cpp/container/deque) */
	template <typename T, typename Alloc = std::allocator<T> >
	class Deque
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
			typedef DequeIterator<T> iterator;
			typedef DequeIterator<T> const_iterator;
			typedef ReverseIterator<iterator> reverse_iterator;
			typedef ReverseIterator<const_iterator> const_reverse_iterator;

		private:
			typedef T** map_pointer;
			typedef Deque<T> Self;

			map_pointer m_map;
			size_type m_size;
			iterator m_start;
			iterator m_finish;

			enum { initial_map_size = 8 };
			
			static size_t buffer_size()
			{
				return DEQUE_BUF_SIZE_FOR(T);
			}

			/* https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a00533_source.html :: 682 */
			void initialize_map(size_t num_elements)
			{
				std::allocator<T *> map_allocator:
				const size_t num_nodes = num_elements / buffer_size() + 1;

				m_size = max((size_t)initial_map_size, size_t(num_nodes + 2));
				m_map = map_allocator.allocate(buffer_size());

				map_pointer nstart = m_map + (m_size - num_nodes) / 2; // 앞에 남는거 반절 또는 노드 하나 남겨두기
				map_pointer nfinish = nstart + num_nodes; // nfinish 뒤에도 마찬가지로 남음
				
				std::allocator<T> allocator;
				for (map_pointer cur = nstart; cur < nfinish; ++cur)
				{
					*cur = allocator.allocate(buffer_size());
				}

				m_start.set_node(nstart);
				m_start.m_cur = nstart.m_first;
				m_finish.set_node(nfinish - 1);
				m_finish.m_cur = m_finish.m_first + num_elements % buffer_size();
			}

			void destroy_data(iterator first, iterator last)
			{
				Alloc alloc;

				for (map_pointer node = first.m_node + 1; node < last.m_node; ++node)
				{
					for (pointer p = *node; p < *node + buffer_size(); p++)
					{
						alloc.destroy(p);
					}
				}

				if (first.m_node != last.m_node)
				{
					for (pointer p = first.m_cur; p < first.m_last; p++)
						alloc.destroy(p);
					for (pointer p = last.m_first; p < last.m_cur; p++)
						alloc.destroy(p);
				}
				else
				{
					for (pointer p = first.m_cur; p < last.m_cur; p++)
						allloc.destroy(p);
				}
			}

			void destroy_node(map_pointer first, map_pointer last)
			{
				Alloc alloc;
				
				for (map_pointer cur = first; cur < last; ++cur)
					alloc.deallocate(*cur, buffer_size());
			}

		public:
			/* constructor */
			Deque()
				: m_map(), m_size(0), m_start(), m_finish()
			{
				initialize_map(0);
			}

			// explicit
			// Deque(const allocator_type& a)

			explicit 
			Deque(size_type count, const value_type& value = value_type())
				: m_map(), m_size(0), m_start(), m_finish()
			{
				initialize_map(0);
				
			}

			/* element access */
			
			
			/* iterators */
			iterator
			begin()
			{
				return (m_start);
			}

			const_iterator
			begin() const
			{
				return (const_iterator(m_start));
			}

			iterator
			end()
			{
				return (m_finish);
			}

			const_iterator
			end() const
			{
				return (const_iterator(m_finish));
			}

			reverse_iterator
			rbegin()
			{
				return (reverse_iterator(m_finish));
			}

			const_reverse_iterator
			rbegin() const
			{
				return (const_reverse_iterator(m_finish));
			}

			reverse_iterator
			rend()
			{
				return (reverse_iterator(m_start));
			}

			const_reverse_iterator
			rend() const
			{
				return (const_reverse_iterator(m_start));
			}

			/* capacity */
			void
			empty() const
			{
				return (m_finish == m_start);
			}

			size_type
			size() const
			{
				return (m_finish - m_start);
			}

			size_type
			max_size() const
			{
				return (allocator_type().max_size());
			}


			/* modifiers */
			void
			clear()
			{
				erase(begin(), end());
			}

			iterator
			erase(iterator pos)
			{
				return (erase(pos, pos + 1));
			}

			iterator
			erase(iterator first, iterator last)
			{
				if (first == last)
					return (first);
				else
				{
					const difference_type n = last - first;
					const difference_type elems_before = first - begin();
					if (static_cast<size_type>(elems_before) <= (size() - n) / 2)
					{
						// move data before first
						if (first != begin())
						{
							move_backward(begin(), first, last);
						}
						// erase data before moved data
						iterator pos = begin() + n;
						destroy_data(begin(), post);
						destroy_node(begin().m_node, pos.m_node);
						m_start = pos;
					}
					else
					{
						if (last != end())
							move(last, end(), first);
						iterator pos = end() - n;
						destroy_data(pos, end);
						destroy_node(pos.m_node + 1, end.m_node + 1);
						m_finish = pos;
					}
					return (begin() + elems_before);
				}
			}
	};
}

#endif