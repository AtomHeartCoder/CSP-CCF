#include <iostream>

using namespace std;

int main(void)
{
	int n;
	cin >> n;

	short prev;
	cin >> prev;

	short max = 0;
	while (--n > 0) {
		short curr;
		cin >> curr;
		short diff = curr > prev ? curr - prev : prev - curr;
		if (diff > max)
			max = diff;
		prev = curr;
	}

	cout << max << endl;

	return 0;
}