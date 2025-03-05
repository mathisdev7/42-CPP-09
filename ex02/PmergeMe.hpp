/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:38:22 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/05 17:54:06 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <exception>

class PmergeMe
{
private:
	std::vector<int> vec;
	std::deque<int> deq;
	void mergeInsertionSortVector(std::vector<int> &arr);
	void mergeInsertionSortDeque(std::deque<int> &arr);

public:
	PmergeMe(int argc, char **argv);
	~PmergeMe();
	void parseInput(int argc, char **argv);
	void execute();
};
