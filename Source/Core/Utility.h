#pragma once

#include "Core/Core.h"

// Parameter enum

enum class EStringSplitType: uint8_t
{
	EmptyLine
};

// std::lib shorthand

template<class T>
static T Sum(const std::vector<T>& array, T init = T())
{
	auto fiter = array.begin();
	auto liter = array.end();
	for (; fiter != liter; ++fiter)
	{
		init = std::move(init) + *fiter;
	}
	return init;
}

template<class T>
static T SumFirst(const std::vector<T>& array, size_t n, T init = T())
{
	auto fiter = array.begin();
	auto liter = array.begin() + n;
	for (; fiter != liter; ++fiter)
	{
		init = std::move(init) + *fiter;
	}
	return init;
}

template<class T>
static void SortAscending(std::vector<T>& out_array)
{
	auto fiter = out_array.begin();
	auto liter = out_array.end();
	sort(fiter, liter,
		[](T lhs, T rhs)
		{
			return lhs > rhs;
		});
}

template<class T>
static void SortDescending(std::vector<T>& out_array)
{
	auto fiter = out_array.begin();
	auto liter = out_array.end();
	sort(fiter, liter,
		[](T lhs, T rhs)
		{
			return lhs < rhs;
		});
}

// Type conversion

static int StringToInt(const std::string& string)
{
	return strtol(string.c_str(), NULL, 10);
}

// String & File operations

static std::vector<std::string> SplitLineToStrings(const std::string& input, char delimiter, char quote_char, char comment_char)
{
#ifdef DEBUG_RUNNER
	std::cout << "original input is [" << input << "]" << std::endl;
#endif

	std::vector<std::string> splits;
	char* pos = (char*)input.c_str();

	if (comment_char && *pos == comment_char)
	{
#ifdef DEBUG_RUNNER
		std::cout << "Comment line found" << std::endl;
#endif
		return splits;
	}

	bool in_quote = false;
	std::ostringstream current;
	while (*pos != '\0')
	{
		if (quote_char && in_quote)
		{
			if (*pos == quote_char)
			{
				in_quote = false;
#ifdef DEBUG_RUNNER
				std::cout << "Leaving quotes" << std::endl;
#endif
			}
			else
			{
				current << (*pos);
			}
			}
		else
		{
			if (quote_char && *pos == quote_char)
			{
				in_quote = true;
#ifdef DEBUG_RUNNER
				std::cout << "In quotes" << std::endl;
#endif
			}
			else if (*pos == delimiter)
			{
				// ABCDE,ABCDE,ABCDE
				// first string goes from 0 to 4...construct as string(0,5). pos will be 5 for the comma. so 5-0=5
				// second string goes from 6 to 10...construct as string(6,5)...pos wil be 11 for the comma. so 11-6=5
				// third string goes from 12 to 16...construct as string(12,5) but need to do this out of loop as its the last string
#ifdef DEBUG_RUNNER
				std::cout << "appending [" << current.str() << "] as a string" << std::endl;
#endif
				splits.push_back(current.str());
				current = std::ostringstream();
			}
			else
			{
				current << (*pos);
		}
		}
		pos++;
	}

	// append the last string. pos will be pointed to the null terminator at 17, so string(12,5) would be pos(17)-start(12)
#ifdef DEBUG_RUNNER
	std::cout << "appending [" << current.str() << "] as the last string" << std::endl;
#endif
	splits.push_back(current.str());

	return splits;
}

static std::vector<int> SplitLineToInts(const std::string& input, char delimiter, char quote_char, char comment_char)
{
#ifdef DEBUG_RUNNER
	std::cout << "original input is [" << input << "]" << std::endl;
#endif

	std::vector<int> splits;
	char* pos = (char*)input.c_str();

	if (comment_char && *pos == comment_char)
	{
#ifdef DEBUG_RUNNER
		std::cout << "Comment line found" << std::endl;
#endif
		return splits;
	}

	bool in_quote = false;
	std::ostringstream current;
	while (*pos != '\0')
	{
		if (quote_char && in_quote)
		{
			if (*pos == quote_char)
			{
				in_quote = false;
#ifdef DEBUG_RUNNER
				std::cout << "Leaving quotes" << std::endl;
#endif
			}
			else
			{
				current << (*pos);
			}
			}
		else
		{
			if (quote_char && *pos == quote_char)
			{
				in_quote = true;
#ifdef DEBUG_RUNNER
				std::cout << "In quotes" << std::endl;
#endif
			}
			else if (*pos == delimiter)
			{
				// ABCDE,ABCDE,ABCDE
				// first string goes from 0 to 4...construct as string(0,5). pos will be 5 for the comma. so 5-0=5
				// second string goes from 6 to 10...construct as string(6,5)...pos wil be 11 for the comma. so 11-6=5
				// third string goes from 12 to 16...construct as string(12,5) but need to do this out of loop as its the last string
#ifdef DEBUG_RUNNER
				std::cout << "appending [" << current.str() << "] as a string" << std::endl;
#endif
				splits.push_back(StringToInt(current.str()));
				current = std::ostringstream();
			}
			else
			{
				current << (*pos);
		}
		}
		pos++;
	}

	// append the last string. pos will be pointed to the null terminator at 17, so string(12,5) would be pos(17)-start(12)
#ifdef DEBUG_RUNNER
	std::cout << "appending [" << current.str() << "] as the last string" << std::endl;
#endif

	splits.push_back(StringToInt(current.str()));

	return splits;
}

