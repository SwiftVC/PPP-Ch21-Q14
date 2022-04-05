/*
*	Author:	CS
*	Date:	2022_03_21	YYYY_MM_DD
*
*	Ch21 Q13's output file is used for the following queries:
*	- count user-defined string in passage
*	- output word(s) with the largest count
*	- output word(s) with the most characters
*	- output word(s) with the least characters
*	- output word(s) starting with the user-defined character sequence
*	- output word(s) with the user-defined number of characters
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

void word_count_query(std::vector<std::string>& vect);	//count user - defined string in passage
void word_with_largest_count(std::vector<std::string>& vect); // output word(s) with the largest count
void longest_word(std::vector<std::string>& vect); // output word(s) with the most characters
void shortest_word(std::vector<std::string>& vect); // output word(s) with the least characters
void match_word_start(std::vector<std::string>& vect, std::string start); // output word(s) starting with the user-defined character sequence
void return_words_with_i_count(std::vector<std::string>& vect, int i);	// output word(s) with the user-defined number of characters

int main() {
	std::vector<std::string> vect;
	std::ifstream in{ "output.txt" };
	while (in)
	{
		std::string temp;
		in >> temp;
		if (in)
			vect.push_back(temp);
	}

	while (true)
	{	
		word_count_query(vect);
		word_with_largest_count(vect);
		longest_word(vect);
		shortest_word(vect);

		// Enter string for all words starting with
		std::string start;
		std::cout << "Enter the start of the words you want returned:" << std::endl;
		std::cin >> start;
		match_word_start(vect, start);

		// Enter number of letters to match
		std::cout << "Enter the number of characters for words to match:" << std::endl;
		int i{ 1 };
		std::cin >> i;
		return_words_with_i_count(vect, i);

		std::cin.clear();
	}		

	return 0;
}

void word_count_query(std::vector<std::string>& vect) {
	std::cout << "Enter a word:" << std::endl;
	std::string query;
	std::cin >> query;
	int count{ 0 };
	for (int i = 0; i < vect.size(); i++)
		if (vect[i] == query)
			++count;
	std::cout << query << " appeared " << count;
	if (count == 1)
		std::cout << " time." << std::endl;
	else
		std::cout << " times." << std::endl;
}
void word_with_largest_count(std::vector<std::string>& vect) {
	std::map<std::string, int> words;

	for (int i = 0; i < vect.size(); i++)
		++words[vect[i]];
	int most_common{ 0 };

	for (auto temp : words)
		if (temp.second > most_common)
			most_common = temp.second;
	
	std::vector<std::string> most_common_words;
	for (auto temp : words)
		if (temp.second == most_common)
			most_common_words.push_back(temp.first);

	std::cout << "Most common word(s):\n";
	for (int i = 0; i < most_common_words.size(); i++)
		std::cout << most_common_words[i] << '\t';
	std::cout << std::endl;
}

void longest_word(std::vector<std::string>& vect) {
	int longest{ 0 };
	for (int i = 0; i < vect.size(); i++)
		if (vect[i].size() > longest)
			longest = vect[i].size();

	std::vector<std::string> longest_words;
	for (auto temp : vect)
		if (temp.size() == longest)
			longest_words.push_back(temp);

	std::cout << "The longest word(s):" << std::endl;
	for (int i = 0; i < longest_words.size(); i++)
		std::cout << longest_words[i] << '\t';
	std::cout << std::endl;
}

void shortest_word(std::vector<std::string>& vect) {
	int shortest = vect[0].size();
	for (int i = 0; i < vect.size(); i++)
		if (vect[i].size() < shortest && vect[i].size() > 0)
			shortest = vect[i].size();

	std::vector<std::string> shortest_words;
	for (auto temp : vect)
		if (temp.size() == shortest)
			shortest_words.push_back(temp);

	std::sort(shortest_words.begin(), shortest_words.end());
	shortest_words.erase(std::unique(shortest_words.begin(), shortest_words.end()), shortest_words.end());

	std::cout << "The shortest word(s):" << std::endl;
	for (int i = 0; i < shortest_words.size(); i++)
		std::cout << shortest_words[i] << '\t';
	std::cout << std::endl;
}

void match_word_start(std::vector<std::string>& vect, std::string start) {
	std::vector<std::string> matching_words;

	for (int i = 0; i < vect.size(); i++)
	{
		bool match{ false };
		if (start.size() <= vect[i].size()) {
			match = true;
			for (int j = 0; j < start.size(); j++) {
				if (start[j] != vect[i][j])
					match = false;
			}
		}
		if (match)
			matching_words.push_back(vect[i]);
	}

	std::sort(matching_words.begin(), matching_words.end());
	matching_words.erase(std::unique(matching_words.begin(), matching_words.end()), matching_words.end());

	std::cout << "The words starting with " << start << ":" << std::endl;
	for (int i = 0; i < matching_words.size(); i++)
		std::cout << matching_words[i] << '\t';
	std::cout << std::endl;

	return;
}

void return_words_with_i_count(std::vector<std::string>& vect, int i) {
	std::vector<std::string> matching_words;
	for (auto temp : vect)
		if (temp.size() == i)
			matching_words.push_back(temp);

	std::sort(matching_words.begin(), matching_words.end());
	matching_words.erase(std::unique(matching_words.begin(), matching_words.end()), matching_words.end());

	std::cout << "The words with "<< i << " characters:" << std::endl;
	for (int i = 0; i < matching_words.size(); i++)
		std::cout << matching_words[i] << '\t';
	std::cout << std::endl;
}