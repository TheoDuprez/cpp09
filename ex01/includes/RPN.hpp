/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:22 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/16 15:52:15 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>

class RPN
{
	private:
		RPN(void);
		RPN(const RPN& src);
		RPN &operator=(const RPN& src);
		~RPN(void);

		static std::stack<int>	_stackRPN;

	public:
		static void	excecuteRPN(std::string rpn);
};
