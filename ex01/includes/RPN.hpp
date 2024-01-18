/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:22 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/18 13:40:04 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <sstream>

class RPN
{
	private:
		RPN(void);
		RPN(const RPN& src);
		RPN &operator=(const RPN& src);
		~RPN(void);

		static std::stack<int>	_stackRPN;

	public:
		static void	makeCalculation(std::string& token);
		static bool	istoken(char c);
		static void	excecuteRPN(std::string rpn);
};

class ErrorException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Error");
		}
};
