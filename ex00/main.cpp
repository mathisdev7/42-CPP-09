/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:42:51 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/03 15:50:46 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
	(void)argc;
	std::string fileName = argv[1];
	try
	{
		BitcoinExchange btc(fileName);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
}
