#include <iostream>

using namespace std;

int main(void)
{
	int n;
	cin >> n;

	int ht[2000][2];
	int wt[2000][2];

	for (int i = 0; i < n; i++) {
		cin >> ht[i][0];
		cin >> ht[i][1];
	}
	for (int i = 0; i < n; i++) {
		cin >> wt[i][0];
		cin >> wt[i][1];
	}

	int sum, h, w;
	sum = h = w = 0;
	while (h < n && w < n) {
		if (ht[h][1] <= wt[w][0]) {
			h++;
		} else if (ht[h][0] >= wt[w][1]) {
			w++;
		} else {
			int s, t;
			s = ht[h][0] > wt[w][0] ? ht[h][0] : wt[w][0];
			if (ht[h][1] < wt[w][1]) {
				t = ht[h][1];
				h++;
			} else {
				t = wt[w][1];
				w++;
			}
			sum += t - s;
		}
	}

	cout << sum << endl;

	return 0;
}