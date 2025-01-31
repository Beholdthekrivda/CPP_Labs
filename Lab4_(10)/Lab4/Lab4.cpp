#include <iostream>
#include <time.h>
#include <stdio.h>
using namespace std;

void create(int count, char arr[])
{
	for (int i = 0; i < count; i++)
	{
		arr[i] = rand() % 18;
	}
}

void unpacked(int count, char arr[])
{
	for (int i = 0; i < count; i++)
	{
		printf("%d", arr[i]);
		printf(" ");
	}
}
// ЗАДАЧА СКОРЕЕ ВСЕГО СДЕЛАНА НЕ ПРАВИЛЬНО
// но пусть будет как черновик
void main()
{
	setlocale(LC_ALL, "RU");

	srand(time(NULL));

	int n;

	cout << "Введите кол-во эл-ов: ";
	cin >> n;

	char* nums = new char[n]; int& ptr = n;

	create(ptr, nums);
	unpacked(ptr, nums);
}