#include <iostream>
#include <time.h>
using namespace std;

const int len_nums = 18;

void create(int count, int arr[])
{
	for (int i = 0; i < count; i++)
	{
		arr[i] = rand() % 18;
	}
}

void package(int count, int nums[], int arr[])
{
	for (int i = 0; i < count; i++)
	{
		arr[nums[i]] += 1;
	}
}

void unpacking(int arr[])
{
	for (int i = 0; i < len_nums; i++)
	{
		for (int j = 0; j < arr[i]; j++)
		{
			cout << i << " ";
		}
	}
}

void main()
{
	setlocale(LC_ALL, "RU");

	srand(time(NULL));

	int n;

	cout << "Введите кол-во эл-ов: ";
	cin >> n;

	int* arr_with_nums = new int[n], * arr_with_count_nums = new int[len_nums];
	int& ptr = n;

	for (int i = 0; i < len_nums; i++)
	{
		arr_with_count_nums[i] = 0;
	}

	create(ptr, arr_with_nums);
	package(n, arr_with_nums, arr_with_count_nums);
	unpacking(arr_with_count_nums);
}