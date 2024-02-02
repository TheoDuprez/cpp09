/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:22 by tduprez           #+#    #+#             */
/*   Updated: 2024/02/02 11:38:43 by tduprez          ###   ########lyon.fr   */
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
#include <algorithm>
#include <ctime>

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

		void			pushInputToContainers(char** arg);
		void			executePmergeMe(void);
		void			pmergeMeDeque(void);
		void			pmergeMeVector(void);
		template<typename PairContainer, typename Container>
		void			createPair(PairContainer& pairContainer, Container& vec);
		template<typename PairContainer>
		void			sortPair(PairContainer& pairContainer);
		template<typename PairContainer>
		PairContainer	mergeSort(PairContainer vec);
		template<typename PairContainer, typename Container>
		void			fillS(PairContainer pairContainer, Container& S);
		template<typename PairContainer, typename Container>
		void			insertIntoS(PairContainer pairContainer, Container& S);
		template<typename PairContainer>
		PairContainer	mergeArray(PairContainer left, PairContainer right);
		// void								fillS(std::vector<std::pair<int, int> > pairContainer, Container& S);
		// void								insertIntoS(std::vector<std::pair<int, int> > pairContainer, std::vector<int>& S);
		template<typename Container>
		int				getIndexToSearch(Container S, int numberToSearch);
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
