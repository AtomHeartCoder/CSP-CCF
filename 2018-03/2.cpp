#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

bool cmpByPos(pair<char, short>& p1, pair<char, short>& p2) {
	return p1.second < p2.second;
}

bool cmpByIndex(pair<char, short>& p1, pair<char, short>& p2) {
	return p1.first < p2.first;
}

int main(void)
{
	int n, L, t;
	cin >> n >> L >> t;

	pair<char, short> ball[100 + 2];
	char drct[100 + 2];
	for (int i = 1; i <= n; i++) {
		short pos;
		cin >> pos;
		drct[i] = 1;
		ball[i].first = i;
		ball[i].second = pos;
	}
	sort(&ball[1], &ball[n + 1], cmpByPos);

	ball[0].second = ball[n + 1].second = -1;

	while (t-- > 0) {
		// make moves
		for (int i = 1; i <= n; i++)
			ball[i].second += drct[i];

		// bump
		if (ball[1].second == 0)
			drct[1] = 1;

		for (int i = 1; i <= n; i++) {
			if (ball[i].second == ball[i + drct[i]].second) {
				drct[i] *= -1;
			}
		}

		if (ball[n].second == L)
			drct[n] = -1;
	}

	sort(&ball[1], &ball[n + 1], cmpByIndex);
	for (int i = 1; i <= n; i++) {
		cout << ball[i].second << ' ';
	}
	cout << endl;
	return 0;
}