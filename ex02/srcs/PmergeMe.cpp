/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/18 13:53:08 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
	return ;
}

PmergeMe::PmergeMe(char** arg)
{
	this->straggler = -1;
	pushInputToContainers(arg);
	return ;
}

PmergeMe::PmergeMe(const PmergeMe& src)
{
	*this = src;
	return ;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& src)
{
	(void)src;
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
	return ;
}

void	PmergeMe::pushInputToContainers(char** arg)
{
	double	numberToCheck;
	char*	endPtr;

	for (int i = 0; arg[i]; i++)
	{
		numberToCheck = strtod(arg[i], &endPtr);
		if (numberToCheck < 0 || numberToCheck > INT_MAX || *endPtr != 0)
			throw ErrorException();
		else
		{
			this->deq.push_back(numberToCheck);
			this->vec.push_back(numberToCheck);
		}
	}
	if (vec.size() % 2 != 0) 
	{
		this->straggler = this->vec.back();
		this->vec.pop_back();
		this->deq.pop_back();
	}
	return ;
}

void	PmergeMe::pmergeMeVector(void)
{
	std::vector<std::pair<int, int> >	pairVector;

	createPair(pairVector);
	sortPair(pairVector);
}

void	PmergeMe::createPair(std::vector<std::pair<int, int> >& pairVector)
{
	for (std::vector<int>::iterator start = this->vec.begin(); start != this->vec.end(); start++)
		pairVector.push_back(std::make_pair(*start, *(++start)));
	return ;
}

void	PmergeMe::sortPair(std::vector<std::pair<int, int> >& pairVector)
{
	int	tmp;

	for (std::vector<std::pair<int, int> >::iterator start = pairVector.begin(); start != pairVector.end(); start++)
	{
		if (start->first > start->second)
		{
			tmp = start->first;
			start->first = start->second;
			start->second = tmp;
		}
	}
	// mettre merge sort par ici
	return ;
}













void	PmergeMe::pmergeMeDeque(void)
{
	// PmergeMe::checkInput(arg);
}
