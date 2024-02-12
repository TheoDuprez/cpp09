/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/02/12 17:06:56 by tduprez          ###   ########lyon.fr   */
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

void	RPN::executeRPN(std::string rpn)
{
	std::istringstream	iss(rpn);
	std::string			token;

	if (rpn.empty())
		throw ErrorException();
	while (iss >> token)
	{
		if ((token.length() == 1 && isdigit(token[0])) || (token.length() == 2 && token[0] == '-' && isdigit(token[1])))
			_stackRPN.push(std::atoi(token.c_str()));
		else if (istoken(token[0]) == true && _stackRPN.size() >= 2)
			makeCalculation(token);
		else
			throw ErrorException();
	}
	if (_stackRPN.size() != 1)
		throw ErrorException();
	std::cout << _stackRPN.top() << std::endl;

	return ;
}

bool	RPN::istoken(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return (true);
	return (false);
}

void	RPN::makeCalculation(std::string& token)
{
	int	number1 = _stackRPN.top();
	_stackRPN.pop();
	int	number2 = _stackRPN.top();
	_stackRPN.pop();
	int	res;

	switch (token[0])
	{
		case '+':
			res = number2 + number1;
			break;
		case '-':
			res = number2 - number1;
			break;
		case '*':
			res = number2 * number1;
			break;
		case '/':
			if (number1 == 0)
				throw ErrorException();
			res = number2 / number1;
			break;
	}
	_stackRPN.push(res);
	return ;
}

const char* ErrorException::what() const throw()
{
	return ("Error");
}

std::stack<int, std::list<int> >	RPN::_stackRPN;
