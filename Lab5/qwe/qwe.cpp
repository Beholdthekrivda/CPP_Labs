#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

void main()
{
	setlocale(LC_ALL, "RU");

	ifstream file("test.txt");
	ofstream file_important("result_important.txt");
	ofstream file_longest("result_longest.txt");
	
	string line;
	while (getline(file, line))
	{
		int pos = 0, found;
		vector<string> words{};

		while ((found = line.find(' ', pos)) != std::string::npos) {
			words.push_back(line.substr(pos, found - pos));
			pos = found + 1;
		}
		words.push_back(line.substr(pos));

		for (auto it = words.cbegin(); it != words.end(); it++)
		{
			cout << *it << " ";
		}

		vector<string> prefix{};
		unordered_map<string, int> prefix_count;

		int prefix_index = 0, word_index = 0, result;
		while (prefix_index < words.size())
		{
			if (word_index == words.size())
			{
				word_index = 0;
				prefix_index += 1;
				continue;
			}

			if (word_index == prefix_index)
			{
				word_index += 1;
				continue;
			}

			if (words[prefix_index].size() <= words[word_index].size())
			{
				result = words[word_index].compare(0, words[prefix_index].size(), words[prefix_index]);
				if (result == 0)
				{
					prefix.push_back(words[prefix_index]);
					prefix_count[words[prefix_index]] += 1;
				}
			}

			word_index += 1;
		}

		if (prefix.empty())
		{
			cout << endl;
			cout << "NO";
			file_important << "NO" << endl;
			file_longest << "NO" << endl;
			return;
		}

		int max = prefix[0].size();
		string max_word;
		for (int i = 0; i < prefix.size(); i++)
		{
			if (max <= prefix[i].size())
			{
				max = prefix[i].size();
				max_word = prefix[i];
			}
		}

		cout << endl;
		int max_important = 0; string important_word; string longest_word;
		for (auto it = prefix_count.begin(); it != prefix_count.end(); it++)
		{
			if (it->second > max_important)
			{
				max_important = it->second;
				important_word = it->first;
			}
			if (it->first.size() > longest_word.size())
			{
				longest_word = it->first;
			}
			cout << "Ключ: " << it->first << " Значение: " << it->second << " ";
		}

		file_longest << longest_word << " ";

		for (int i = 0; i < words.size(); i++)
		{
			if (words[i].size() > longest_word.size() && words[i].compare(0, longest_word.size(), longest_word) == 0)
			{
				file_longest << words[i] << " ";
			}
		}
		file_longest << endl;

		file_important << important_word << " " << max_important << endl;
		cout << endl;
		cout << endl;
	}
	file_longest.close();
	file_important.close();
	file.close();
}
	