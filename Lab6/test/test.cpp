#include <iostream>
using namespace std;

int solutions = 0;

void per(int k, int n, int P[], bool R[]) // k - это позиция числа в массиве. Изначально смотрим на первую позицию
{
    if (k == n) // выводим массив с числами если дошли до конца массива
    {
        for (int i = 0; i < n; i++)
        {
            cout << P[i] << " ";
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        if (!R[i]) // если число не занято
        {
            R[i] = true; // прописываем что оно теперь занято
            P[k] = i + 1;  // добавляем число в массив      
            per(k + 1, n, P, R); // просматриваем последующие позиции
            R[i] = false; // обнуляем вхождение числа (бэктрекинг)
        }
    }
}

void Queen(int col, int n, int queens[], bool rows[], bool diag1[], bool diag2[])
{
    if (col == n) {
        solutions++;
        cout << "Решение " << solutions << ": ";
        for (int i = 0; i < n; i++)
            cout << queens[i] + 1 << " ";
        cout << endl;
        return;
    }

    for (int row = 0; row < n; row++) {
        int d1 = row - col + n - 1;
        int d2 = row + col;

        if (!rows[row] && !diag1[d1] && !diag2[d2]) {
            rows[row] = diag1[d1] = diag2[d2] = true;
            queens[col] = row;
            Queen(col + 1, n, queens, rows, diag1, diag2);
            rows[row] = diag1[d1] = diag2[d2] = false; // Откат
        }
    }
}

void lesson1()
{
    int n;
    cout << "Введите n: ";
    cin >> n;

    int* P = new int[n];
    bool* R = new bool[n];

    for (int i = 0; i < n; i++)
    {
        P[i] = 0;
        R[i] = false;
    }

    per(0, n, P, R);
}

void lesson2()
{
    int n;
    cout << "Введите кол-во ферзей: ";
    cin >> n;

    int* queens = new int[n];      // queens[col] = строка (0-based)
    bool* rows = new bool[n];       // Занятые строки
    bool* diag1 = new bool[2 * n - 1];      // Правая диагональ (row - col + n - 1)
    bool* diag2 = new bool[2 * n - 1];      // Левая диагональ (row + col)
    
    for (int i = 0; i < n; i++)
    {
        queens[i] = 0; rows[i] = false;
    }

    for (int i = 0; i < 2 * n - 1; i++)
    {
        diag1[i] = false; diag2[i] = false;
    }

    Queen(0, n, queens, rows, diag1, diag2);
    cout << "Всего решений: " << solutions << endl;
}

int main() 
{
    setlocale(LC_ALL, "RU");

    lesson2();
    cout << endl;
    lesson1();
    
    return 0;
}