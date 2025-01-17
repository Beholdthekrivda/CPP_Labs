#include <iostream>
#include <cmath>

int main()
{	
	setlocale(LC_ALL, "RU");

	double func, step, len, x, start, end = 4;

	std::cout << "¬ведите начальное значение (от 0 до 4): ";
	std::cin >> start;

	if (0 < start <= 4)
	{
		len = end - start;
		step = len / 10;
		x = start;

		std::cout << "«начение step: " << step << std::endl;

		while (x <= end)
		{
			func = sin(x) / x;
			x = x + step;
			std::cout << "«начение функции: " << func << std::endl;
		}
	}

	std::cout << " " << std::endl;

	int a = 0, b = 1, c = 0, n = 0, sum = 0;
	double max;

	std::cout << "¬ведите сумму (max): ";
	std::cin >> max;
	
	while (sum < max)
	{
		sum = sum + b;

		std::cout << b << " ";

		c = a + b;
		a = b;
		b = c;

		n = n + 1;
	}

	std::cout << "\n";
	std::cout << n << std::endl;
	std::cout << sum << std::endl;

	return 0;
}