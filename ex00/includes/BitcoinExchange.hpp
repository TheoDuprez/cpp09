/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tduprez <tduprez@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:03:22 by tduprez           #+#    #+#             */
/*   Updated: 2024/01/10 13:59:21 by tduprez          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <string>
#include <sstream>

class BitcoinExchange
{
	private:
		BitcoinExchange(void);
		std::map<std::string, double> _priceDataBase;
		std::map<std::string, double> _dateDataBase;

	public:
		BitcoinExchange(std::string dateDataBase);
		BitcoinExchange(const BitcoinExchange& src);
		BitcoinExchange &operator=(const BitcoinExchange& src);
		~BitcoinExchange(void);

		void	parseFile(std::ifstream& file, std::map<std::string, double> &map, void (*f)(std::string, std::map<std::string, double> &));
};
