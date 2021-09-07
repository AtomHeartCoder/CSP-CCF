#include <iostream>
#include <cstring>

using namespace std;

#define ROWS	20
#define SEATS	5

int main(void)
{
	char seats[ROWS];
	memset(seats, 0, sizeof(seats));

	int n;
	cin >> n;

	while (n-- > 0) {
		int p;
		cin >> p;

		bool found = false;
		for (int r = 0; !found && r < ROWS; r++) {
			unsigned char mask = ~(~0 << p);
			for (int i = 1; i <= SEATS - p + 1; i++) {
				if ((seats[r] & mask) == 0) {
					seats[r] |= mask;
					while (p-- > 0) {
						cout << r * 5 + i << ' ';
						i++;
					}
					cout << endl;
					found = true;
					break;
				}
				mask <<= 1;
			}
		}
		if (found)
			continue;
		for (int r = 0; r < ROWS && p > 0; r++) {
			for (int i = 0; i < SEATS && p > 0; i++) {
				unsigned char mask = 1 << i;
				if ((seats[r] & mask) == 0) {
					seats[r] |= mask;
					cout << r * 5 + i + 1 << ' ';
					p--;
				}
			}
		}
		cout << endl;
	}

	return 0;
}
