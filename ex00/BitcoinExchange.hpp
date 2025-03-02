/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:05:56 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/02 11:53:19 by mazeghou         ###   ########.fr       */
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

class FileNotFoundException: public std::exception
{
virtual const char* what() const throw()
{
    return "File not found.";
}
};

class FileContentWrong: public std::exception
{
virtual const char* what() const throw()
{
    return "File content must have this pattern: date | value.";
}
};

void retrieveData(std::string input);
void processData(std::string line);
void retrieveMyData(std::string filePath, std::function<void (std::string, std::string)> insertData);
template <typename T, typename Y>

class BitcoinExchange
{
    private:
    std::map<T, Y> data;
    BitcoinExchange() {};
    public:
    static void insertData(std::string date, std::string value)
    {
        std::istringstream iss(value);
        Y numericValue;

        if (!(iss >> numericValue)) {
            throw FileContentWrong();
        }
        data.insert(std::make_pair(date, numericValue));
    }
    BitcoinExchange(std::string input) 
    {
        retrieveMyData("data.csv", insertData);
        retrieveData(input); 
    };
    ~BitcoinExchange() {};
};
