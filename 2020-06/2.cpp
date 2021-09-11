#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool cmp(pair<int, int> &p1, pair<int, int> &p2)
{
	return p1.first < p2.first;	
}

int main(void)
{
	int n, m[2];
	cin >> n >> m[0] >> m[1];

	vector<pair<int, int>> vec[2];

	for (int i = 0; i < 2; i++) {
		while (m[i]-- > 0) {
			int idx, val;
			cin >> idx >> val;
			vec[i].push_back(make_pair(idx, val));
		}
		sort(vec[i].begin(), vec[i].end(), cmp);
	}

	long long product = 0;
	auto it0 = vec[0].begin();
	auto it1 = vec[1].begin();
	auto end0 = vec[0].end();
	auto end1 = vec[1].end();
	while (it0 != end0 && it1 != end1) {
		if (it0->first == it1->first) {
			product += (long long)it0->second * it1->second;
			++it0;
			++it1;
		} else if (it0->first < it1->first) {
			++it0;
		} else {
			++it1;
		}
	}

	cout << product << endl;

	return 0;
}