#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void matrix(int n, int m, int* v1, int* v2, const string& matrix_file) 
{
    ofstream out(matrix_file);
    out << n << " " << m << endl;

    // Строим матрицу смежноси
    int** M = new int* [n];
    for (int i = 0; i < n; ++i) 
    {
        M[i] = new int[n]();
    }

    for (int k = 0; k < m; ++k) 
    {
        int u = v1[k], v = v2[k];
        M[u][v] = 1;
        M[v][u] = 1;
    }

    // Пишем её в файл
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            out << M[i][j] << " ";
        }
        out << endl;
    }

    out.close();

    // Освобождаем память
    for (int i = 0; i < n; ++i) delete[] M[i];
    delete[] M;
}

void graph(const string& matrix_file, const string& graph_file, int*& L) 
{
    ifstream in(matrix_file);
    int n, m;
    in >> n >> m;  // читаем размер

    // Загружаем матрицу
    int** M = new int* [n];
    for (int i = 0; i < n; ++i) 
    {
        M[i] = new int[n];
        for (int j = 0; j < n; ++j) 
        {
            in >> M[i][j];
        }
    }
    in.close();

    // Степени вершин L[i]
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (M[i][j]) L[i]++; // считаем кол-во смежных вершин для i-ой вершины
        }
    }

    // Выделяем подмассивы neighbours[i][0..L[i]-1]
    int** neighbours = new int* [n];
    for (int i = 0; i < n; ++i) neighbours[i] = new int[L[i]];

    // Заполняем массив
    int* pos = new int[n]();
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            if (M[i][j]) 
            {
                neighbours[i][pos[i]++] = j;
            }
        }
    }

    // Записываем в graph_k.txt
    ofstream out(graph_file);
    out << n << " " << m << endl;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < L[i]; ++j) 
        {
            out << neighbours[i][j] + 1 << " ";
        }
        out << endl;
    }

    out.close();

    // Чистим память
    delete[] pos;
    for (int i = 0; i < n; ++i) 
    {
        delete[] neighbours[i];
        delete[] M[i];
    }
    delete[] neighbours;
    delete[] M;
}

void paths(const string& graph_file, const string& paths_file, int* L)
{
    ifstream in(graph_file);
    ofstream out(paths_file);

    int n, m;
    in >> n >> m;

    for (int i = 0; i < n; ++i) 
    {
        for (int k = 0; k < L[i]; ++k) 
        {
            int v;
            in >> v;            
            if (i < v - 1) 
            {      
                out << i + 1 << " " << v << endl;
            }
        }
    }

    in.close(); out.close();
}

void lesson1()
{
    ifstream file("Graph.txt");

    int n, m, graph_num = 1;
    while (file >> n >> m)
    {
        // читаем рёбра
        int* v1 = new int[m]; // массив левых вершин
        int* v2 = new int[m]; // массив правых вершин
        for (int k = 0; k < m; ++k)
        {
            file >> v1[k] >> v2[k];
            --v1[k]; --v2[k];
        }

        int* L = new int[n](); // массив кол-ва смежных вершин для каждой i-ой вершины

        // имена файлов
        string matrix_file = "C:/Users/Bruh263/Desktop/CPP_Labs/Lab8/Lab8/matrices/matrix_" + to_string(graph_num) + ".txt";
        string graph_file = "C:/Users/Bruh263/Desktop/CPP_Labs/Lab8/Lab8/graphs/graph_" + to_string(graph_num) + ".txt";
        string paths_file = "C:/Users/Bruh263/Desktop/CPP_Labs/Lab8/Lab8/paths/paths_" + to_string(graph_num) + ".txt";

        matrix(n, m, v1, v2, matrix_file);
        graph(matrix_file, graph_file, L);
        paths(graph_file, paths_file, L);

        delete[] v1; delete[] v2;
        ++graph_num;
    }

    file.close();
}

