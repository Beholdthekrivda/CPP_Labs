#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

void main()
{
	setlocale(LC_ALL, "RU");

	/*ifstream file("test.txt");
	
	string line, word;
	while (getline(file, line))
	{
		
	}*/

	vector<string> words{ "t7h", "g8ur", "g8urg8ury", "t7hd3wg8ure", "t7hkl" };
	vector<string> prefix {};
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
		cout << "NO" << endl;
		return;
	}

	int max = prefix[0].size();
	string max_word;
	for (int i = 0; i < prefix.size(); i++)
	{
		cout << prefix[i] << " ";
		if (max <= prefix[i].size())
		{
			max = prefix[i].size();
			max_word = prefix[i];
		}
	}

	cout << endl;
	cout << max_word << " " << max;

	cout << endl;
	for (auto it = prefix_count.begin(); it != prefix_count.end(); it++)
	{
		cout << "Ключ: " << it->first << " Значение: " << it->second << " ";
	}
}
	