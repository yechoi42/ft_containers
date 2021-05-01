/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:52:22 by yechoi            #+#    #+#             */
/*   Updated: 2021/05/01 19:43:18 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <memory>
#include "stddef.h"

namespace ft
{

	struct InputIteratorTag {};
	struct OutputIteratorTag : public InputIteratorTag {};
	struct ForwardIteratorTag : public InputIteratorTag, OutputIteratorTag {};
	struct BidirectionalIteratorTag : public ForwardIteratorTag {};
	struct RandomAccessIteratorTag : public BidirectionalIteratorTag {};
	 
	/* standard iterait traits */
	template <typename Iter>
	struct IteratorTraits
	{
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef difference_type distance_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
   	};
	   
	
	/* iterait traits for pointer */
	template <typename T>
	struct IteratorTraits<T *>
	{
		typedef RandomAccessIteratorTag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef ptrdiff_t distance_type;
		typedef T *pointer;
		typedef T &reference;
	};

	/* iterait traits for const pointer */
	template <typename T>
	struct IteratorTraits<const T *>
	{
		typedef RandomAccessIteratorTag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef ptrdiff_t distance_type;
		typedef T *pointer;
		typedef T &reference;
	};

	/* ReverseIterator member types and member functions (https://en.cppreference.com/w/cpp/iterator/reverse_iterator) */
	template <typename Iter>
	class ReverseIterator
	{
		private:
			Iter m_base;
			ReverseIterator();
		
		public:
			typedef Iter iterator_type;
			typedef typename IteratorTraits<Iter>::difference_type difference_type;
			typedef typename IteratorTraits<Iter>::value_type value_type;
			typedef typename IteratorTraits<Iter>::pointer pointer;
			typedef typename IteratorTraits<Iter>::reference reference;
			typedef typename IteratorTraits<Iter>::iterator_category iterator_category;

			ReverseIterator(Iter base) : m_base(base)
			{}

			ReverseIterator(const ReverseIterator<Iter> &other) : m_base(other.base)
			{}

			~ReverseIterator()
			{}

			ReverseIterator<Iter> &operator=(const ReverseIterator<Iter> &other)
			{
				m_base = other.m_base;
				return (*this);
			}

			Iter base() const
			{
				return (m_base);
			}

			reference operator*() const
			{
				Iter iter(m_base);
				--iter;
				return (*iter);
			}

			pointer operator->() const
			{
				Iter iter(m_base);
				--iter;
				return (ite.operator->())
			}

			ReverseIterator<Iter> &operator++()
			{
				--m_base;
				return (*this);
			}

			ReverseIterator<Iter> &operator--()
			{
				++m_base;
				return (*this);
			}

			ReverseIterator<Iter> operator++(int)
			{
				ReverseIterator<Iter> tmp(m_base++);
				return (tmp);
			}

			ReverseIterator<Iter> operator--(int)
			{
				ReverseIterator<Iter> tmp(m_base--);
				return (tmp);
			}

			ReverseIterator<Iter> &operator+=(difference_type offset)
			{
				m_base -= offset;
				return (*this);
			}

			ReverseIterator<Iter> &operator-=(difference_type offset)
			{
				m_base += offset;
				return (*this);
			}
	};

	/* ReverseIterator non-member fucntion (https://en.cppreference.com/w/cpp/iterator/reverse_iterator) */
	template <typename Iter1, typename Iter2>
	bool operator==(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator!=(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator<(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator<=(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator>(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iter1, typename Iter2>
	bool operator>=(const ReverseIterator<Iter1>& lhs, const ReverseIterator<Iter2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename Iter>
	ReverseIterator<Iter> operator+(typename ReverseIterator<Iter>::difference_type n, const ReverseIterator<Iter>& it)
	{
		ReverseIterator<Iter> tmp(it.base() - n);
		return (tmp);
	}

	template <typename Iter>
	typename ReverseIterator<Iter>::difference_type operator-(const ReverseIterator<Iter>& lhs, const ReverseIterator<Iter>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

}

#endif