int deep(int v, int n, int** M, int* R, int compId) 
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (M[i][j] == 0) count++;
        }
    }

    if (count == (n * n))
    {
        cout << "Семей: " << n << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "Семья " << i + 1 << ": " << i << endl;
        }
        return 0;
    }

    for (int u = 0; u < n; u++) 
    {
        if (M[v][u] && R[u] == 0) 
        {
            R[u] = compId;
            deep(u, n, M, R, compId);
        }
    }

    return 1;
}

int deep_D(int v, int n, int** M, int* R, int*L, int compId)
{
    for (int u = 0; u < L[v]; u++)
    {
        int q = M[v][u];
        if (R[q] == 0)
        {
            R[q] = compId;
            deep_D(q, n, M, R, L, compId);
        }
    }

    return 1;
}

void lesson2()
{
    ifstream file("gen.txt");

    int a, b, n = 13;

    int** M = new int* [n];
    for (int i = 0; i < n; i++) M[i] = new int[n]();

    while (file >> a >> b)
    {
        if (a == -1 && b == -1)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    cout << M[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;

            int* R = new int[n]();

            int* L = new int[n]();
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    if (M[i][j]) L[i]++; // считаем кол-во смежных вершин для i-ой вершины
                }
            }

            // Выделяем подмассивы neighbours[i][0..L[i]-1]
            int** neighbours = new int* [n];
            for (int i = 0; i < n; ++i) neighbours[i] = new int[L[i]];

            // Заполняем массив
            int* pos = new int[n]();
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    if (M[i][j])
                    {
                        neighbours[i][pos[i]++] = j;
                    }
                }
            }

            int count = 0;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (M[i][j] == 0) count++;
                }
            }

            if (count == (n * n))
            {
                cout << "Семей: " << n << endl;
                for (int i = 0; i < n; i++)
                {
                    cout << "Семья " << i + 1 << ": " << i << endl;
                }
                continue;
            }

            int compCount = 0, result;
            for (int i = 0; i < n; i++) 
            {
                if (R[i] == 0) 
                {
                    ++compCount;
                    R[i] = compCount;
                    result = deep_D(i, n, neighbours, R, L, compCount);
                    if (!result) break;
                }
            }

            if (result)
            {
                int **members = new int*[n];
                for (int i = 0; i < n; i++) members[i] = new int[n]();
                int *sizes = new int[n]();

                for (int i = 0; i < n; i++)
                {
                    int c = R[i];          
                    members[c][sizes[c]++] = i;
                }

                cout << "Семей: " << compCount << endl;
                for (int c = 1; c <= compCount; c++)
                {
                    cout << "Семья " << c << ": ";
                    for (int k = 0; k < sizes[c]; k++)
                    {
                        cout << members[c][k] << ' ';
                    }
                    cout << endl;
                }

                cout << endl;
                for (int i = 0; i < n; i++)
                {
                    R[i] = 0;
                    for (int j = 0; j < n; j++)
                    {
                        M[i][j] = 0;
                    }
                }
                continue;
            }    
        }
        else
        {
            M[a][b] = 1; M[b][a] = 1;
        }
    }

    for (int i = 0; i < n; i++) delete M[i];
    delete[] M;
    file.close();
}

void hamilton(int k, int n, int** M, int* P, int* R, int& count)
{
    int i = P[k - 1];

    if (i == n - 1)
    {
        for (int i = 0; i < k; i++)
            cout << P[i] + 1 << (i + 1 < k ? " -> " : "");
        count++;
        cout << endl;
        return;
    }

    for (int j = 0; j < n; j++)
    {
        if ((R[j] == 0) && M[i][j])
        {
            P[k] = j;
            R[j] = 1;
            hamilton(k + 1, n, M, P, R, count);
            R[j] = 0;
        }
    }
}

void hamilton_D(int k, int n, int** M, int* P, int* R, int* L, int& count)
{
    int i = P[k - 1];

    if (i == n - 1)
    {
        for (int i = 0; i < k; i++)
            cout << P[i] + 1 << (i + 1 < k ? " -> " : "");
        count++;
        cout << endl;
        return;
    }

    for (int j = 0; j < L[i]; j++)
    {
        int q = M[i][j];
        if (R[q] == 0) 
        {
            P[k] = q;
            R[q] = 1;
            hamilton_D(k + 1, n, M, P, R, L, count);
            R[q] = 0;
        }
    }
}

