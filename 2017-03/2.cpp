#include <iostream>
#include <map>
#include <list>
#include <iterator>

using namespace std;

int main(void)
{
	int n;
	cin >> n;

	list<int> line;
	map<int, list<int>::iterator> smap;

	for (int i = 1; i <= n; i++) {
		line.push_back(i);
		auto it = prev(line.end());
		smap[i] = it;
	}

	int m;
	cin >> m;

	while (m-- > 0) {
		int p, q;
		cin >> p >> q;
		if (q == 0)
			continue;

		auto it = smap[p];
		auto it2 = it;
		advance(it2, q);

		line.erase(it);
		if (q > 0)
			it2++;
		smap[p] = line.insert(it2, p);
			
	}

	for (auto it = line.begin(); it != line.end(); it++)
		cout << *it << ' ';
	cout << endl;

	return 0;
}