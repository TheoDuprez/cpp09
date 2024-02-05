/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/02/05 13:15:00 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
	return ;
}

BitcoinExchange::BitcoinExchange(std::string dataBase)
{
	std::ifstream file;

	file.open(dataBase.c_str());
	if (file.is_open() == false)
		throw InvalidFileException();
	checkDataBase(file);
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
	this->_btcDataBase = src._btcDataBase;
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
	std::ostringstream oss;

	while (getline(file, line))
	{
		if (i++ == 1)
			continue ;
		commasPos = line.find(',');
		if (commasPos != 10 || isValidLineFormat(line.substr(0, commasPos), line.substr(commasPos + 1, line.length())) == false) {
			oss << "Error at line " << i - 1 << ": format invalid, line format should be \"YYYY-MM-DD,VALUE\".";
			throw InvalidDataBaseLineException(oss.str());
		} else if (isValidDate(std::atoi(line.substr(0, 4).c_str()), std::atoi(line.substr(5, 2).c_str()), std::atoi(line.substr(8, 2).c_str())) == false) {
			oss << "Error at line " << i - 1 << ": date invalid, date should be between 0001-01-01 and 9999-12-31.";
			throw InvalidDataBaseLineException(oss.str());
		} else if (isValidValue(line, commasPos) == false || line.substr(commasPos + 1, line.length()) == "-0") {
			oss << "Error at line " << i - 1 << ": price invalid, price should be between 0 and 2147483647.";
			throw InvalidDataBaseLineException(oss.str());
		} else if (this->_btcDataBase.find(line.substr(0, commasPos)) != this->_btcDataBase.end()) {
			oss << "Error at line " << i - 1 << ": date already exists.";
			throw InvalidDataBaseLineException(oss.str());
		}
		this->_btcDataBase.insert(std::pair<std::string, double>(line.substr(0, commasPos), std::strtod(line.substr(commasPos + 1, line.size()).c_str(), NULL)));
	}
	return ;
}

bool	BitcoinExchange::isValidLineFormat(std::string date, std::string value)
{
	if (date.length() != 10 || countOccurences(date, '-') != 2 || date.find('-') != 4 || date.find_last_of('-') != 7 || value.length() == 0)
		return false;
	for (size_t i = 0; i < date.length(); i++)
	{
		if (date[i] == '-')
			continue ;
		if (isdigit(date[i]) == false)
			return false;
	}
	if (isStringContainOnlyNumbers(value) == false)
		return false;
	return true;
}

bool	BitcoinExchange::isStringContainOnlyNumbers(std::string line)
{
	size_t	i = 0;

	if (line[i] == '-')
		i++;
	for (; i < line.length(); i++)
		if (isdigit(line[i]) == false && line[i] != '.')
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

bool	BitcoinExchange::isLeapYear(int year) { return ((year % 4 == 0) && (year % 100 != 0 || year % 400 == 0)); }

bool	BitcoinExchange::isValidValue(std::string& line, int pos)
{
	char	*endPtr;
	double	value = std::strtod(line.substr(pos + 1, line.length()).c_str(), &endPtr);

	if (*endPtr != 0 || value < 0 || value > INT_MAX)
		return false;
	return true;
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
		try {
			checkInputLine(line);
		} catch (InvalidInputLineException& e) {
			std::cout << e.what() << std::endl;
			continue ;
		}
		if (this->_btcDataBase.find(line.substr(0, 10)) != this->_btcDataBase.end())
			std::cout <<  line.substr(0, 10) << " => " << line.substr(13, line.length()) << " = " << this->_btcDataBase[line.substr(0, 10)] * std::strtod(line.substr(12, line.size()).c_str(), NULL) << std::endl;
		else {
			it = this->_btcDataBase.lower_bound(line.substr(0, 10));
			it--;
			std::cout <<  line.substr(0, 10) << " => " << line.substr(13, line.length()) << " = " << this->_btcDataBase[it->first] * std::strtod(line.substr(12, line.size()).c_str(), NULL) << std::endl;
		}
	}
	return ;
}

void	BitcoinExchange::checkInputLine(std::string& line)
{
	std::string _errorMsg;

	if (line.length() < 10 || line.substr(10, 3) != " | " || isStringContainOnlyNumbers(line.substr(13, line.length())) == false) {
		_errorMsg = "Error: bad input => " + line.substr(0, line.length());
		throw InvalidInputLineException(_errorMsg);
	} else if (std::strtold(line.substr(12, line.length()).c_str(), NULL) > 1000) {
		_errorMsg = "Error: too large a number.";
		throw InvalidInputLineException(_errorMsg);
	} else if (isValidValue(line, 12) == false || line.substr(13, line.length()) == "-0") {
		_errorMsg = "Error: not a positive number.";
		throw InvalidInputLineException(_errorMsg);
	}
}

int	BitcoinExchange::countOccurences(std::string& line, char c)
{
	int	count = 0;

	for (size_t i = 0; i < line.length(); i++)
		if (line[i] == c)
			count++;
	return (count);
}

const char* InvalidFileException::what() const throw()
{
	return ("Error: invalid file");
}

const char* InvalidInputLineException::what() const throw()
{
	return _errorMsg.c_str();
}

const char* InvalidDataBaseLineException::what() const throw()
{
	return _errorMsg.c_str();
}
