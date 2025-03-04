/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:06:01 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/03 15:58:55 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(std::string input)
{
	retrieveMyData("data.csv");
	retrieveData(input);
}

BitcoinExchange::~BitcoinExchange() {};

void BitcoinExchange::retrieveData(std::string input)
{
	std::string line;
	std::ifstream infile(input.c_str());
	if (!infile)
		throw FileNotFoundException();
	while (getline(infile, line))
	{
		// if (line.find("|") == std::string::npos)
		// {
		//     throw FileContentWrong();
		// }
		processData(line);
	}
}
void BitcoinExchange::insertData(std::string date, std::string value)
{
	std::istringstream iss(value);
	double numericValue;
	std::map<std::string, double>::iterator it;

	iss >> numericValue;
	if (numericValue < 0)
	{
		std::cout << numericValue << std::endl;
		throw FileContentWrong();
	}
	data.insert(std::make_pair(date, numericValue));
	it = data.find("2012-01-11");
	std::cout << "Date: " << date << ", " << "Value: " << numericValue << std::endl;
	if (it->first.length() > 0)
		std::cout << it->first << std::endl;
}
void BitcoinExchange::retrieveMyData(std::string filePath)
{
	std::string line;
	std::ifstream infile(filePath.c_str());
	if (!infile)
		throw FileNotFoundException();
	while (getline(infile, line))
	{
		std::istringstream iss(line);
		std::string date;
		std::string value;
		std::string token;
		int iteration = 0;
		while (std::getline(iss, token, ',') && iteration < 2)
		{
			token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
			if (iteration == 0 && token.length() > 0)
				date = token;
			else if (iteration == 1 && token.length() > 0)
				value = token;
			iteration++;
		}
		if (iteration == 1 || iteration < 1)
			std::cout << "Error: No data found for date: " << token << std::endl;
		this->insertData(date, value);
	}
}

void BitcoinExchange::processData(std::string line)
{
	if (line.length() == 0)
	{
		std::cout << "Error: Line empty" << std::endl;
		return;
	}
	std::istringstream iss(line);
	std::string date;
	std::string value;
	std::string token;
	int iteration = 0;
	while (std::getline(iss, token, '|') && iteration < 2)
	{
		token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
		if (iteration == 0 && token.length() > 0)
			date = token;
		else if (iteration == 1 && token.length() > 0)
			value = token;
		iteration++;
	}
	if (iteration == 1 || iteration < 1)
		std::cout << "Error: No data found for date: " << token << std::endl;
	else
	{
		std::cout << "Date: " << date << ", " << "Value: " << value << std::endl;
	}
}
