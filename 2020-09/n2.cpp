#include <iostream>

using namespace std;

struct Zone {
	int x_l;
	int y_d;
	int x_r;
	int y_u;
	bool inRange(int x, int y) {
		return x >= x_l && x <= x_r &&
			   y >= y_d && y <= y_u;
	}
};

int main(void)
{
	int n, k, t;
	Zone zone;
	cin >> n >> k >> t;
	cin >> zone.x_l >> zone.y_d >> zone.x_r >> zone.y_u;

	int pass = 0;
	int remain = 0;
	while (n-- > 0)
	{
		int consecutive = 0;
		bool p = false;
		bool r = false;
		for (int i = 0; i < t; i++) {
			int x, y;
			cin >> x >> y;
			if (zone.inRange(x, y)) {
				p = true;
				if (++consecutive >= k)
					r = true;
			} else {
				consecutive = 0;
			}
		}
		if (p)
			pass++;
		if (r)
			remain++;
	}

	cout << pass << endl;
	cout << remain << endl;

	return 0;
}