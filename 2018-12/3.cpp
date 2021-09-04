#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

struct Prefix {
	unsigned ip;
	int len;
	bool operator < (Prefix &p) const {
		return ip == p.ip ? len < p.len : ip < p.ip;
	}
};

void parsePrefix(char *raw, Prefix &prefix)
{
	char *p = raw;
	bool gotlen = false;
	unsigned ip = 0;
	int part = 4;
	for (;;) {
		if (*p == '.' || *p == 0) {
			if (*p == 0)
				p = nullptr;
			else
				*p = 0;
			ip = (ip << 8) | (unsigned char)atoi(raw);
			raw = p + 1;
			part--;
			if (p == nullptr)
				break;
		} else if (*p == '/') {
			prefix.len = atoi(p + 1);
			gotlen = true;
		}
		p++;
	}

	if (part > 0) {
		ip <<= part * 8;
	}
	if (!gotlen) {
		prefix.len = 8 * (4 - part);
	}
	prefix.ip = ip;
}

void printPrefix(Prefix &prefix)
{
	int ip = prefix.ip;
	unsigned char *p = (unsigned char *)&ip;
	printf("%u.%u.%u.%u/%d\n", p[3], p[2], p[1], p[0], prefix.len);
}

int main(void)
{
	int n;
	cin >> n;
	cin.ignore(32, '\n');

	char input[32];
	vector<Prefix> prefixes(n);

	for (int i = 0; i < n; i++) {
		cin.getline(input, 32);
		parsePrefix(input, prefixes[i]);
	}

	sort(prefixes.begin(), prefixes.end());

	list<Prefix *> plist;
	for (int i = 0; i < n; i++)
		plist.push_back(&prefixes[i]);

	auto it = plist.begin();
	auto it2 = plist.begin();
	it2++;
	while (it2 != plist.end()) {
		Prefix *p1 = *it;
		Prefix *p2 = *it2;
		unsigned mask = ~0ULL << (sizeof(unsigned) * 8 - p1->len);

		if ((p1->ip & mask) == (p2->ip & mask)) {
			it2 = plist.erase(it2);
		} else {
			it = it2++;
		}
	}

	it = it2 = plist.begin();
	it2++;
	while (it2 != plist.end()) {
		Prefix *p1 = *it;
		Prefix *p2 = *it2;

		bool flag = false;
		if (p1->len == p2->len) {
			unsigned mask = ~0ULL << (sizeof(unsigned) * 8 - p1->len + 1);

			if ((p1->ip & mask) == (p2->ip & mask)) {
				it2 = plist.erase(it2);
				p1->ip &= mask;
				p1->len--;
				flag = true;

				if (it != plist.begin()) {
					it2 = it--;
				}
			}
		}
		
		if (!flag) {
			it = it2++;
		}
	}

	for (auto it = plist.begin(); it != plist.end(); it++)
		printPrefix(**it);

	return 0;
}