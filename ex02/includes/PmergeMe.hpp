/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:22 by tduprez           #+#    #+#             */
/*   Updated: 2024/02/12 17:03:48 by tduprez          ###   ########lyon.fr   */
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

		PmergeMe(void);
		void			pushInputToContainers(char** arg);
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
		template<typename Container>
		int				getIndexToSearch(Container S, int numberToSearch);

	public:
		PmergeMe(char** arg);
		PmergeMe(const PmergeMe& src);
		PmergeMe &operator=(const PmergeMe& src);
		~PmergeMe(void);

		void			executePmergeMe(void);
};

class ErrorException : public std::exception
{
	public:
		virtual const char* what() const throw();
};

#endif
