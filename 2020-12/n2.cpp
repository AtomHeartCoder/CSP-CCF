#include <iostream>
#include <map>

using namespace std;

struct Theta {
	int y;
	int res0;
	int res1;
	int right;
	Theta(void) { right = 0; }
	Theta(int yy, int res) {
		y = yy;
		res0 = 0;
		res1 = 0;
		right = 0;
		count(res);
	}
	void count(int res) {
		if (res == 1)
			res1++;
		else
			res0++;
	}
};

int main(void)
{
	int m;
	cin >> m;

	map<int, Theta> stat;
	for (int i = 0; i < m; i++) {
		int y, result;
		cin >> y >> result;
		if (stat.find(y) != stat.end())
			stat[y].count(result);
		else
			stat[y] = Theta(y, result);
	}

	int cnt0 = 0;
	for (auto p = stat.begin(); p != stat.end(); ++p) {
		Theta &t = p->second;
		t.right = cnt0;
		cnt0 += t.res0;
	}
	int cnt1 = 0;
	for (auto p = stat.rbegin(); p != stat.rend(); ++p) {
		Theta &t = p->second;
		cnt1 += t.res1;
		t.right += cnt1;
	}
	int theta = 0;
	int max = 0;
	for (auto p = stat.begin(); p != stat.end(); ++p) {
		if (p->second.right >= max) {
			max = p->second.right;
			theta = p->first;
		}
	}
	cout << theta << endl;
	return 0;
}