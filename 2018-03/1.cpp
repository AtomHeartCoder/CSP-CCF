#include <iostream>

using namespace std;

int main(void)
{
	int bonus = 0;
	int score = 0;

	for (;;) {
		int move;
		cin >> move;
		
		if (move == 1) {
			bonus = 0;
			score++;
		}
		else if (move == 2) {
			bonus += 2;
			score += bonus;
		}
		else
			break;
	}
	cout << score << endl;
	return 0;
}
