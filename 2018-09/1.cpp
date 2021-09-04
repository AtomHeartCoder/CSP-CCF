#include <iostream>
#include <stdio.h>

using namespace std;

int main(void)
{
	int n;
	short price[1000];

	cin >> n;
	for (int i = 0; i < n; i++) {
		short input;
		cin >> input;
		price[i] = input;
	}

	printf("%hd ", (price[0] + price[1]) / 2);

	for (int i = 1; i < n - 1; i++) {
		int next = price[i - 1] + price[i] + price[i + 1];
		printf("%hd ", next / 3);
	}

	printf("%hd", (price[n - 2] + price[n - 1]) / 2);

	return 0;
}