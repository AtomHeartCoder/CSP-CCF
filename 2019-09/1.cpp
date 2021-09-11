#include <iostream>
// #include <vector>

using namespace std;

int main(void)
{
	int N, M;
	cin >> N >> M;

	int T = 0;
	int k = -1;
	int P = 0;
	for (int n = 1; n <= N; n++) {
		int apples;
		cin >> apples;
		
		int remove = 0;
		for (int i = 0; i < M; i++) {
			int rm;
			cin >> rm;
			remove += rm;
		}

		if (remove < P) {
			P = remove;
			k = n;
		}

		T += apples + remove;
	}

	cout << T << ' ' << k << ' ' << -P << endl;

	return 0;
}