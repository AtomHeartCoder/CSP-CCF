#include <iostream>

using namespace std;

int main(void)
{
	int n, k;
	cin >> n >> k;

	int total = 0;
	int count = 0;
	for (int i = 0; i < n; i++) {
		int cur = 0;
		cin >> cur;
		total += cur;
		if (total >= k) {
			total = 0;
			count++;
		}
	}
	if (total > 0)
		count++;

	cout << count << endl;
	return 0;
}
