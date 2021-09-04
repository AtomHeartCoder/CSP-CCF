#include <iostream>

using namespace std;

int main(void)
{
	int r, y, g;
	int n;

	cin >> r >> y >> g;
	cin >> n;

	int cost = 0;

	while (n --> 0) {
		int k, t;
		cin >> k >> t;
		switch (k) {
		case 0:
		case 1:
			cost += t;
			break;
		case 2:
			cost += t + r;
			break;
		}
	}

	cout << cost << endl;

	return 0;
}