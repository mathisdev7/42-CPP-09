/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:40:57 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/05 12:03:02 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>
#include <cctype>

class RPN
{
private:
	std::stack<int> stack;

public:
	RPN(std::string expression);
	~RPN();
	bool isRPN(const std::string &expression);
	int evaluateRPN(const std::string &expression);
};
