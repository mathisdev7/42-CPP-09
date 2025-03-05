/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:06:01 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/05 10:34:18 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int day, int month, int year)
{
	if (year < 1 || month < 1 || month > 12 || day < 1)
	{
		return false;
	}

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2 && isLeapYear(year))
	{
		daysInMonth[1] = 29;
	}

	return day <= daysInMonth[month - 1];
}

bool isValidDateString(const std::string &dateStr)
{
	if (dateStr.length() != 10 || dateStr[4] != '-' || dateStr[7] != '-')
	{
		return false;
	}

	int year = atoi(dateStr.substr(0, 4).c_str());
	int month = atoi(dateStr.substr(5, 2).c_str());
	int day = atoi(dateStr.substr(8, 2).c_str());

	return isValidDate(day, month, year);
}

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
		std::istringstream iss(value);
		double numericValue;
		std::map<std::string, double>::iterator it;

		iss >> numericValue;
		if (numericValue < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
		}
		else if (numericValue > 1000)
			std::cout << "Error: too large a number." << std::endl;
		else if (!isValidDateString(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
		}
		else
		{
			std::map<std::string, double>::iterator it = data.lower_bound(date);

			if (it == data.end() || it->first != date)
			{
				if (it == data.begin())
				{
					std::cout << "Error: No available previous date for " << date << std::endl;
					return;
				}
				--it;
			}
			std::cout << date << " => " << numericValue << " = " << it->second * numericValue << std::endl;
		}
	}
}
