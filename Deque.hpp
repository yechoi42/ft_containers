/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:49:49 by yechoi            #+#    #+#             */
/*   Updated: 2021/05/17 15:48:13 by yechoi           ###   ########.fr       */
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

	/* non-member functions */
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

			void reallocate_map(size_type nodes_to_add, bool add_at_front)
			{
				std::allocator<T *> map_alloc;

				const size_type old_num_node = m_finish.m_node - m_start.m_node + 1;
				const size_type new_num_nodes = old_num_node + nodes_to_add;

				map_pointer new_nstart;
				if (m_size > 2 * new_num_nodes)
				{
					new_nstart = m_map + (m_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
					if (new_nstart < m_start.m_node)
						std::copy(m_start.m_node, m_finish.m_node + 1, new_nstart);
					else
						std::copy_backward(m_start.m_node, m_finish.m_node + 1, new_nstart + old_num_node);
				}
				else
				{
					size_type new_map_size = m_size + std::max(m_size, nodes_to_add) + 2;
					map_pointer new_map = map_alloc.allocate(new_map_size);
					new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
					std::copy(m_start.node, m_finish.node + 1, new_nstart);
					map_alloc.deallocate(m_map, m_size);
					m_map = new_map;
					m_size = new_map_size;

				}
				m_start.set_node(new_nstart);
				m_finish.set_node(new_nstart + old_num_node - 1);
			}

			void reserve_back(size_type n)
			{
				Alloc alloc;

				// buffer left on last node
				size_type rest = m_finish.m_last - m_finish.m_cur - 1;
				// if more size is needed than left buffer size
				if (n > rest)
				{
					// find out how many nodes to allocate`
					size_type new_nodes = (n - 1) / buffer_size() + 1;

					// if needed nodes are bigger than left nodes, reallocate new nodes
					if (new_nodes + 1 > m_size - (m_finish.m_node - m_map))
						reallocate_map(new_nodes, false);
					// allocate each buffer on each node
					for (size_type i = 1; i <= new_nodes; ++i)
						*(m_finish.m_node + i) = alloc.allocate(buffer_size());
				}
				return (m_finish + difference_type(n));
			}

			void reserve_front(size_type n)
			{
				Alloc alloc;

				size_type rest = m_start.m_cur - m_start.m_first;
				if (n > rest)
				{
					size_type new_nodes = (n - 1) / buffer_size() + 1;

					if (new_nodes > size_type(m_start.m_node - m_map))
						reallocate_map(new_nodes, true);
					for (size_type i = 1; i <= new_nodes; i++)
					{
						*(m_start.m_node - i) = alloc.allocate(buffer_size());
					}
					return (m_start - difference_type(n));
				}
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

			/* destructor */
			~Deque()
			{
				clear();
				destroy_node(m_start.node, m_finish.node + 1);
				std::allocator<T *> map_alloc;
				map_alloc.deallocate(m_map, m_size);
			}

			void
			assign(size_type count, const T& value)
			{
				clear();

			}

			template<typedef InputIt>
			void assign(Inputit first, InputIt last)
			{

			}

			allocator_type
			get_allocator() const
			{

			}

			/* element access */
			reference
			at(size_type pos)
			{
				if (pos >= size())
				{
					throw (std::out_of_range;)
				}
				return (*this)[pos];
			}

			const_reference
			at(size_type pos) const
			{
				if (pos >= size())
				{
					throw (std::out_of_range;)
				}
				return (*this)[pos];
			}

			reference
			operator[](size_type pos)
			{
				return (m_start[difference_type[n]]);
			}

			const_reference
			operator[](size_type pos) const
			{
				return (m_start[difference_type[n]]);
			}

			reference
			front()
			{
				return (*m_start);
			}

			const_reference
			front() const
			{
				return (*m_start);
			}

			reference
			back()
			{
				return (*(m_finish - 1));
			}

			const_reference
			back() const
			{
				return (*(m_finish - 1));
			}

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
			insert(iterator pos, const T& value)
			{

			}

			void
			insert(iterator pos, size_type count, const T& value)
			{

			}
			
			template< typedef InputIt >
			void 
			insert(iterator pos, InputIt first, InputIt last)
			{
				
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
						destroy_data(begin(), pos);
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

			void
			push_back(const T& value)
			{
				Alloc alloc;
				iterator it = reserve_back(1) - 1;

				alloc.constructor(it.m_cur, value);
				m_finish = it + 1;
			}

			void
			pop_back()
			{
				erase(m_finish - 1);
			}

			void
			push_front(const T& value)
			{
				Alloc alloc;
				iterator it = reserve_front(1);

				alloc.construct(it.m_cur, val);
				m_start = it;
			}

			void
			pop_front
			{
				erase(m_start);
			}

			void
			resize(size_type count, T value = T() )
			{
				if (count >= size())
					insert(end(), count - size(), value);
				else
					erase(begin() + count, end());
			} 

			void
			swap(Self &other)
			{

			}
	};

	/* non-member functions */
	template< class T, class Alloc >
	bool operator==(const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{

	}

	template< class T, class Alloc >
	bool operator!=(const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{

	}

	template< class T, class Alloc >
	bool operator<(const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{

	}

	template< class T, class Alloc >
	bool operator<=(const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{

	}

	template< class T, class Alloc >
	bool operator>(const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{
		
	}

	template< class T, class Alloc >
	bool operator>=(const Deque<T,Alloc>& lhs, const Deque<T,Alloc>& rhs)
	{

	}

	template< class T, class Alloc >
	void swap(Deque<T,Alloc>& lhs, Deque<T,Alloc>& rhs)
	{
		
	}
};
#endif