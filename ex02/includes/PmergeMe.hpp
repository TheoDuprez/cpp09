/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:22 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/23 15:16:55 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PmergeMe_HPP
# define PmergeMe_HPP

#include <iostream>
#include <cstdlib>
#include <climits>
#include <deque>
#include <vector>
#include <utility>

class PmergeMe
{
	private:
		std::vector<int>	vec;
		std::deque<int>		deq;
		int					straggler;

	public:
		PmergeMe(void);
		PmergeMe(char** arg);
		PmergeMe(const PmergeMe& src);
		PmergeMe &operator=(const PmergeMe& src);
		~PmergeMe(void);

		void	pmergeMeDeque(void);
		void	pmergeMeVector(void);
		void	createPair(std::vector<std::pair<int, int> >& pairVector);
		void	sortPair(std::vector<std::pair<int, int> >& pairVector);
		void	pushInputToContainers(char** arg);
};

class ErrorException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Error");
		}
};

#endif
