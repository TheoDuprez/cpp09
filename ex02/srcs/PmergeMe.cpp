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

std::vector<std::pair<int, int> > mergeArray(std::vector<std::pair<int, int> > left, std::vector<std::pair<int, int> > right);

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
	std::cout << std::endl << "After:   ";
	for (size_t i = 0; i < this->vec.size(); i++)
		std::cout << this->vec[i] << " ";
	std::cout << std::endl;
	std::cout << "Time to process a range of " << this->vec.size() << " elements with std::vector : " << static_cast<double>(time) << " us" << std::endl;
}

void	PmergeMe::pmergeMeVector(void)
{
	std::vector<std::pair<int, int> >	pairVector;
	std::vector<int>					S;
	std::vector<int>					pend;

	createPair(pairVector);
	sortPair(pairVector);
	pairVector = mergeSortVector(pairVector);
	fillS(pairVector, S);
	insertIntoS(pairVector, S);
	this->vec = S;
	return ;
}

void	PmergeMe::fillS(std::vector<std::pair<int, int> > pairVector, std::vector<int>& S)
{
	std::vector<std::pair<int, int> >::iterator start = pairVector.begin();
	S.push_back(start->first);
	for (; start != pairVector.end(); start++)
		S.push_back(start->second);
	return ;
}

int	PmergeMe::determineNumberOfSuit(int power, int oldNumber)
{
	return ((2 << power) - oldNumber);
}

int	PmergeMe::getIndexToSearch(std::vector<int> S, int numberToSearch)
{
	int	i = 0;
	while (S[i++] < numberToSearch)
		;
	return (i);
}

void	PmergeMe::insertIntoS(std::vector<std::pair<int, int> > pairVector, std::vector<int>& S)
{
	int	suitNumber = 2;
	int	oldNumber;
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
			if (numberInserted == pairVector.size() - 1)
			{
				if (this->straggler != -1)
					S.insert(std::upper_bound(S.begin(), S.end(), this->straggler), this->straggler);
				return ;
			}
			if (index > pairVector.size() - 1)
				index = pairVector.size() - 1;
			S.insert(std::upper_bound(S.begin(), S.begin() + getIndexToSearch(S, (pairVector.begin() + index)->first), (pairVector.begin() + index)->first), (pairVector.begin() + index)->first);
			numberInserted++;
		}
		oldIndex += suitNumber;
	}
	return ;
}

std::vector<std::pair<int, int> > PmergeMe::mergeSortVector(std::vector<std::pair<int, int> > vec)
{
	if (vec.size() < 2)
		return vec;
	std::vector<std::pair<int, int> > left(vec.begin(), vec.begin() + vec.size() / 2);
	std::vector<std::pair<int, int> > right(vec.begin() + vec.size() / 2, vec.end());
	return mergeArray(mergeSortVector(left), mergeSortVector(right));
}

std::vector<std::pair<int, int> > mergeArray(std::vector<std::pair<int, int> > left, std::vector<std::pair<int, int> > right)
{
	std::vector<std::pair<int, int> >	res;
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
	return ;
}

void	PmergeMe::pmergeMeDeque(void)
{
	// PmergeMe::checkInput(arg);
}
