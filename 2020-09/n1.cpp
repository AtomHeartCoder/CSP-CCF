#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pos {
	int dis;
	int idx;
};

bool cmp(Pos &p1, Pos &p2)
{
	return p1.dis == p2.dis ? p1.idx < p2.idx : p1.dis < p2.dis;
}

int main(void)
{
	int n, X, Y;
	cin >> n >> X >> Y;

	vector<Pos> pos(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		x -= X;
		y -= Y;
		pos[i].dis = x * x + y * y;
		pos[i].idx = i + 1;
	}

	sort(pos.begin(), pos.end(), cmp);

	cout << pos[0].idx << endl;
	cout << pos[1].idx << endl;
	cout << pos[2].idx << endl;

	return 0;
}