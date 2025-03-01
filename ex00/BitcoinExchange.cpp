/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:06:01 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/01 20:01:56 by mazeghou         ###   ########.fr       */
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
        if (line.find("|") == std::string::npos)
        {
            throw FileContentWrong();
        }
    }
}