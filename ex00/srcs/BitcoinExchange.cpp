/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/15 14:45:51 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

// Voir si il faut gerer les doublons dans input

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
	checkDataBase(file);
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
		if (isValidDate(std::atoi(line.substr(0, 4).c_str()), std::atoi(line.substr(5, 2).c_str()), std::atoi(line.substr(8, 2).c_str())) == false)
			throw InvalidDateException();
		if (isValidValue(line, commasPos) == false)
			throw InvalidPriceException();
		if (this->_btcDataBase.find(line.substr(0, commasPos)) != this->_btcDataBase.end())
			throw InvalidAmountException();
		this->_btcDataBase.insert(std::pair<std::string, double>(line.substr(0, commasPos), std::strtod(line.substr(commasPos + 1, line.size()).c_str(), NULL)));
	}
	return ;
}

void	BitcoinExchange::printAmount(std::ifstream& file)
{
	int			i = 1;
	std::string	line;
	std::map<std::string, double>::iterator it;

	while (getline(file, line))
	{
		if (i++ == 1)
			continue ;
		if (checkAmountDataBase(line) == false)
			continue ;
		else if (this->_btcDataBase.find(line.substr(0, 10)) != this->_btcDataBase.end())
			std::cout <<  line.substr(0, 10) << " => " << line.substr(13, line.length()) << " = " << this->_btcDataBase[line.substr(0, 10)] * std::strtod(line.substr(12, line.size()).c_str(), NULL) << std::endl;
		else {
			it = this->_btcDataBase.lower_bound(line.substr(0, 10));
			it--;
			std::cout <<  line.substr(0, 10) << " => " << line.substr(13, line.length()) << " = " << this->_btcDataBase[it->first] * std::strtod(line.substr(12, line.size()).c_str(), NULL) << std::endl;
		}
	}
	return ;
}

bool	BitcoinExchange::checkAmountDataBase(std::string& line)
{
	if (line.substr(10, 3) != " | ") {
		std::cout << "Error: bad input => " << line.substr(0, 10) << std::endl;
		return false;
	} else if (std::strtold(line.substr(12, line.length()).c_str(), NULL) > 2147483647) {
		std::cout << "Error: too large number." << std::endl;
		return false;
	} else if (isValidValue(line, 12) == false) {
		std::cout << "Error: not a positive number." << std::endl;
		return false;
	}
	return true;
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

bool	BitcoinExchange::isValidValue(std::string line, int pos)
{
	char	*endPtr;
	double	value = std::strtod(line.substr(pos + 1, line.length()).c_str(), &endPtr);

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
