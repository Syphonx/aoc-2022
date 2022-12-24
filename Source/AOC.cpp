#include <iostream>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <stack>
#include <deque>
#include <stdlib.h>

#include "Days/Days.h"

struct Advent
{
	AocDay* day;
	std::string input;
	std::string example;
};

static const Advent s_Advent[] =
{
	{ new Day1(),   "../Input/Day1.txt", "../Input/Day1_Example.txt" },
	{ new Day2(),   "../Input/Day2.txt", "../Input/Day2_Example.txt" },
	{ new Day3(),   "../Input/Day3.txt", "../Input/Day3_Example.txt" },
	{ new Day4(),   "../Input/Day4.txt", "../Input/Day4_Example.txt" },
	{ new Day5(),   "../Input/Day5.txt", "../Input/Day5_Example.txt" },
	{ new Day6(),   "../Input/Day6.txt", "../Input/Day6_Example.txt" },
	{ new Day7(),   "../Input/Day7.txt", "../Input/Day7_Example.txt" },
	{ new Day8(),   "../Input/Day8.txt", "../Input/Day8_Example.txt" },
	{ new Day9(),   "../Input/Day9.txt", "../Input/Day9_Example.txt" },
	{ new Day10(), "../Input/Day10.txt", "../Input/Day10_Example.txt" },
	{ new Day11(), "../Input/Day11.txt", "../Input/Day11_Example.txt" },
	{ new Day12(), "../Input/Day12.txt", "../Input/Day12_Example.txt" },
	{ new Day13(), "../Input/Day13.txt", "../Input/Day13_Example.txt" },
	{ new Day14(), "../Input/Day14.txt", "../Input/Day14_Example.txt" },
	{ new Day15(), "../Input/Day15.txt", "../Input/Day15_Example.txt" },
	{ new Day16(), "../Input/Day16.txt", "../Input/Day16_Example.txt" },
	{ new Day17(), "../Input/Day17.txt", "../Input/Day17_Example.txt" },
	{ new Day18(), "../Input/Day18.txt", "../Input/Day18_Example.txt" },
	{ new Day19(), "../Input/Day19.txt", "../Input/Day19_Example.txt" },
	{ new Day20(), "../Input/Day20.txt", "../Input/Day20_Example.txt" },
	{ new Day21(), "../Input/Day21.txt", "../Input/Day21_Example.txt" },
	{ new Day22(), "../Input/Day22.txt", "../Input/Day22_Example.txt" },
	{ new Day23(), "../Input/Day23.txt", "../Input/Day23_Example.txt" },
	{ new Day24(), "../Input/Day24.txt", "../Input/Day24_Example.txt" },
	{ new Day25(), "../Input/Day25.txt", "../Input/Day25_Example.txt" },
};

struct CommandLine
{
	CommandLine()
		: day(0)
		, part(0)
		, test(0)
		, extra_args()
	{
	}

	bool RunSpecificDay() const
	{
		return day != 0;
	}

	bool RunSpecificPart() const
	{
		return part != 0;
	}

	bool RunWithTestInput() const
	{
		return test != 0;
	}

	int day;
	int part;
	int test;
	std::vector<std::string> extra_args;
};

void usage(std::string prog_name)
{
	std::cerr << "Usage for " << prog_name << std::endl;
	std::cerr << "   Run all: " << prog_name << " -a" << std::endl;
	std::cerr << "   Run one day: " << prog_name << " -d day [extra_args...]" << std::endl;
	std::cerr << "   Run one day/part: " << prog_name << " -d day -p part" << std::endl;
}

double BenchPart(const Advent& advent, const std::string& input, int part)
{
	double totalTime = 0;
	auto now = std::chrono::steady_clock::now();
	std::string result;

	if (part == 1)
	{
		result = advent.day->part1(input, {});
	}
	else if (part == 2)
	{
		result = advent.day->part2(input, {});
	}

	auto elapsed = std::chrono::steady_clock::now() - now;
	printf("Part %d: %s\n", part, result.c_str());
	totalTime += elapsed.count();
	printf("Took: [%lld us]\n", int64_t(elapsed.count() * 1e-3));

	return totalTime;
}

double BenchDay(const Advent& advent, const CommandLine& cmd)
{
	printf("\nRunning solution for Day %d...\n", advent.day->GetDay());

	double totalTime = 0;

	if (cmd.part == 0)
	{
		totalTime += BenchPart(advent, cmd.RunWithTestInput() ? advent.example : advent.input, 1);
		totalTime += BenchPart(advent, cmd.RunWithTestInput() ? advent.example : advent.input, 2);
	}
	else
	{
		if (cmd.part == 1)
		{
			totalTime += BenchPart(advent, cmd.RunWithTestInput() ? advent.example : advent.input, 1);
		}
		else if (cmd.part == 2)
		{
			totalTime += BenchPart(advent, cmd.RunWithTestInput() ? advent.example : advent.input, 2);
		}
	}

	return totalTime;
}

int main(int argc, char* argv[])
{
	CommandLine cmd;
	std::deque<std::string> args;
	for (int i = 1; i < argc; i++)
	{
		args.push_back(argv[i]);
	}

	if (args.size() == 0)
	{
		usage("AoC");
		return 1;
	}

	while (!args.empty())
	{
		std::string arg = args.front();
		args.pop_front();

		if (arg == "-d" || arg == "-p")
		{
			std::string val = args.front();
			args.pop_front();

			if (arg == "-d")
			{
				cmd.day = std::stoi(val);
			}
			else if (arg == "-p")
			{
				cmd.part = std::stoi(val);
			}
		}
		else if (arg == "-a")
		{
			cmd.day = 0;
			cmd.part = 0;
		}
		else if (arg == "-t")
		{
			cmd.test = 1;
		}
	}

	double totalTime = 0;

	if (cmd.RunSpecificDay())
	{
		totalTime += BenchDay(s_Advent[cmd.day - 1], cmd);
	}
	else
	{
		for (const Advent& advent : s_Advent)
		{
			totalTime += BenchDay(advent, cmd);
		}
	}

	printf("\nTotal: %lld us\n", int64_t(totalTime * 1e-3));

	return 0;
}