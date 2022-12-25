#pragma once

#include "Days/Day.h"

using namespace std;

class Day1
	: public AocDay
{
		const int32_t num_elves = 3;

public:
	Day1()
		: AocDay(1)
	{
	}

	virtual std::string part1(std::string filename, std::vector<std::string> args) override
	{
		vector< vector<int32_t> > elves;
		int32_t largest = 0;

		ReadLinesAsIntArray(filename, elves);

		for (const std::vector<int>& elf : elves)
		{
			largest = max(Sum<int32_t>(elf), largest);
		}

		return to_string(largest);
	}

	virtual std::string part2(std::string filename, std::vector<std::string> args) override
	{
		vector<vector<int32_t>> elves;
		vector<int32_t> running;

		ReadLinesAsIntArray(filename, elves);

		for (const auto& elf : elves)
		{
			running.push_back(Sum<int32_t>(elf));
		}

		SortAscending(running);

		return to_string(SumFirst(running, num_elves));
	}
};