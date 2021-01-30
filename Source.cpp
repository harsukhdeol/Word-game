#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <random>
#include <cctype>


bool wordCheck(const std::vector<std::string>& list,const std::string& input)
{
	for (auto& word : list)
	{
		if (input == word)
		{
			return true;
		}
	}
	return false;
}

std::vector<std::string> getIntersection(const std::vector<std::string>& list1, const std::vector<std::string>& list2) {
	std::vector<std::string> common_list;

	for (const auto& word : list1) {
		if (wordCheck(list2, word))
		{
			common_list.push_back(word);
		}
	}
	return common_list;

}
std::vector<int> fillBuckets(const std::string& word)
{
	std::vector<int> buckets(26, 0);
	for (char c : word)
	{
		buckets[c - 'a']++;// adds 1 to the correct index according to ascii
	}
	return buckets;
}

int wordScore(std::string& word1, std::string& word2)
{
	const std::vector<int> bucket1 = fillBuckets(word1);
	const std::vector<int> bucket2 = fillBuckets(word2);

		int score = 0;
	for (int i = 0; i <26; i++) {
		score += std::min(bucket1[i], bucket2[i]);// matching letter score
	}
	for (int i = 0; i < 5; i++) {
		if (word1[i] == word2[i])// return true if 
		{
			score++;
		}
	}
	return score;
}




int main()
{
		std::vector<std::string> five_words_list;
	{// make file input a different scope so file autmatically closes
		std::ifstream five_word_file("sgb-words.txt");

		for (std::string line; std::getline(five_word_file, line);) // load all strings in vector
		{
			if (line.empty())
			{
				continue;
			}
			five_words_list.push_back(line);
		}
	}

	std::vector<std::string> common_words_list;
	{// make file input a different scope so file autmatically closes
		std::ifstream common_word_file("wordlist.txt");

		for (std::string line; std::getline(common_word_file, line);) // load all strings in vector
		{
			if (line.empty())
			{
				continue;
			}
			common_words_list.push_back(line);
		}
	}

	common_words_list.resize(2000);
	auto common_list = getIntersection(common_words_list, five_words_list);

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, common_list.size()-1);
	 std::string target = common_list[dist(rng)];
	std::string input;
	while (true)
	{
		std::cout << std::string("Enter a five letter word") << std::endl;
		std::cin >> input;
		for (auto& c : input)
		{
			c = std::tolower(c);
		}
		if (input.size() != 5)
		{
			std::cout << std::string("I said a FIVE letter word dumbass") << std::endl;
		}
		else if (!wordCheck(five_words_list, input))
		{
			std::cout << std::string("That's not a real word fam") << std::endl;
		}
		else
		{
		const int score = wordScore(input, target);
		if (score == 10)
		{
			std::cout << "You did it damn" << std::endl;
			break;
		}
		else {
			std::cout << "Nah that aint it. Score: " << score << std::endl;
		}
	}

	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}