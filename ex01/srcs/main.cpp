/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:07:51 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/18 13:40:31 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage: ./RPN \"RPN NOTATION\"" << std::endl;
		return (1);
	}

	try
	{
		RPN::excecuteRPN(av[1]);
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		return (1);
	}

	return (0);
}
