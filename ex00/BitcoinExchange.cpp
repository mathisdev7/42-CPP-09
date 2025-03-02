/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:06:01 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/02 11:48:12 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void retrieveData(std::string input)
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

void retrieveMyData(std::string filePath, std::function<void (std::string, std::string)> insertData)
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
        insertData(date, value);
    }
}

void processData(std::string line)
{
    if (line.length() == 0)
    {
        std::cout << "Error: Line empty" << std::endl;
        return ;
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