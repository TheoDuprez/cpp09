/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/13 04:57:06 by tduprez          ###   ########lyon.fr   */
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
	// checkDataBase(file);
	return ;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
	*this = src;
	return ;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange& src)
{
	if (this != &src)
	{
		///////////////////////////////////////////////////////////////////////////////////////////
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
	return ;
}

void	BitcoinExchange::checkDataBase(std::ifstream& file)
{
	int			commasPos;
	int			i = 1;
	std::string	line;

	

	while (getline(file, line))
	{
		if (i++ == 1)
			continue ;
		commasPos = line.find(',');
		if (commasPos != 10 || isValidLineFormat(line.substr(0, commasPos)) == false)
			throw InvalidLineFormatException();
		if (isValidDate(std::atoi(line.substr(0, 4).c_str()), std::atoi(line.substr(5, 7).c_str()), std::atoi(line.substr(8, 10).c_str())) == false)
			throw InvalidDateException();
		if (isValidPrice(line, commasPos) == false)
			throw InvalidPriceException();
		this->_btcDataBase.insert(std::pair<std::string, double>(line.substr(0, commasPos), std::strtod(line.substr(commasPos + 1, line.size()).c_str(), NULL)));
	}
	return ;
}

void	BitcoinExchange::printAmount(std::ifstream& file)
{
	int			commasPos;
	int			i = 1;
	std::string	line;
	std::string	formatedLine;

	while (getline(file, line))
	{
		if (i++ == 1)
			continue ;
		line = line.substr(0, 10) + "|" + line.substr(13, line.length());
		// line = line.substr(10, 11).c_str();
		std::cout << "test = " << line << std::endl;
		commasPos = line.find(',');
		// if (commasPos != 10 || isValidLineFormat(line.substr(0, commasPos)) == false)
		// 	throw InvalidLineFormatException();
		// if (isValidDate(std::atoi(line.substr(0, 4).c_str()), std::atoi(line.substr(5, 7).c_str()), std::atoi(line.substr(8, 10).c_str())) == false)
		// 	throw InvalidDateException();
		// if (isValidPrice(line, commasPos) == false)
		// 	throw InvalidPriceException();
		this->_btcDataBase.insert(std::pair<std::string, double>(line.substr(0, commasPos), std::strtod(line.substr(commasPos + 1, line.size()).c_str(), NULL)));
	}
	return ;
}

int	BitcoinExchange::countOccurences(std::string line, char c)
{
	int	count = 0;

	for (size_t i = 0; i < line.length(); i++)
		if (line[i] == c)
			count++;
	return (count);
}

bool	BitcoinExchange::isValidLineFormat(std::string line)
{
	if (line.length() != 10 || countOccurences(line, '-') != 2 || line.find('-') != 4 || line.find_last_of('-') != 7)
		return false;
	for (size_t i = 0; i < line.length(); i++)
	{
		if (line[i] == '-')
			continue ;
		if (isdigit(line[i]) == false)
			return false;
	}
	return true;
}

bool	BitcoinExchange::isValidPrice(std::string line, int commasPos)
{
	char	*endPtr;
	double	value = std::strtod(line.substr(commasPos + 1, line.length()).c_str(), &endPtr);

	std::cout << value << std::endl;
	if (*endPtr != 0 || value < 0)
		return false;
	return true;
}

bool	BitcoinExchange::isValidDate(int year, int month, int day)
{
	if ((month > 12 || month < 1) || (year < 1 || year > 9999) || day < 1)
		return false;
	else if (month == 2 && isLeapYear(year) && day > 29)
		return false;
	else if (month == 2 && !isLeapYear(year) && day > 28)
		return false;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
			return false;
	}
	else if (day > 31)
		return false;
	return true;
}

// // Les annees bissextiles sont les annees divisibles par 4, sauf si elles sont divisibles par 100.
// // Toutefois, les annees divisibles par 400 sont bissextiles.

bool	BitcoinExchange::isLeapYear(int year) { return ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0)); }
