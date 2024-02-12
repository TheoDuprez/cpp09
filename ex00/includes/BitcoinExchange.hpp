/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:22 by tduprez           #+#    #+#             */
/*   Updated: 2024/02/12 15:56:34 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <climits>
#include <sstream>

class BitcoinExchange
{
	private:
		BitcoinExchange(void);
		std::map<std::string, double> _btcDataBase;
		void	checkDataBase(std::ifstream& file);
		void	checkInputLine(std::string& line);
		int		countOccurences(std::string& line, char c);
		bool	isValidLineFormat(std::string date, std::string value);
		bool	isLeapYear(int year);
		bool	isValidDate(std::string date);
		bool	isStringContainOnlyNumbers(std::string line);
		bool	isValidValue(std::string& line, int commasPos);

	public:
		BitcoinExchange(std::string dateDataBase);
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange &operator=(const BitcoinExchange& src);
		~BitcoinExchange(void);

		void	printAmount(std::ifstream& file);
};

class InvalidFileException : public std::exception
{
	public:
		virtual const char* what() const throw();
};

class InvalidInputLineException : public std::exception
{
	private:
		std::string _errorMsg;

	public:
		InvalidInputLineException(std::string& errorMsg) : _errorMsg(errorMsg) {}
		~InvalidInputLineException() throw() {}
		virtual const char* what() const throw();
};

class InvalidDataBaseLineException : public std::exception
{
	private:
		const std::string _errorMsg;

	public:
		InvalidDataBaseLineException(const std::string& errorMsg) : _errorMsg(errorMsg) {}
		~InvalidDataBaseLineException() throw() {}
		virtual const char* what() const throw();
};

#endif
