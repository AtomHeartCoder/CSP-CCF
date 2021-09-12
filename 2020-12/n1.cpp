#include <iostream>

using namespace std;

int main(void)
{
	int n;
	cin >> n;

	int y = 0;
	while (n-- > 0) {
		int w, score;
		cin >> w >> score;
		y += w * score;
	}
	if (y < 0)
		y = 0;

	cout << y << endl;

	return 0;
}