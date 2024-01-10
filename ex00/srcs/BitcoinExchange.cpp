/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/10 17:38:40 by tduprez          ###   ########lyon.fr   */
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
	// do
	parseFile(file, this->_priceDataBase, NULL);
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

void	BitcoinExchange::parseFile(std::ifstream& file, std::map<std::string, double> &map, void (*f)(std::string, std::map<std::string, double> &))
{
	int pos;
	std::string line;

	while (getline(file, line))
	{
		if (f)
		{
			f(line, map);
			pos = line.find('|');
		}
		else
		{
			pos = line.find(',');
		}
		this->_priceDataBase.insert(std::pair<std::string, double>(line.substr(0, pos), std::strtod(line.substr(pos + 1, line.size()).c_str(), NULL)));
	}
	// this->_priceDataBase.erase(--this->_priceDataBase.end());
	// this->_priceDataBase.erase(this->_priceDataBase.rbegin());
	return ;
}

// void	BitcoinExchange::parseDate(std::string line)
// {
// 	int pos = line.find('-');
// 	int year = std::atoi(line.substr(0, pos));
// 	pos = std::find(line.begin() + pos, line.end(), '-');

// 	return ;
// }

// void	BitcoinExchange::parsePrice(double price)
// {

// 	pos = line.find('|');
// 	price = line.substr(pos + 1, line.size());
// 	map.insert(std::pair<std::string, double>(date, std::strtod(price.c_str(), NULL)));
// 	return ;
// }

// // Les annees bissextiles sont les annees divisibles par 4, sauf si elles sont divisibles par 100.
// // Toutefois, les annees divisibles par 400 sont bissextiles.

// bool	isLeapYear(int year) { return ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0)) }

