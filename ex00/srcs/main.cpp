/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:07:51 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/15 12:57:15 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Usage: ./btc [dateDataBase]" << std::endl;
		return (1);
	}

	try
	{
		std::ifstream file(av[1]);
		if (!file.is_open())
			throw InvalidFileException();
		BitcoinExchange exchange((std::string("data.csv")));
		exchange.printAmount(file);
	}
	catch(const std::exception& e)
	{
		std::cout << "Error : " << e.what() << std::endl;
	}

	return (0);
}
