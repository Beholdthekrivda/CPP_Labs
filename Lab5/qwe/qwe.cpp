#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

void lesson1()
{
	cout << "Введите слово, а затем число" << endl;
	int num; char word[10];
	scanf("%s", word);
	scanf("%d", &num);

	printf("%s", word);
	printf("%d", num);

	FILE* file = fopen("data.txt", "w");
	fprintf(file, "%s %d", word, num);
	fclose(file);

	file = fopen("data.txt", "r");

	int num1; char word1[10];
	fscanf(file, "%s %d", word1, &num1);
	cout << endl;

	if (feof(file))
	{
		cout << "Достигнут конец файла" << endl;
	}

	fclose(file);

	{
		char arr[] = { 10, 20, 30, 40, 50 };
		ofstream file("data.bin", ios::binary);
		if (file) 
		{
			file.write(arr, sizeof(arr));
		}
	}

	{
		char arr[5];
		ifstream file("data.bin", ios::binary);
		if (file) 
		{
			file.read(arr, sizeof(arr));
			for (int i = 0; i < size(arr); i++)
			{
				cout << static_cast<int>(arr[i]) << " ";
			}
		}
	}

	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "RU");

	lesson1();

	ifstream file("test.txt");
	ofstream file_important("result_important.txt");
	ofstream file_longest("result_longest.txt");
	
	string line;
	while (getline(file, line))
	{
		int pos = 0, found;
		vector<string> words{};

		while ((found = line.find(' ', pos)) != string::npos) {
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
			if (words[i].size() >= longest_word.size() && words[i].compare(0, longest_word.size(), longest_word) == 0)
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
	