#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Node { int data; Node* next; };

int main()
{
	setlocale(LC_ALL, "RU");

	cout << "Упражнение 3" << endl;

	const int n = 10;

	//вариант 1

	int nums1[n];

	for (size_t i = 0; i < n; i++)
	{
		nums1[i] = i * i;
	}

	for (size_t i = 0; i < n; i++)
	{
		cout << nums1[i] << " ";
	}

	cout << endl;

	//вариант 2

	int nums2[n];
	int* ptr = nums2;

	for (int i = 0; i < n; i++)
	{
		*(ptr + i) = i * i;
	}

	for (int i = 0; i < n; i++)
	{
		cout << *(ptr + i) << " ";
	}

	cout << endl;

	//вариант 3 

	int* nums3 = new int[n];

	for (int i = 0; i < n; i++)
	{
		nums3[i] = i * i;
	}

	for (int i = 0; i < n; i++)
	{
		cout << nums3[i] << " ";
	}

	cout << endl;

	//вариант 4

	int* nums4 = new int[n];

	for (int i = 0; i < n; i++)
	{
		*(nums4 + i) = i * i;
	}

	for (int i = 0; i < n; i++)
	{
		cout << *(nums4 + i) << " ";
	}

	cout << endl;

	cout << "Упражнение 4" << endl;

	Node* head, * temp, * help_temp;

	head = new struct Node;
	temp = head;
	for (int i = 0; i < n; i++)
	{
		temp->data = i;

		if (i < n - 1)
		{
			help_temp = new struct Node;
			temp->next = help_temp;
			temp = help_temp;
		}
	}
	temp->next = NULL;

	temp = head;
	while (temp != NULL)
	{
		cout << temp->data << " ";
		temp = temp->next;
	}

	return 0;
}