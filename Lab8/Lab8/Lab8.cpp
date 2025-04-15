#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void matrix(int n, int m, const int* v1, const int* v2, const string& matrix_file) 
{
    ofstream out(matrix_file);
    out << n << endl;

    // Строим временную матрицу
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
    int n;
    in >> n;  // читаем размер

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

    // Считаем количество рёбер m (неориентированный граф)
    int m = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (M[i][j]) ++m;
        }
    }
    
    // Степени вершин L[i]
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (M[i][j]) L[i]++;
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

    // Записываем упорядоченный список в graph_k.txt
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

int main() 
{
    setlocale(LC_ALL, "RU");

    ifstream file("Graph.txt");

    int n, m, graph_num = 1;
    while (file >> n >> m) 
    {
        // читаем рёбра
        int* v1 = new int[m];
        int* v2 = new int[m];
        for (int k = 0; k < m; ++k) 
        {
            file >> v1[k] >> v2[k];
            --v1[k]; --v2[k];
        }

        int* L = new int[n]();

        // имена файлов
        string matrix_file = "matrix_" + to_string(graph_num) + ".txt";
        string graph_file = "graph_" + to_string(graph_num) + ".txt";
        string paths_file = "paths_" + to_string(graph_num) + ".txt";

        matrix(n, m, v1, v2, matrix_file);
        graph(matrix_file, graph_file, L);
        paths(graph_file, paths_file, L);

        delete[] v1; delete[] v2;
        ++graph_num;
    }

    file.close();
    return 0;
}
