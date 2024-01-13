/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:22 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/13 04:22:07 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

class BitcoinExchange
{
	private:
		BitcoinExchange(void);
		std::map<std::string, double> _btcDataBase;

	public:
		BitcoinExchange(std::string dateDataBase);
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange &operator=(const BitcoinExchange& src);
		~BitcoinExchange(void);

		void	checkDataBase(std::ifstream& file);
		int		countOccurences(std::string line, char c);
		bool	isValidLineFormat(std::string line);
		void	printAmount(std::ifstream& file);
		bool	isValidDate(int year, int month, int day);
		bool	isValidPrice(std::string line, int commasPos);
		bool	isLeapYear(int year);
};

class InvalidDateException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Invalid date");
		}
};

class InvalidLineFormatException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Invalid line, line format should be \"YYYY-MM-DD,VALUE\"");
		}
};

class InvalidFileException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Invalid file");
		}
};

class InvalidPriceException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Invalid price");
		}
};
