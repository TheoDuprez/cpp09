/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/11 17:57:57 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

bool	isValidDateFormat(std::string line);
bool	isLeapYear(int year);

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
	parseFile(file, this->_priceDataBase, NULL);
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
	int posCommas;
	int i = 1;
	std::string line;

	while (getline(file, line))
	{
		if (i == 1)
		{
			i++;
			continue ;
		}
		if (f)
		{
			f(line, map);
			posCommas = line.find('|');
		}
		else
		{
			posCommas = line.find(',');
		}
		if (isValidDateFormat(line.substr(0, posCommas)) == false)
		{
			std::cout << "Error at lign " << i << ": " << line.substr(0, posCommas) << " is not a valid date" << std::endl;
			exit(1);
		}
		std::cout << line << std::endl;
		this->_priceDataBase.insert(std::pair<std::string, double>(line.substr(0, posCommas), std::strtod(line.substr(posCommas + 1, line.size()).c_str(), NULL)));
		i++;
	}
	// this->_priceDataBase.erase(--this->_priceDataBase.end());
	std::cout << this->_priceDataBase.rbegin()->first << std::endl;
	parseDate(this->_priceDataBase.begin()->first);
	return ;
}

int	countOccurences(std::string line, char c)
{
	int	count = 0;

	for (int i = 0; i < line.length(); i++)
		if (line[i] == c)
			count++;
	return (count);
}

bool	isValidDateFormat(std::string line)
{
	if (line.length() > 10 || countOccurences(line, '-') != 2)
		return false;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '-')
			continue ;
		if (isdigit(line[i]) == false)
			return false;
	}
	return true;
}

bool	isValidDate(int year, int month, int day)
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

void	BitcoinExchange::parseDate(std::string line)
{
	char	*endPtr;
	long	year = std::atoi(line.substr(0, line.find('-')).c_str());
	long	month = std::atoi(line.substr(line.find('-') + 1, line.find_last_of('-')).c_str());
	long	day = std::atoi(line.substr(line.find_last_of('-') + 1, line.length()).c_str());
	
	if (isValidDate(year, month, day) == false)
	{
		std::cout << "Error: " << line << " is not a valid date" << std::endl;
		exit(1);
	}
	// std::cout << year << " " << month << " " << day << std::endl;
	// int pos = line.find('-');
	// int year = std::atoi(line.substr(0, pos).c_str());
	// line.replace(line.begin(), line.begin() + (pos + 1), "");
	// pos = line.find('-');
	// std::cout << line << std::endl;
	// int year = std::atoi(line.substr(0, pos));
	// pos = std::find(line.begin() + pos, line.end(), '-');

	return ;
}

// int	getDate(std::string line)
// {
// 	return ()
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

bool	isLeapYear(int year) { return ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0)); }

