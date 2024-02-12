/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:22 by tduprez           #+#    #+#             */
/*   Updated: 2024/02/12 17:06:25 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <list>
#include <sstream>

class RPN
{
	private:
		RPN(void);
		RPN(const RPN& src);
		RPN &operator=(const RPN& src);
		~RPN(void);

		static std::stack<int, std::list<int> >	_stackRPN;
		static void	makeCalculation(std::string& token);
		static bool	istoken(char c);

	public:
		static void	executeRPN(std::string rpn);
};

class ErrorException : public std::exception
{
	public:
		virtual const char* what() const throw();
};

#endif
