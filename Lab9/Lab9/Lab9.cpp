#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printBinary(char n) 
{
    for (int i = 7; i >= 0; i--) 
    {
        cout << ((n >> i) & 1);
    }
    cout << endl;
}

unsigned char rotl8(unsigned char n, int pos) 
{
    if (pos < 0) pos = -pos;
    pos %= 8; 
    return (n << pos) | (n >> (8 - pos));
}

unsigned char rotr8(unsigned char n, int pos) 
{
    if (pos < 0) pos = -pos;
    pos %= 8;
    return (n >> pos) | (n << (8 - pos));
}

void encryption(unsigned char& n, int pos)
{
    if (pos < 0)
    {
        n = rotl8(n, pos);
    }
    else
    {
        n = rotr8(n, pos);
    }
}

void decryption(unsigned char& n, int pos)
{
    if (pos < 0)
    {
        n = rotr8(n, pos);
    }
    else
    {
        n = rotl8(n, pos);
    }
}

int main()
{
    setlocale(LC_ALL, "RU");

    ifstream file("test.txt");
    ofstream out("encryp.txt");
    string line;
    getline(file, line);
    
    int shift;
    cout << "Введите размер сдвига: "; cin >> shift;

    for (unsigned char i : line)
    {
        encryption(i, shift);
        out << i;
    }

    file.close();
    out.close();

    ifstream file1("encryp.txt");
    ofstream out1("decryp.txt");
    getline(file1, line);

    for (unsigned char i : line)
    {
        decryption(i, shift);
        out1 << i;
    }
}
