#include <iostream>
#include <cmath>

using namespace std;

int main()
{	
	setlocale(LC_ALL, "RU");

	cout << "”пражнение 1" << endl;

	double func, step, len, x, start, end = 4;

	cout << "¬ведите начальное значение (от 0 до 4): ";
	cin >> start;

	if (0 < start <= 4)
	{
		len = end - start;
		step = len / 10;
		x = start;

		cout << "«начение step: " << step << endl;

		while (x <= end)
		{
			func = sin(x) / x;
			x = x + step;
			cout << "«начение функции: " << func << endl;
		}
	}

	cout << " " << endl;
	cout << "”пражнение 2" << endl;

	int a = 0, b = 1, c = 0, n = 0, sum = 0;
	double max;

	cout << "¬ведите сумму (max): ";
	cin >> max;
	
	while (sum < max)
	{
		sum = sum + b;

		cout << b << " ";

		c = a + b;
		a = b;
		b = c;

		n = n + 1;
	}

	cout << "\n";
	cout << n << endl;
	cout << sum << endl;

	return 0;
}