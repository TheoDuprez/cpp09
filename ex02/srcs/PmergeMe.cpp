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
	static_cast<void>(src);
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
	if (this->vec.size() % 2 != 0)
	{
		this->straggler = this->vec.back();
		this->vec.pop_back();
		this->deq.pop_back();
	}
	return ;
}

void	PmergeMe::executePmergeMe(void)
{
	clock_t timeVec;
	clock_t timeDeq;

	std::cout << "Before:  ";
	for (size_t i = 0; i < this->vec.size(); i++)
		std::cout << this->vec[i] << " ";
	if (this->straggler != -1)
		std::cout << this->straggler << " ";
	std::cout << std::endl;
	timeVec = clock();
	pmergeMeVector();
	timeVec = clock() - timeVec;
	timeDeq = clock();
	pmergeMeDeque();
	timeDeq = clock() - timeDeq;
	std::cout << std::endl << "After:   ";
	for (size_t i = 0; i < this->vec.size(); i++)
		std::cout << this->vec[i] << " ";
	std::cout << std::endl;
	std::cout << "Time to process a range of " << this->vec.size() << " elements with std::vector : " << static_cast<double>(timeVec) << " us" << std::endl;
	std::cout << "Time to process a range of " << this->deq.size() << " elements with std::deque  : " << static_cast<double>(timeDeq) << " us" << std::endl;
}

void	PmergeMe::pmergeMeVector(void)
{
	std::vector<std::pair<int, int> >	pairContainer;
	std::vector<int>					S;

	createPair(pairContainer, this->vec);
	sortPair(pairContainer);
	pairContainer = mergeSort(pairContainer);
	fillS(pairContainer, S);
	insertIntoS(pairContainer, S);
	this->vec = S;
	return ;
}

void	PmergeMe::pmergeMeDeque(void)
{
	std::deque<std::pair<int, int> >	pairContainer;
	std::deque<int>					S;

	createPair(pairContainer, this->deq);
	sortPair(pairContainer);
	pairContainer = mergeSort(pairContainer);
	fillS(pairContainer, S);
	insertIntoS(pairContainer, S);
	this->deq = S;
	return ;
}

template<typename PairContainer, typename Container>
void	PmergeMe::createPair(PairContainer& pairContainer, Container& vec)
{
	for (typename Container::iterator start = vec.begin(); start != vec.end(); start++)
		pairContainer.push_back(std::make_pair(*start, *(++start)));
	return ;
}

template<typename PairContainer>
void	PmergeMe::sortPair(PairContainer& pairContainer)
{
	int	tmp;

	for (typename PairContainer::iterator start = pairContainer.begin(); start != pairContainer.end(); start++)
	{
		if (start->first > start->second)
		{
			tmp = start->first;
			start->first = start->second;
			start->second = tmp;
		}
	}
	return ;
}

template<typename PairContainer>
PairContainer PmergeMe::mergeSort(PairContainer pairContainer)
{
	if (pairContainer.size() < 2)
		return pairContainer;
	PairContainer left(pairContainer.begin(), pairContainer.begin() + pairContainer.size() / 2);
	PairContainer right(pairContainer.begin() + pairContainer.size() / 2, pairContainer.end());
	return mergeArray(mergeSort(left), mergeSort(right));
}

template<typename PairContainer>
PairContainer PmergeMe::mergeArray(PairContainer left, PairContainer right)
{
	PairContainer		res;
	size_t				leftIndex = 0;
	size_t				rightIndex = 0;

	while (leftIndex < left.size() && rightIndex < right.size())
	{
		if (left[leftIndex].second < right[rightIndex].second)
			res.push_back(left[leftIndex++]);
		else
			res.push_back(right[rightIndex++]);
	}
	while (leftIndex < left.size())
		res.push_back(left[leftIndex++]);
	while (rightIndex < right.size())
		res.push_back(right[rightIndex++]);
	return res;
}

template<typename PairContainer, typename Container>
void	PmergeMe::fillS(PairContainer pairContainer, Container& S)
{
	typename PairContainer::iterator start = pairContainer.begin();
	S.push_back(start->first);
	for (; start != pairContainer.end(); start++)
		S.push_back(start->second);
	return ;
}

template<typename PairContainer, typename Container>
void	PmergeMe::insertIntoS(PairContainer pairContainer, Container& S)
{
	int		suitNumber = 2;
	int		oldNumber;
	size_t	oldIndex = 0;
	size_t	numberInserted = 0;

	for (int i = 0; true; i++)
	{
		if (i == 0)
			oldNumber = 0;
		else
			oldNumber = suitNumber;
		suitNumber = (2 << i) - oldNumber;
		for (size_t index = suitNumber + oldIndex; index > oldIndex; index--)
		{
			if (numberInserted == pairContainer.size() - 1)
			{
				if (this->straggler != -1)
					S.insert(std::upper_bound(S.begin(), S.end(), this->straggler), this->straggler);
				return ;
			}
			if (index > pairContainer.size() - 1)
				index = pairContainer.size() - 1;
			S.insert(std::upper_bound(S.begin(), S.begin() + getIndexToSearch(S, (pairContainer.begin() + index)->second), (pairContainer.begin() + index)->first), (pairContainer.begin() + index)->first);
			numberInserted++;
		}
		oldIndex += suitNumber;
	}
	return ;
}

template<typename Container>
int	PmergeMe::getIndexToSearch(Container S, int numberToSearch)
{
	int	i = 0;
	while (S[i++] < numberToSearch)
		;
	return (i);
}
