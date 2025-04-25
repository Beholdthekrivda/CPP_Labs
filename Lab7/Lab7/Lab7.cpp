#include <iostream>
#include <fstream>
using namespace std;

double eps = 0.000001;

int general_solution(int n, int m, double** A, double*& X)
{
    int* L = new int[n];
    for (int i = 0; i < n; i++) L[i] = i;

    int i = 0, r;
    if (n < m) r = n;
    else r = m;

    while (i < r)
    {
        int v = i, u = i;
        for (int j = i; j < m; j++)
        {
            for (int k = i; k < n; k++)
            {
                if (abs(A[j][k]) > abs(A[v][u]))
                {
                    v = j;
                    u = k;
                }
            }
        }

        if (abs(A[v][u]) < eps) r = i;
        else
        {
            if (v != i)
            {
                double* z = A[i];
                A[i] = A[v];
                A[v] = z;
            }

            if (u != i)
            {
                for (int k = 0; k < m; k++)
                {
                    double z = A[k][i];
                    A[k][i] = A[k][u];
                    A[k][u] = z;
                }

                int p = L[i];
                L[i] = L[u];
                L[u] = p;
            }

            double c = A[i][i];
            for (int j = i; j <= n; j++) A[i][j] /= c;

            for (int k = 0; k < m; k++)
            {
                if (k != i)
                {
                    c = A[k][i];
                    for (int j = i; j <= n; j++) A[k][j] -= c * A[i][j];
                }
            }

            i++;
        }
    }

    i = r;
    // проверяем на наличие строки вида 0 0 0 0 ... 0 | b, b != 0
    while (i < m && abs(A[i][n]) < eps) i++;
    if (i < m)
    {
        return 0;
    }
    else if (r == n)
    {
        for (int j = 0; j < n; j++) X[L[j]] = A[j][n];
        return 1;
    }
    else
    {
        for (int k = r; k < n; k++)
        {
            cout << "Введите значение для x" << L[k] + 1 << ": ";
            cin >> X[L[k]];
        }
        cout << endl;

        // 2) Обратная подстановка для ведущих переменных
        for (int j = 0; j < r; j++)
        {
            X[L[j]] = A[j][n];
            for (int k = r; k < n; k++) X[L[j]] -= A[j][k] * X[L[k]];
        }
    }

    return 1;
}

void lesson3()
{
    ifstream file("test1.txt");

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

        int* perm = new int[n];
        for (int i = 0; i < n; i++)
        {
            perm[i] = i;
        }

        int result = general_solution(n, m, matrix, x);

        if (result)
        {
            for (int i = 0; i < n; i++)
            {
                cout << "x" << i + 1 << "=" << x[i] << " ";
            }
            cout << endl;
        }
        cout << endl;

        for (int i = 0; i < m; i++)
            delete[] matrix[i];
        delete[] matrix;
        delete[] x;
    }

    file.close();
}

void singlesolution(int n, int m, double** matrix, double*& x, int* perm)
{
    double* y = new double[n]; // создаем новый массив для значений неизвестных в марице с переставленными столбцами
    for (int i = min(n, m) - 1; i >= 0; i--)
    {
        y[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++)
        {
            y[i] -= matrix[i][j] * y[j];
        }
        y[i] /= matrix[i][i];
    }

    // присваиваем значения массиву x с учетом перестановок
    for (int i = 0; i < n; i++)
    {
        x[perm[i]] = y[i];
    }
    delete[] y;
}

int triangulation(int n, int m, double**& matrix, int* perm)
{
    int swapcount = 0;

    if (m == 0 || n == 0) return swapcount;

    for (int i = 0; i < min(m, n) - 1; i++) // метод поиска макс эл-та на всей площади матрицы, кроме последнего столбца
    {
        double maxVal = fabs(matrix[i][i]); // как в случае с нахождением маскимального эл-та берем за макс самое первое число
        int maxRow = i, maxCol = i; // также делаем для столбца и строки
        for (int r = i; r < m; r++)
        {
            for (int c = i; c < n; c++)
            {
                double val = fabs(matrix[r][c]);
                // здесь находим индекс столбца и строки максимального эл-та
                if (val > maxVal)
                {
                    maxVal = val;
                    maxRow = r;
                    maxCol = c;
                }
            }
        }

        if (maxVal < eps) // если максимальный элемент близок к нулю, то говорим что матрциа вырожденная
        {
            cout << "Вырожденная матрица" << endl;
            return 0;
        }

        if (maxRow != i) // если макс эл-т находится не в i-ой строке, то меняем местами строки i и maxrow
        {
            double* temp = matrix[i];
            matrix[i] = matrix[maxRow];
            matrix[maxRow] = temp;
            swapcount++;
        }

        if (maxCol != i) // если макс эл-т находится не в i-ом столбце, то меняем местами i и maxcol
        {
            for (int r = 0; r < m; r++)
            {
                double temp = matrix[r][i];
                matrix[r][i] = matrix[r][maxCol];
                matrix[r][maxCol] = temp;
            }
            // замена строк происходит без последствий, но замена столбцов ведет к изменению порядка записи переменных в системе
            // поэтому чтобы в дальнейшем сохранить порядок вводим массив, в котором будем отслеживать перестановки столбцов 
            int tempPerm = perm[i];
            perm[i] = perm[maxCol];
            perm[maxCol] = tempPerm;
            swapcount++;
        }

        for (int j = i + 1; j < m; j++)
        {
            double mul = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n + 1; k++)
            {
                matrix[j][k] -= matrix[i][k] * mul;
            }
        }
    }

    int last = min(m, n) - 1;
    if (fabs(matrix[last][last]) < eps)
    {
        cout << "Вырожденная матрица" << endl;
        return 0;
    }

    return swapcount;
}

void lesson1_2()
{
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

        int* perm = new int[n];
        for (int i = 0; i < n; i++)
        {
            perm[i] = i;
        }

        int result = triangulation(n, m, matrix, perm);

        if (result)
        {
            singlesolution(n, m, matrix, x, perm);

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
                cout << "x" << i + 1 << "=" << x[i] << " ";
            }
            cout << endl;
        }
        cout << endl;

        for (int i = 0; i < m; i++)
            delete[] matrix[i];
        delete[] matrix;
        delete[] x;
        delete[] perm;
    }

    file.close();
}

int main()
{
    setlocale(LC_ALL, "RU");
    lesson1_2();
    lesson3();
    return 0;
}
