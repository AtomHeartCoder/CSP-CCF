#include <iostream>
#include <stdio.h>

using namespace std;

int main(void)
{
	int r, y, g;
	int n;

	cin >> r >> y >> g;
	cin >> n;

	long long cost = 0;
	int cycle = r + y + g;

	while (n-- > 0) {
		int k, t;
		cin >> k >> t;
		
		if (k == 0) {
			cost += t;
			continue;
		}
		
		switch (k) {
		case 1:
			t = r - t;	
			break;
		case 2:
			t = y - t + r + g;
			break;
		case 3:
			t = g - t + r;
			break;
		}

		t = (t + cost) % cycle;
		if (t < r) {				// red
			k = 1;
			t = r - t;
		} else if (t < r + g) {		// green
			k = 3;
		} else {					// yellow
			k = 2;
			t = cycle - t;
		}
		
		if (k == 1)
			cost += t;
		else if (k == 2)
			cost += t + r;
	}

	cout << cost << endl;

	return 0;
}