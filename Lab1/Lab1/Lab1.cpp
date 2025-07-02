#include <iostream>

using namespace std;

void lesson1();
void lesson2();

int main()
{
	setlocale(LC_ALL, "RU");

	lesson1();
	cout << endl;
	lesson2();

	return 0;
}

void lesson1()
{
	cout << "Упражнение 1" << endl;

	double func, step, x, start, end = 4;

	cout << "Введите начальное значение (от 0 до 4): ";
	cin >> start;

	if (0 < start <= 4)
	{
		step = (end - start) / 9;
		x = start;

		cout << "Значение step: " << step << endl;

		while (x <= end)
		{
			func = sin(x) / x;
			x += step;
			cout << "Значение функции: " << func << endl;
		}
	}
}

void lesson2()
{
	cout << "Упражнение 2" << endl;

	int a = 0, b = 1, next = 0, n = 0, sum = 0;
	double max;

	cout << "Введите сумму (max): ";
	cin >> max;

	while (true)
	{
		sum = sum + b;

		if (sum > max)
		{
			sum -= b;
			break;
		}

		cout << b << " ";

		next = a + b;
		a = b;
		b = next;

		n += 1;
	}

	cout << "\n";
	cout << "Кол-во элементов: " << n << endl;
	cout << "Сумма: " << sum << endl;
}