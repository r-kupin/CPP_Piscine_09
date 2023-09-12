/******************************************************************************/
/*                                                                            */
/*                                                         :::      ::::::::  */
/*    MutantStack.h                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*    Created: 2023/02/27 00:03:42 by rokupin           #+#    #+#            */
/*                                                     ###   ########.fr      */
/*                                                                            */
/******************************************************************************/

#ifndef EX02_MUTANTSTACK_H
#define EX02_MUTANTSTACK_H


#include <stack>

template <typename T>
class MutantStack : public std::stack<T> {
public:
	typedef
		typename std::deque<T>::iterator
										iterator;
	typedef
		typename std::deque<T>::reverse_iterator
										reverse_iterator;
	typedef
		typename std::deque<T>::const_iterator
										const_iterator;
	typedef
		typename std::deque<T>::const_reverse_iterator
										const_reverse_iterator;

	MutantStack()
	: std::stack<T>(), base_deque_(this->c) {}
	MutantStack(const MutantStack &other)
	: std::stack<T>(other), base_deque_(other->c) {}

	~MutantStack(){};

	MutantStack &operator=(MutantStack const &other) {
		std::stack<T>::operator=(other);
		return *this;
	}

	/**
	 *  Returns a read/write iterator that points to the first element in the
	 *  %deque.  Iteration is done in ordinary element order.
	 */
	iterator begin() { return base_deque_.begin(); }

	/**
	 *  Returns a read-only (constant) iterator that points to the first
	 *  element in the %deque.  Iteration is done in ordinary element order.
	 */
	const_iterator begin() const { return base_deque_.begin(); }

	/**
	 *  Returns a read/write iterator that points one past the last
	 *  element in the %deque.  Iteration is done in ordinary
	 *  element order.
	 */
	iterator end() { return base_deque_.end(); }

	/**
	 *  Returns a read-only (constant) iterator that points one past
	 *  the last element in the %deque.  Iteration is done in
	 *  ordinary element order.
	 */
	const_iterator end() const { return base_deque_.end(); }

	/**
	 *  Returns a read/write reverse iterator that points to the
	 *  last element in the %deque.  Iteration is done in reverse
	 *  element order.
	 */
	reverse_iterator rbegin() { return base_deque_.rbegin(); }

	/**
	 *  Returns a read-only (constant) reverse iterator that points
	 *  to the last element in the %deque.  Iteration is done in
	 *  reverse element order.
	 */
	const_reverse_iterator rbegin() const { return base_deque_.rbegin(); }

	/**
	 *  Returns a read/write reverse iterator that points to one
	 *  before the first element in the %deque.  Iteration is done
	 *  in reverse element order.
	 */
	reverse_iterator rend() { return base_deque_.rend(); }

	/**
	 *  Returns a read-only (constant) reverse iterator that points
	 *  to one before the first element in the %deque.  Iteration is
	 *  done in reverse element order.
	 */
	const_reverse_iterator rend() const { return base_deque_.rend(); }

private:
	std::deque<T> &base_deque_;
};


#endif //EX02_MUTANTSTACK_H
