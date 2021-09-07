#include <iostream>
#include <vector>

using namespace std;

struct Sidekick {
	int hp;
	int atk;
	Sidekick(int atk, int hp) {
		this->atk = atk;
		this->hp = hp;
	}
};

struct Player {
	int hp;
	vector<Sidekick> sidekicks;
	Player(void) {
		hp = 30;
	}
	void summon(int pos, int atk, int hp) {
		auto it = sidekicks.begin() + (pos - 1);
		sidekicks.insert(it, Sidekick(atk, hp));
	}
};

int main(void)
{
	Player players[2];
	Player *us = &players[0];
	Player *them = &players[1];

	int n;
	cin >> n;
	cin.ignore(100, '\n');

	char input[128];
	while (n-- > 0) {
		cin >> input;
		switch (input[0]) {
			case 's': {
				int pos, atk, hp;
				cin >> pos >> atk >> hp;
				us->summon(pos, atk, hp);
				break;
			}
			case 'a': {
				int atkidx, defidx;
				cin >> atkidx >> defidx;
				auto attacker = us->sidekicks.begin() + (atkidx - 1);

				if (defidx == 0) {
					them->hp -= attacker->atk;
				} else {
					auto defender = them->sidekicks.begin() + (defidx - 1);
					attacker->hp -= defender->atk;
					defender->hp -= attacker->atk;
					if (attacker->hp <= 0)
						us->sidekicks.erase(attacker);
					if (defender->hp <= 0)
						them->sidekicks.erase(defender);
				}
				break;
			}
			case 'e': {
				Player *temp = us;
				us = them;
				them = temp;
				break;
			}
		}
	}

	int res = (players[0].hp > 0) ?
				(players[1].hp > 0 ? 0 : 1) : -1;
	cout << res << endl;

	cout << players[0].hp << endl;
	int size = players[0].sidekicks.size();
	cout << size << ' ';
	for (int i = 0; i < size; i++)
		cout << players[0].sidekicks[i].hp << ' ';
	cout << endl;

	cout << players[1].hp << endl;
	size = players[1].sidekicks.size();
	cout << size << ' ';
	for (int i = 0; i < size; i++)
		cout << players[1].sidekicks[i].hp << ' ';
	cout << endl;

	return 0;
}
