/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:07:51 by tduprez           #+#    #+#             */
/*   Updated: 2024/02/05 14:22:15 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac <= 2)
	{
		std::cout << "Usage: ./PmergeMe \"Numbers\"" << std::endl;
		return (1);
	}
	try
	{
		PmergeMe	fordJohnson(av + 1);
		fordJohnson.executePmergeMe();
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		return (1);
	}

	return (0);
}
