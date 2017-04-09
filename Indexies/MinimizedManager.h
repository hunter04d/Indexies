#pragma once
#include <vector>
#include <algorithm>

class MinimizedManager
{
	
	std::string core;
	std::vector<std::string> other_sets;
	std::vector<std::string> other_sets_sorted;
	const size_t num_of_vars;
public:
	MinimizedManager(const std::vector<std::string>& _otherSets, const std::string& _core) : core(_core), other_sets(_otherSets), other_sets_sorted(other_sets), num_of_vars(std::count(core.cbegin(),core.cend(), 'v'))
	{
		std::sort(other_sets_sorted.begin(),other_sets_sorted.end(), [](const auto& set1, const auto& set2)
		{
			return std::count(set1.cbegin(), set1.cend(), '-') < std::count(set2.cbegin(), set2.cend(), '-');
		});
	}

	std::vector<std::string> GetAll()
	{
		std::vector<std::string> out;
		for (const auto& set: other_sets)
		{
			out.push_back(core + set);
		}
		return out;
	}
	void PCNFnize()
	{
		
	}
	

};

inline std::vector<std::string> Namefy(std::string _in)
{
	std::vector<std::string> out(2);
	char name = 'a';
	for (auto& ch : _in)
	{
		if (ch == 'v')
		{
			name = 'a';
			out[0] += "   ";
			out[1] += " v ";
			continue;
		}
		if (ch == '1')
		{
			out[0].push_back(' ');
			out[1].push_back(name);
			++name;
		}
		else if (ch == '0')
		{
			out[0].push_back('_');
			out[1].push_back(name);
			++name;
		}

		else if (ch == '-')
		{
			++name;
		}
		else if (ch == '('|| ch == ')')
		{
			out[0].push_back(' ');
		}
	}
	return out;
}