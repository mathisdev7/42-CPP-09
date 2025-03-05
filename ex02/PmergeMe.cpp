/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazeghou <mazeghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:38:20 by mazeghou          #+#    #+#             */
/*   Updated: 2025/03/05 17:54:27 by mazeghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
	parseInput(argc, argv);
}

void PmergeMe::execute()
{
	std::vector<int>::iterator it_vec_begin = vec.begin();
	std::vector<int>::iterator it_vec_end = vec.end();
	std::cout << "Before: " << std::endl;
	while (it_vec_begin != it_vec_end)
	{
		std::cout << *it_vec_begin << " ";
		it_vec_begin++;
	}
	std::cout << std::endl;

	clock_t start_vec = clock();
	mergeInsertionSortVector(vec);
 	clock_t end_vec = clock();
	double elapsed_time_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC * 1000000;

	clock_t start_deq = clock();
	mergeInsertionSortDeque(deq);
	clock_t end_deq = clock();
	double elapsed_time_deq = static_cast<double>(end_deq - start_deq) / CLOCKS_PER_SEC * 1000000;

	it_vec_begin = vec.begin();
	it_vec_end = vec.end();
	std::cout << "After: " << std::endl;
	while (it_vec_begin != it_vec_end)
	{
		std::cout << *it_vec_begin << " ";
		it_vec_begin++;
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << elapsed_time_vec << " us" << std::endl;
	std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << elapsed_time_deq << " us" << std::endl;
}

void PmergeMe::mergeInsertionSortVector(std::vector<int> &vec)
{
	// first step is to make pairs
	size_t n = vec.size();

	// if the number of elements is odd, put the last element alone
	std::vector<std::vector<int> > pairs;

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		// make pairs of 2 elements each
		if (vec[i] > vec[i + 1])
		{
			std::swap(vec[i], vec[i + 1]);
		}
		std::vector<int> pair;
		pair.push_back(vec[i]);
		pair.push_back(vec[i + 1]);
		pairs.push_back(pair);
	}
	if (n % 2 == 1)
	{
		std::vector<int> pair;
		pair.push_back(vec[n - 1]);
		pairs.push_back(pair);
	}

	// second step is to merge pairs into pairs of pairs
	while (pairs.size() > 1)
	{
		std::vector<std::vector<int> > newPairs;

		for (size_t i = 0; i + 1 < pairs.size(); i += 2)
		{
			// merge 2 pairs
			std::vector<int> merged;
			std::vector<int> &pair1 = pairs[i];
			std::vector<int> &pair2 = pairs[i + 1];

			size_t j = 0;
			size_t k = 0;
			// merge pair1 and pair2
			while (j < pair1.size() && k < pair2.size())
			{
				if (pair1[j] < pair2[k])
					merged.push_back(pair1[j++]);
				else
					merged.push_back(pair2[k++]);
			}
			// add remaining elements
			while (j < pair1.size())
				merged.push_back(pair1[j++]);
			while (k < pair2.size())
				merged.push_back(pair2[k++]);
			newPairs.push_back(merged);
		}
		if (pairs.size() % 2 == 1)
			newPairs.push_back(pairs.back());
		pairs = newPairs;
	}
	vec = pairs[0];
}

void PmergeMe::mergeInsertionSortDeque(std::deque<int> &deq)
{
	// first step is to make pairs
	size_t n = deq.size();

	// if the number of elements is odd, put the last element alone
	std::deque<std::deque<int> > pairs;

	for (size_t i = 0; i + 1 < n; i += 2)
	{
		// make pairs of 2 elements each
		if (deq[i] > deq[i + 1])
		{
			std::swap(deq[i], deq[i + 1]);
		}
		std::deque<int> pair;
		pair.push_back(deq[i]);
		pair.push_back(deq[i + 1]);
		pairs.push_back(pair);
	}
	if (n % 2 == 1)
	{
		std::deque<int> pair;
		pair.push_back(deq[n - 1]);
		pairs.push_back(pair);
	}

	// second step is to merge pairs into pairs of pairs
	while (pairs.size() > 1)
	{
		std::deque<std::deque<int> > newPairs;

		for (size_t i = 0; i + 1 < pairs.size(); i += 2)
		{
			// merge 2 pairs
			std::deque<int> merged;
			std::deque<int> &pair1 = pairs[i];
			std::deque<int> &pair2 = pairs[i + 1];

			size_t j = 0;
			size_t k = 0;
			// merge pair1 and pair2
			while (j < pair1.size() && k < pair2.size())
			{
				if (pair1[j] < pair2[k])
					merged.push_back(pair1[j++]);
				else
					merged.push_back(pair2[k++]);
			}
			// add remaining elements
			while (j < pair1.size())
				merged.push_back(pair1[j++]);
			while (k < pair2.size())
				merged.push_back(pair2[k++]);
			newPairs.push_back(merged);
		}
		if (pairs.size() % 2 == 1)
			newPairs.push_back(pairs.back());
		pairs = newPairs;
	}
	deq = pairs[0];
}

void PmergeMe::parseInput(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "No input, only integers are allowed." << std::endl;
		return ;
	}
	int i = 1;
	while (argv[i])
	{
		char *endptr;
		long num = std::strtol(argv[i], &endptr, 10);

		if (*endptr != '\0' || num <= 0)
		{
			std::cerr << "Wrong input, only integers are allowed." << std::endl;
			return ;
		}
		vec.push_back(static_cast<int>(num));
		deq.push_back(static_cast<int>(num));
		i++;
	}
	execute();
}

PmergeMe::~PmergeMe()
{
}
