#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <atomic>

const int SIZE = 20;
int arr[SIZE];

std::atomic<int> counter{ 0 };

void countEven()
{
	for (int i = 0; i < SIZE; i++)
	{
		if (arr[i] % 2 == 0)
		{
			counter++;
		}
	}
}

void countNegative()
{
	for (int i = 0; i < SIZE; i++)
	{
		if (arr[i] < 0)
		{
			counter++;
		}
	}
}

int main()
{
	std::srand(std::time(nullptr));

	for (int i = 0; i < SIZE; i++)
	{
		arr[i] = std::rand() % 41 - 20;
	}

	std::cout << "Array: ";

	for (int i = 0; i < SIZE; i++)
	{
		std::cout << arr[i] << " ";
	}

	std::cout << "\n";

	counter = 0;

	std::thread t1(countEven);
	t1.join();

	std::cout << "Even: " << counter << "\n";

	counter = 0;

	std::thread t2(countNegative);
	t2.join();

	std::cout << "Negative: " << counter << "\n";

	return 0;
}