/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:09:58 by tduprez           #+#    #+#             */
/*   Updated: 2024/02/14 14:33:40 by tduprez          ###   ########lyon.fr   */
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
	if (file.is_open() == false || file.peek() == EOF)
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

	while (file.peek() != EOF && getline(file, line))
	{
		if (i == 1 && !line.empty() && line == "date,exchange_rate") {
			i++;
			continue ;
		} else if (i == 1) {
			oss << "Error at line " << i << ": title of csv should be \"date,exchange_rate\"";
			throw InvalidDataBaseLineException(oss.str());
		}
		commasPos = line.find(',');

		if (commasPos != 10 || isValidLineFormat(line.substr(0, commasPos), line.substr(commasPos + 1, line.length())) == false) {
			oss << "Error at line " << i << ": format invalid, line format should be \"YYYY-MM-DD,VALUE\".";
			throw InvalidDataBaseLineException(oss.str());
		}
		if (isValidDate(line.substr(0, 10)) == false) {
			oss << "Error at line " << i << ": date invalid, date should be between 0001-01-01 and 9999-12-31.";
			throw InvalidDataBaseLineException(oss.str());
		}

		if (isValidValue(line, commasPos) == false || line.substr(commasPos + 1, line.length()) == "-0") {
			oss << "Error at line " << i << ": price invalid, price should be between 0 and 2147483647.";
			throw InvalidDataBaseLineException(oss.str());
		}

		if (this->_btcDataBase.find(line.substr(0, commasPos)) != this->_btcDataBase.end()) {
			oss << "Error at line " << i << ": date already exists.";
			throw InvalidDataBaseLineException(oss.str());
		}

		this->_btcDataBase.insert(std::pair<std::string, double>(line.substr(0, commasPos), std::strtod(line.substr(commasPos + 1, line.size()).c_str(), NULL)));
		i++;
	}
	if (i == 2) {
		oss << "Error at line " << i << ": database need 1 or more key | value.";
		throw InvalidDataBaseLineException(oss.str());
	}
	return ;
}

bool	BitcoinExchange::isValidLineFormat(std::string date, std::string value)
{
	if (date.length() != 10 || std::count(date.begin(), date.end(), '-') != 2 || date.find('-') != 4 || date.find_last_of('-') != 7 || value.length() == 0)
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

bool	BitcoinExchange::isValidDate(std::string date)
{
	int	year = std::atoi(date.substr(0, 4).c_str());
	int	month = std::atoi(date.substr(5, 2).c_str());
	int	day = std::atoi(date.substr(8, 2).c_str());

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
	std::string date;
	std::string value;
	std::map<std::string, double>::iterator it;

	while (getline(file, line))
	{
		if (i++ == 1 && line == "date | value")
			continue ;
		try {
			checkInputLine(line);
		} catch (InvalidInputLineException& e) {
			std::cout << e.what() << std::endl;
			continue ;
		}
		date = line.substr(0, 10);
		value = line.substr(13, line.size());
		if (this->_btcDataBase.find(date) != this->_btcDataBase.end())
			std::cout << date << " => " << value << " = " << this->_btcDataBase[date] * std::strtod(value.c_str(), NULL) << std::endl;
		else {
			it = this->_btcDataBase.lower_bound(date);
			if (it == this->_btcDataBase.begin())
				std::cout << "Error: the date was not found, and no lower date was found." << std::endl;
			else {
				it--;
				std::cout << date << " => " << value << " = " << this->_btcDataBase[it->first] * std::strtod(value.c_str(), NULL) << std::endl;
			}
		}
	}
	return ;
}

void	BitcoinExchange::checkInputLine(std::string& line)
{
	std::string _errorMsg;
	std::string date;
	std::string value;

	if (line.length() > 12) {
		date = line.substr(0, 10);
		value = line.substr(13, line.length());
	}

	if (line.length() < 10 || line.substr(10, 3) != " | " || isValidLineFormat(date, value) == false) {
		_errorMsg = "Error: bad input => " + line.substr(0, line.length());
		throw InvalidInputLineException(_errorMsg);
	}
	if (isValidDate(date) == false) {
		_errorMsg = "Error: invalid date.";
		throw InvalidInputLineException(_errorMsg);
	}
	if (std::strtold(value.c_str(), NULL) > 1000) {
		_errorMsg = "Error: too large a number.";
		throw InvalidInputLineException(_errorMsg);
	}
	if (isValidValue(line, 12) == false || value == "-0") {
		if (std::strtod(value.c_str(), NULL) >= 0)
			_errorMsg = "Error: wrong value.";
		else
			_errorMsg = "Error: not a positive number.";
		throw InvalidInputLineException(_errorMsg);
	}
	return ;
}

const char* InvalidFileException::what() const throw()
{
	return ("Error: invalid file");
}

InvalidInputLineException::InvalidInputLineException(std::string& errorMsg): _errorMsg(errorMsg) {}

InvalidInputLineException::~InvalidInputLineException() throw() {}

const char* InvalidInputLineException::what() const throw()
{
	return _errorMsg.c_str();
}

InvalidDataBaseLineException::InvalidDataBaseLineException(const std::string& errorMsg) : _errorMsg(errorMsg) {}

InvalidDataBaseLineException::~InvalidDataBaseLineException() throw() {}

const char* InvalidDataBaseLineException::what() const throw()
{
	return _errorMsg.c_str();
}
