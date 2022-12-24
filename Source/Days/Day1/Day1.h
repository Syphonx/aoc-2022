#pragma once

#include "Days/Day.h"

class Day1
	: public AocDay
{
public:
	Day1()
		: AocDay(1)
	{
	}

	virtual std::string part1(std::string filename, std::vector<std::string> args) override
	{
		std::vector<int> elves;
		ReadAsInts(filename, elves);

		int max = 0;
		int total = 0;

		for (const int line : elves)
		{
			total += line;
			if (line == 0)
			{
				max = std::max(max, total);
				elves.push_back(total);
				total = 0;
			}
		}

		return std::to_string(max);
	}

	virtual std::string part2(std::string filename, std::vector<std::string> args) override
	{
		int count = 0;
		return std::to_string(count);
	}
};