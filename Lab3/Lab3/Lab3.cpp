#include <iostream>
#include <cstring>

using namespace std;

int main()
{   
    setlocale(LC_ALL, "RU");

    int count_word;
    char words[20][11];

    cout << "Введите кол-во слов: ";
    cin >> count_word;

    if (count_word > 20 || count_word < 1)
    {
        cout << "Кол-во слов не более 20 и не менее 1" << endl;
        return 1;
    }

    for (int i = 0; i < count_word; i++)
    {
        cout << "Введите слово: " << endl;
        cin >> words[i];

        if (strlen(words[i]) > 10)
        {
            cout << "Длина слова должна быть меньше 10" << endl;
            return 1;
        }
    }

    for (int i = 0; i < count_word; i++)
    {
        cout << "Слово " << i + 1 << ": " << words[i] << endl;
    }

    return 0;
} 