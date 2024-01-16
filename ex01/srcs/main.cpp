/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:07:51 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/16 15:38:45 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

int main(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		std::cout << "Usage: ./RPN \"RPN NOTATION\"" << std::endl;
		return (1);
	}
	
	RPN::excecuteRPN(av[1]);
	return (0);
}
