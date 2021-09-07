#include <iostream>

using namespace std;

#define COLUMN	10
#define ROW		15
#define SIZE	4

int main(void)
{
	short board[ROW];
	int i, j;
	for (i = 0; i < ROW; i++) {
		board[i] = 0;
		for (j = 0; j < COLUMN; j++) {
			int input;
			cin >> input;
			board[i] |= input << j;
		}
	}

	short pattern[SIZE];
	for (i = 0; i < SIZE; i++) {
		pattern[i] = 0;
		for (j = 0; j < SIZE; j++) {
			int input;
			cin >> input;
			pattern[i] |= input << j;
		}
	}

	int pos;	
	cin >> pos;
	for (i = 0; i < SIZE; i++)
		pattern[i] <<= (pos - 1);

	int bias;
	for (bias = SIZE; bias > 0; bias--)
		if (pattern[bias - 1] != 0)
			break;
	bias = SIZE - bias;		// empty lines at the bottom of pattern

	for (i = 1; i <= ROW - SIZE + bias; i++) {
		bool collide = false;
		for (j = SIZE - 1; j >= 0; j--) {
			if (i + j >= ROW)
				continue;
			if (pattern[j] & board[i + j]) {
				collide = true;
				break;
			}
		}
		if (collide)
			break;
	}
	i--;

	for (j = 0; j < SIZE; j++)
		if (i + j < ROW)
			board[i + j] |= pattern[j];

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COLUMN; j++) {
			int output = board[i] & (1 << j);
			cout << ((output == 0) ? '0' : '1') << ' ';
		}
		cout << endl;
	}

	return 0;
}