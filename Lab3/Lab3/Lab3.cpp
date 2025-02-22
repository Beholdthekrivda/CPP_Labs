#include <iostream>
#include <cstring>

using namespace std;

int main()
{   
    //setlocale(LC_ALL, "RU");

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