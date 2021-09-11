#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Position {
	int x;
	int y;
};

bool cmp(const Position *pos1, const Position *pos2)
{
	if (pos1->x != pos2->x)
		return pos1->x < pos2->x;
	return pos1->y < pos2->y;
}

#define MAXN	1000

int main(void)
{
	int n;
	cin >> n;

	Position pos[MAXN];
	vector<Position *> ppos(n);

	for (int i = 0; i < n; i++) {
		cin >> pos[i].x >> pos[i].y;
		ppos[i] = &pos[i];
	}

	sort(ppos.begin(), ppos.end(), cmp);

	int counts[5] = { 0, 0, 0, 0, 0 };
	for (int i = 1; i < n - 1; i++) {
		Position *p = ppos[i];
		int mark = 0;
		int found = 0;
		
		Position *pp;
		int j;

		for (j = i - 1; j >= 0; j--) {
			pp = ppos[j];
			if (pp->x < p->x - 1)
				break;
			if (pp->x == p->x - 1) {
				if (pp->y == p->y - 1 || pp->y == p->y + 1)
					mark++;
				else if (pp->y == p->y)
					found++;
				else if (pp->y < p->y - 1)
					break;
			}
			else if (pp->x == p->x && pp->y == p->y - 1) {
				found++;
			}
		}
		if (found < 2)
			continue;

		for (j = i + 1; j < n; j++) {
			pp = ppos[j];
			if (pp->x > p->x + 1)
				break;
			if (pp->x == p->x + 1) {
				if (pp->y == p->y - 1 || pp->y == p->y + 1)
					mark++;
				else if (pp->y == p->y)
					found++;
			 	else if (pp->y > p->y + 1)
				 	break;
			}
			else if (pp->x == p->x && pp->y == p->y + 1) {
				found++;
			}
		}
		if (found < 4)
			continue;

		counts[mark]++;
	}

	for (int i = 0; i < 5; i++)
		cout << counts[i] << endl;

	return 0;
}