static std::vector<std::vector<int>> SplitLinesToIntArrays(const std::vector<std::string>& input_lines, EStringSplitType split_type, std::string delimiter)
{
#ifdef DEBUG_RUNNER
	std::cout << "original input is [" << input_lines << "]" << std::endl;
#endif

	std::vector<std::vector<int>> result;
	std::vector<int> split;

	for (const std::string& line : input_lines)
	{
		if (split_type == EStringSplitType::EmptyLine && line.empty())
		{
			result.push_back(split);
			split.clear();
		}
		else
		{
			split.push_back(StringToInt(line));
		}
	}

	if (!split.empty())
	{
		result.push_back(split);
	}

	return result;
}

static bool ReadAsStrings(const std::string& filename, std::vector<std::string>& lines)
{
	std::ifstream infile(filename);
	if (!infile)
	{
		std::cerr << "*****Error opening file " << filename << std::endl;
		return false;
	}

	std::string line;
	while (getline(infile, line))
	{
#ifdef DEBUG_RUNNER
		std::cout << "Read line [" << line << "] from file" << std::endl;
#endif
		lines.push_back(line);
	}
	infile.close();

	return true;
}

static bool ReadAsInts(const std::string& filename, std::vector<int>& data)
{
	std::vector<std::string> lines;

	if (!ReadAsStrings(filename, lines))
	{
		std::cerr << "Error reading in the data from " << filename << std::endl;
		return false;
	}

	for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
	{
		data.push_back(StringToInt(*iter));
	}

	return true;
}

static bool ReadAsSplitStrings(const std::string& filename, std::vector<std::vector<std::string>>& split_strings, char delimiter, char quote_char, char comment_char)
{
	std::vector<std::string> lines;
	if (!ReadAsStrings(filename, lines))
	{
		return false;
	}

	for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
	{
		std::vector<std::string> results = SplitLineToStrings(*iter, delimiter, quote_char, comment_char);
		if (results.size() > 0)
		{
			split_strings.push_back(results);
		}
	}

	return true;
}

static bool ReadAsSplitInts(const std::string& filename, std::vector<std::vector<int>>& data, char delimiter, char quote_char, char comment_char)
{
	std::vector<std::string> lines;
	if (!ReadAsStrings(filename, lines))
	{
		std::cerr << "Error reading in the data from " << filename << std::endl;
		return false;
	}

	for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
	{
		std::vector<int> results = SplitLineToInts(*iter, delimiter, quote_char, comment_char);
		if (results.size() > 0)
		{
			data.push_back(results);
		}
	}

	return true;
}

static bool ReadLinesAsIntArray(const std::string& filename, std::vector<std::vector<int>>& data, EStringSplitType split_type = EStringSplitType::EmptyLine, std::string delimiter = "")
{
	std::vector<std::string> lines;
	if (!ReadAsStrings(filename, lines))
	{
		std::cerr << "Error reading in the data from " << filename << std::endl;
		return false;
	}

	std::vector<std::vector<int>> results = SplitLinesToIntArrays(lines, split_type, delimiter);
	if (results.size() > 0)
	{
		data = results;
	}

	return true;
}

static bool ReadAsSplitLongs(const std::string& filename, std::vector<std::vector<long>>& split_longs, char delimiter, char quote_char, char comment_char)
{
	std::vector<std::string> lines;
	if (!ReadAsStrings(filename, lines))
	{
		return false;
	}

	for (std::vector<std::string>::iterator iter = lines.begin(); iter != lines.end(); ++iter)
	{
		std::vector<std::string> long_strings = SplitLineToStrings(*iter, delimiter, quote_char, comment_char);
		std::vector<long> longs;

		for (std::vector<std::string>::iterator str_long_iter = long_strings.begin(); str_long_iter != long_strings.end(); ++str_long_iter)
		{
			std::string str_long = *str_long_iter;
			longs.push_back(strtol(str_long.c_str(), NULL, 10));
		}

		split_longs.push_back(longs);
	}

	return true;
}