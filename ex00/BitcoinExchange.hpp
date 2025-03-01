/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:05:56 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/01 20:01:18 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <exception>
#include <cstring>
#include <map>
#include <string>

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
template <typename T, typename Y>

class BitcoinExchange
{
    private:
    std::map<T, Y> data;
    BitcoinExchange() {};
    public:
    BitcoinExchange(std::string input) 
    {
        retrieveData(input); 
    };
    ~BitcoinExchange() {};
};
