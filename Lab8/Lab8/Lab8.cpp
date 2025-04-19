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

        int* R = new int[n]();
        int* P = new int[n]();
        P[0] = 0;
        R[0] = 1;
        int count = 0;
        hamilton(1, n, M, P, R, count);

        cout << "Количество путей: " << count << endl;

        for (int i = 0; i < n; i++) delete M[i];
        delete[] M;
        delete[] P;
        delete[] R;
    }

}

int main() 
{
    setlocale(LC_ALL, "RU");

    cout << "Упражнение 3" << endl;
    lesson3();

    return 0;
}
