#include <iostream>
#include <vector>

using namespace std;

struct Dot {
	int x, y;
	char type;
};

struct Line {
	int a, b, c;
	int f(int x, int y) {
		return a + b * x + c * y;
	}
};

int main(void)
{
	int n, m;
	cin >> n >> m;

	vector<Dot> dots(n);
	for (int i = 0; i < n; i++)
		cin >> dots[i].x >> dots[i].y >> dots[i].type;

	while (m-- > 0) {
		Line line;
		cin >> line.a >> line.b >> line.c;

		char type[2];
		auto end = dots.end();
		auto dot = dots.begin();
		int res = line.f(dot->x, dot->y);
		type[res > 0 ? 1 : 0] = dot->type;
		type[res > 0 ? 0 : 1] = dot->type == 'A' ? 'B' : 'A';

		bool yes = true;
		for (++dot; dot != end; ++dot) {
			int res = line.f(dot->x, dot->y);
			if (type[res > 0 ? 1 : 0] != dot->type) {
				yes = false;
				break;
			}
		}
		cout << (yes ? "Yes" : "No") << endl;
	}

	return 0;
}