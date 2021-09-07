#include <iostream>

using namespace std;

int main(void)
{
	int n;
	cin >> n;

	int count = 0;
	int prev, curr;
	cin >> prev;
	
	enum { INIT, ASC, DESC } state = INIT;

	while (--n > 0) {
		cin >> curr;
		if (curr > prev && state == DESC) {
			count++;
			state = ASC;
		} else if (curr < prev && state == ASC) {
			count++;
			state = DESC;
		} else if (state == INIT) {
			state = curr > prev ? ASC : DESC;
		}
		prev = curr;
	}

	cout << count << endl;

	return 0;
}