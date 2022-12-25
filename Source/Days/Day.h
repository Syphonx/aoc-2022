#pragma once

#include "Core/Utility.h"

class AocDay
{
public:
	AocDay(int day)
		: day(day)
	{
	}
	virtual ~AocDay() {}

	int GetDay() const { return day; }

	virtual std::string part1(std::string filename, std::vector<std::string> args) { return ""; }
	virtual std::string part2(std::string filename, std::vector<std::string> args) { return ""; }

protected:
	int day;
};

class AocMonth
{
public:
	AocMonth() 
		: days()
	{

	}
	~AocMonth() {}

	void AddDay(int day, AocDay* dayPtr)
	{
		days[day] = dayPtr;
	}

	AocDay* GetDay(int day)
	{
		auto iter = days.find(day);
		if (iter != days.end())
		{
			return ((*iter).second);
		}

		return nullptr;
	}

protected:
	std::unordered_map<int, AocDay*> days;
};