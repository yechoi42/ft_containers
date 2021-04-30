/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:52:22 by yechoi            #+#    #+#             */
/*   Updated: 2021/04/30 16:56:53 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
#define UTILITY_HPP

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
}

#endif