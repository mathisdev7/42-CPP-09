/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 11:03:53 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/05 12:19:02 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(std::string expression)
{
	if (!this->isRPN(expression))
	{
		std::cout << "RPN expression is not valid." << std::endl;
		return;
	}

	int result = this->evaluateRPN(expression);
	std::cout << "Result: " << result << std::endl;
}

RPN::~RPN()
{
}

bool RPN::isRPN(const std::string &expression)
{
	std::stack<int> stack;
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (token.length() == 1 && std::isdigit(token[0]) && token[0] >= '0' && token[0] <= '9')
			stack.push(1);
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (stack.size() < 2)
				return false;
			stack.pop();
		}
		else
			return false;
	}
	return stack.size() == 1;
}

int RPN::evaluateRPN(const std::string &expression)
{
	std::stack<int> evalStack;
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (std::isdigit(token[0]) || (token.length() > 1 && token[0] == '-' && std::isdigit(token[1])))
			evalStack.push(atoi(token.c_str()));
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (evalStack.size() < 2)
			{
				std::cerr << "Error: Too few operands for operator " << token << "\n";
				return (0);
			}
			int b = evalStack.top();
			evalStack.pop();
			int a = evalStack.top();
			evalStack.pop();
			int result = 0;

			if (token == "+")
				result = a + b;
			else if (token == "-")
				result = a - b;
			else if (token == "*")
				result = a * b;
			else if (token == "/")
			{
				if (b == 0)
				{
					std::cerr << "Error: Division by zero\n";
					return (0);
				}
				result = a / b;
			}
			evalStack.push(result);
		}
		else
		{
			std::cerr << "Error: Invalid character '" << token << "'\n";
			return (0);
		}
	}
	if (evalStack.size() != 1)
	{
		std::cerr << "Error: RPN expression is not valid.\n";
		return (0);
	}
	return evalStack.top();
}
