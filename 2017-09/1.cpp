#include <iostream>

using namespace std;

int main(void)
{
	int N;
	cin >> N;

	int total = 0;
	if (N >= 10 * 5) {
		int count = N / (10 * 5);
		total += count * (5 + 2);
		N -= count * (10 * 5);
	}
	if (N >= 10 * 3) {
		int count = N / (10 * 3);
		total += count * (3 + 1);
		N -= count * (10 * 3);
	}
	total += N / 10;

	cout << total << endl;

	return 0;
}