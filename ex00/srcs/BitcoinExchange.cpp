/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/09 18:06:52 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	return ;
}

BitcoinExchange::BitcoinExchange(std::string priceDataBase)
{
	std::ifstream file;

	file.open(priceDataBase.c_str());
	if (!file.is_open())
	{
		std::cout << "Error: " << priceDataBase << " is not a valid file" << std::endl;
		exit(1);
	}
	do
	{
		int pos;
		std::string line;
		getline(file, line);

		pos = line.find(',');
		this->_priceDataBase.insert(std::pair<std::string, double>(line.substr(0, pos), std::strtod(line.substr(pos + 1, line.size()).c_str(), NULL)));
		
	} while (file.good());
	// while (file.good())
	// {
	// }
	for (std::map<std::string, double>::iterator start = this->_priceDataBase.begin(); start != this->_priceDataBase.end(); start++)
		std::cout << start->first << " | " << start->second << std::endl;
	return ;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
	if (this != &src)
		*this = src;
	return ;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& src)
{
	if (this != &src)
	{
		
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
	return ;
}
