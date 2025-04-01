#include <iostream>
#include <fstream>

using namespace std;

double eps = 0.000001;

void singlesolution(int n, int m, double** matrix, double*& X)
{
    for (int i = min(n - 1, m - 1); i >= 0; i--)
    {
        X[i] = matrix[i][n]; // тк здесь уже должа была получиться матрица ступенчатого вида, то мы берем последний эл-т
        for (int j = i + 1; j < n; j++) // в этом цикле происходит корректировка
        {
            X[i] -= matrix[i][j] * X[j]; // а если быть точнее то, j - это предыдщий полученный эл-т
            // и мы его учитываем для нахождения следующего неизвестного
            // пример: в матрице 3 * 4 мы нашли x3, а что бы найти x2 мы должны использовать x3, т.к. уравнение будет иметь вид 0*x1 + c1*x2 + c2*x3 = b
            // или x2 = (b - c2*x3) / c1
            // в нашем случае c2 = matrix[i][j], x3 = X[j]
        }
        X[i] /= matrix[i][i]; // соответсвено c1 = matrix[i][i]
    }
}

int triangulation(int n, int m, double**& matrix)
{
    int swapcount = 0;

    if (m == 0 || n == 0) return swapcount;

    for (int i = 0; i < min(m, n) - 1; i++)
    {
        double max = abs(matrix[i][i]); // к в случае с нахождением маскимального эл-та берем за макс самое первое число
        int maxpos = i; // тоже самое с позицией максимального

        for (int k = i + 1; k < m; k++)
        {
            double el = abs(matrix[k][i]); // выбираем из стобца k максимальное значение
            if (el > max)
            {
                max = el;
                maxpos = k;
            }
        }

        if (abs(matrix[maxpos][i]) <= eps) // если максимальный элемент в столбце близок к нулю, то говорим что матрциа вырожденная
        {
            cout << "Вырожденная матрица" << endl;
            return 0;
        }

        if (i != maxpos) // если ведущий (максимальный) эл-т не в текущей строке, то меняем строки местами
        {
            double* z = matrix[i]; matrix[i] = matrix[maxpos]; matrix[maxpos] = z;
            swapcount++;
        }

        for (int j = i + 1; j < m; j++) // обрабатываем строки ниже i-ой строки
        {
            double mul = matrix[j][i] / matrix[i][i]; // определяем во сколько раз эл-т matrix[j][i] больше или меньше ведущего эл-та
            // это нужно чтобы занулить эл-ты
            for (int k = i; k < n + 1; k++) // для строки j (которая ниже строки i) обнуляем эл-ты 
            {
                matrix[j][k] -= matrix[i][k] * mul;
            }
        }
    }

    int last = min(m, n) - 1;
    if (abs(matrix[last][last]) < eps)
    {
        cout << "Вырожденная матрица" << endl;
        return 0;
    }

    return swapcount;
}

void main()
{
	setlocale(LC_ALL, "RU");

	ifstream file("test.txt");

	int m, n;

	while (file >> m >> n)
	{
        double** matrix = new double* [m];
        for (int i = 0; i < m; i++) 
        {
            matrix[i] = new double[n + 1];
        }

        for (int i = 0; i < m; i++) 
        {
            for (int j = 0; j < n + 1; j++) 
            {
                file >> matrix[i][j];
            }
        }

		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n + 1; j++)
			{
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
        cout << endl;

        double* x = new double[n];

        for (int i = 0; i < n; i++)
        {
            x[i] = 0;
        }

        int result = triangulation(n, m, matrix);

        if (result)
        {
            singlesolution(n, m, matrix, x);

            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n + 1; j++)
                {
                    cout << matrix[i][j] << " ";
                }
                cout << endl;
            }
            
            for (int i = 0; i < n; i++)
            {
                cout << x[i] << " ";
            }
            cout << endl;
        }
        cout << endl;

        for (int i = 0; i < m; i++) 
        {
            delete[] matrix[i];
        }
        delete[] matrix;
	}

    file.close();
}