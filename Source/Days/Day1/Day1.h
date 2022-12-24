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
		int count = 0;
		return std::to_string(count);
	}

	virtual std::string part2(std::string filename, std::vector<std::string> args) override
	{
		int count = 0;
		return std::to_string(count);
	}
};