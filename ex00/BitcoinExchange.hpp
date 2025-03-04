/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:05:56 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/03 15:40:09 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <exception>
#include <cstring>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>

class FileNotFoundException : public std::exception
{
	virtual const char *what() const throw()
	{
		return "File not found.";
	}
};

class FileContentWrong : public std::exception
{
	virtual const char *what() const throw()
	{
		return "File content must have this pattern: date | value.";
	}
};
class BitcoinExchange
{
private:
	std::map<std::string, double> data;
	BitcoinExchange() {};

public:
	void insertData(std::string date, std::string value);
	BitcoinExchange(std::string input);
	~BitcoinExchange();
	void retrieveData(std::string input);
	void processData(std::string line);
	void retrieveMyData(std::string filePath);
};
