/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/16 16:40:04 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"
#include <cstdlib>

RPN::RPN(void)
{
	return ;
}

RPN::RPN(const RPN& src)
{
	*this = src;
	return ;
}

RPN& RPN::operator=(const RPN& src)
{
	(void)src;
	return (*this);
}

RPN::~RPN(void)
{
	return ;
}

void	RPN::excecuteRPN(std::string rpn)
{
	for (size_t i = 0; i < rpn.length(); i++)
	{
		if (i % 2 == 0)
			continue ;
		RPN::_stackRPN.push(std::atoi(&rpn[i]));
	}
	while (RPN::_stackRPN.empty() == false)
	{
		std::cout << "TEST\n";
		std::cout << _stackRPN.top();
		RPN::_stackRPN.pop();
		if (RPN::_stackRPN.empty() == false)
			std::cout << " ";
	}
	std::cout << std::endl;
	return ;
}

std::stack<int>	RPN::_stackRPN;
