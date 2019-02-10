#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <cstdlib>

struct statistics 
{
	std::string word;
	size_t number;

	statistics () : word(""), number(0) {}
};

//!_______________________
//!function prepairs word to hash it
//!it makes all letters small and deletes punctuation marks at the end of a word
//!_______________________
std::string prepare(const std::string & word);

//!_______________________
//!compares numbers of two statistics structs
//!_______________________
bool predicator_struct_statistics(statistics s1, statistics s2);


std::string prepare(const std::string & word)
{
	std::string result = word;

	std::transform(result.begin(), result.end(), result.begin(), tolower);

	if (((result.back()) == ',') || ((result.back()) == '.') || ((result.back()) == ':')\
		|| ((result.back()) == '-') || ((result.back()) == '\'') || ((result.back()) == ';') || ((result.back()) == '"'))
	{
		result.pop_back();
	}

	return result;
}

bool predicator_struct_statistics(statistics s1, statistics s2)
{
	return s1.number > s2.number;
}

int main()
{
	std::cout << "I can count each word in your text, but I don't know Russian letters, so text must be on English\n";
	std::string filename;
	std::cout << "Please, write name of the file, example: text.txt" << std::endl;
	std::cin >> filename;

	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "File didn't opened" << std::endl;
		std::cout << "May be you mistaced in filename, please check it and run me again\n";
		system("pause");
		exit(0);
	}

	size_t topamount = 0;
	std::cout << "How much the mostly frequent words do you want to see?\n";
	std::cin >> topamount;

	std::string word;
	std::map<std::string, size_t> wordcounter;

	while (!file.eof())
	{
		file >> word;
		word = prepare(word);

		wordcounter[word]++;
	}

	file.close();

	std::vector<statistics> vectorstat;
	statistics structstat;

	for (auto it = wordcounter.begin(); it != wordcounter.end(); ++it)
	{
		structstat.word = it->first;
		structstat.number = it->second;

		vectorstat.push_back(structstat);
	}

	std::sort(vectorstat.begin(), vectorstat.end(), predicator_struct_statistics);

	size_t counter = 0;
	for (auto it = vectorstat.begin(); it != vectorstat.end() && counter < topamount; ++it, counter++)
	{
		std::cout << it->word << "\t|  " << it->number << std::endl;
	}

	system("pause");
	return 0;
}
