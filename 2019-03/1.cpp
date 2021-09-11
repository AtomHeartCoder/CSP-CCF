#include <iostream>
#include <stdio.h>

using namespace std;

int main(void)
{
	int n;
	cin >> n;

	int max, min;
	int mid, mid2;

	for (int i = 1; i <= n; i++) {
		int input;
		cin >> input;

		if (i == 1)
			min = input;
		if (i == n)
			max = input;
		if (n & 1) {	// odd
			if (i == n / 2 + 1)
				mid = mid2 = input;
		}
		else {			// even
			if (i == n / 2)
				mid = input;
			else if (i == n / 2 + 1)
				mid2 = input;
		}
	}

	if (min > max) {
		n = min;
		min = max;
		max = n;
	}

	char const *str[] = {
		"",
		".5"
	};

	printf("%d %d%s %d\n", max, (mid + mid2) / 2, str[(mid + mid2) % 2], min);

	return 0;
}