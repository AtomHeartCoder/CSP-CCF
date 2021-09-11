#include <iostream>

using namespace std;

int main(void)
{
	// ios::sync_with_stdio(false);
	// cin.tie(nullptr);

	int N;
	cin >> N;

	int T = 0;
	int D = 0;
	int E = 0;

	int fallState = 0;
	bool fallenMark[4] = { false, false, false, false };
	for (int n = 1; n <= N; n++) {
		int m;
		cin >> m;
		
		int apples = 0;
		bool fallen = false;
		while (m-- > 0) {
			int a;
			cin >> a;
			if (a > 0) {
				if (a < apples)
					fallen = true;
				apples = a;
			}
			else {
				apples += a;
			}
		}

		T += apples;

		if (fallen) {
			if (n <= 2)
				fallenMark[n - 1] = true;
			if (n >= N - 1)
				fallenMark[4 - (N - n) - 1] = true;
			D++;
			fallState++;
			if (fallState >= 3)
				E++;
		} else {
			fallState = 0;
		}
	}

	if (fallenMark[0] && fallenMark[3]) {
		if (fallenMark[1])
			E++;
		if (fallenMark[2])
			E++;
	}

	cout << T << ' ' << D << ' ' << E << endl;

	return 0;
}