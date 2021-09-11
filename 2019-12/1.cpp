#include <iostream>

using namespace std;

struct Player {
	int jmpcnt;
	Player *next;
};

static bool jump(int num)
{
	if (num % 7 == 0)
		return true;

	while (num != 0) {
		if (num % 10 == 7)
			return true;
		num /= 10;
	}

	return false;
}

int main(void)
{
	Player players[4] = {
		{0, &players[1]},
		{0, &players[2]},
		{0, &players[3]},
		{0, &players[0]},
	};

	int n;
	cin >> n;

	Player *cur = &players[0];
	int num = 1;

	while (n > 0) {
		if (jump(num++))
			cur->jmpcnt++;
		else
			n--;
		cur = cur->next;
	}

	for (cur = players; cur < players + 4; cur++)
		cout << cur->jmpcnt << endl;

	return 0;
}