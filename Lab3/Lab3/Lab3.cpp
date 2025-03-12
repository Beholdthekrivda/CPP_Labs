#include <iostream>

using namespace std;

void lesson1()
{
    char word1[] = "Hello world", word2[] = "alone", word3[] = "alon", cop[20];

    cout << strlen(word1) << endl;

    strcpy(cop, word1);
    cout << cop << endl;

    int result = strcmp(word2, word3);
    cout << result << endl;
    if (result == 0)
    {
        cout << "Слова одинаковые" << endl;
    }
    else
    {
        cout << "Слова неодинаковые" << endl;
    }
}

int main()
{   
    setlocale(LC_ALL, "RU");

    lesson1();

    int count_word;
    char words[20][11];

    cout << "Enter the number of words: ";
    cin >> count_word;

    if (count_word > 20 || count_word < 1)
    {
        cout << "The number of words should be no more than 20 and no less than 1" << endl;
        return 1;
    }

    for (int i = 0; i < count_word; i++)
    {
        cout << "Enter the word: " << endl;
        cin >> words[i];
        
        if (strlen(words[i]) > 10)
        {
            cout << "Length of word should be less or equal 10" << endl;
            return 1;
        }
    }

    for (int i = 1; i < count_word; i+=2)
    {
        cout << "word " << i + 1 << ": " << words[i] << endl;
    }

    return 0;
} 