void lesson3()
{
    ifstream file("directed_graph.txt");

    int n, m;
    while (file >> n >> m)
    {
        int** M = new int* [n];
        for (int i = 0; i < n; i++) M[i] = new int[n]();

        int v, u;
        for (int i = 0; i < m; i++)
        {
            file >> v >> u;
            M[v - 1][u - 1] = 1;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << M[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        int* L = new int[n]();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (M[i][j]) L[i]++; // считаем кол-во смежных вершин для i-ой вершины
            }
        }

        // Выделяем подмассивы neighbours[i][0..L[i]-1]
        int** neighbours = new int* [n];
        for (int i = 0; i < n; ++i) neighbours[i] = new int[L[i]];

        // Заполняем массив
        int* pos = new int[n]();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (M[i][j])
                {
                    neighbours[i][pos[i]++] = j;
                }
            }
        }

        int* R = new int[n]();
        int* P = new int[n]();
        P[0] = 0;
        R[0] = 1;
        int count = 0;
        hamilton_D(1, n, neighbours, P, R, L, count);

        cout << "Количество путей: " << count << endl;

        for (int i = 0; i < n; i++) delete M[i];
        delete[] M;
        delete[] P;
        delete[] R;
    }

}

void euler(int** M, int n)
{
    int q = 0;
    for (int i = 0; i < n && (q < 3); i++)
    {
        int s = 0;
        for (int j = 0; j < n; j++)
        {
            if (M[i][j]) s++;
        }
        if (s & 1)
        {
            q++;
        }
    }

    if (q == 0) 
    {
        cout << "Можно нарисовать эту фигуру, начиная и заканчивая рисование в одной и той же точке" << endl;
    }
    else if (q == 2) 
    {
        cout << "Можно нарисовать эту фигуру, начиная и заканчивая рисование в различных точках" << endl;
    }
    else 
    {
        cout << "Не существует" << endl;
    }
}

void euler_D(int*L, int n)
{
    int q = 0;
    for (int i = 0; i < n && (q < 3); i++)
    {
        if (L[i] % 2 != 0)
        {
            q++;
        }
    }

    if (q == 0)
    {
        cout << "Можно нарисовать эту фигуру, начиная и заканчивая рисование в одной и той же точке" << endl;
    }
    else if (q == 2)
    {
        cout << "Можно нарисовать эту фигуру, начиная и заканчивая рисование в различных точках" << endl;
    }
    else
    {
        cout << "Не существует" << endl;
    }
}

void lesson5()
{
    ifstream file("d_g.txt");

    int n, m;
    while (file >> n >> m)
    {
        int** M = new int* [n];
        for (int i = 0; i < n; i++) M[i] = new int[n]();

        int v, u;
        for (int i = 0; i < m; i++)
        {
            file >> v >> u;
            M[v - 1][u - 1] = 1;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << M[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;

        int* L = new int[n]();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (M[i][j]) L[i]++; // считаем кол-во смежных вершин для i-ой вершины
            }
        }

        // Выделяем подмассивы neighbours[i][0..L[i]-1]
        //int** neighbours = new int* [n];
        //for (int i = 0; i < n; ++i) neighbours[i] = new int[L[i]];

        //// Заполняем массив
        //int* pos = new int[n]();
        //for (int i = 0; i < n; ++i)
        //{
        //    for (int j = 0; j < n; ++j)
        //    {
        //        if (M[i][j])
        //        {
        //            neighbours[i][pos[i]++] = j;
        //        }
        //    }
        //}

        euler_D(L, n);

        cout << endl;
    }
}

int main() 
{
    setlocale(LC_ALL, "RU");

    /*cout << "Упражнение 1" << endl;
    lesson1();
    cout << endl;*/
    cout << "Упражнение 2" << endl;
    lesson2();
    cout << endl;
    cout << "Упражнение 3" << endl;
    lesson3();
    cout << endl;
    cout << "Упражнение 5" << endl;
    lesson5();

    return 0;
}
