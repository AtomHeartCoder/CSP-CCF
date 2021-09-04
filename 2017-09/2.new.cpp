#include <iostream>
#include <queue>
#include <stdio.h>

using namespace std;

enum Type {
	RETURN, BORROW,
};

struct Event {
	int key;
	int time;
	Type type;
	bool operator>(const Event &event) const {
		if (time != event.time)
			return time > event.time;
		if (type != event.type)
			return type > event.type;
		return key > event.key;
	}
};

int main(void)
{
	int N, K;
	cin >> N >> K;

	vector<int> sheet(N);
	vector<int> index(N + 1);
	priority_queue<Event, vector<Event>, greater<Event>> events;
	
	for (int i = 0; i < N; i++) {
		sheet[i] = i + 1;
		index[i + 1] = i;
	}

	while (K-- > 0) {
		int key, start, length;
		Event b, r;
		cin >> key >> start >> length;

		b.key = r.key = key;
		b.time = start;
		b.type = BORROW;
		r.time = start + length;
		r.type = RETURN;

		events.push(b);
		events.push(r);
	}

	int empty = N;
	while (!events.empty()) {
		Event event = events.top();
		events.pop();
		
		if (event.type == BORROW) {
			if (index[event.key] < empty)
				empty = index[event.key];
			sheet[index[event.key]] = 0;
		}
		else {
			sheet[empty] = event.key;
			index[event.key] = empty;
			while (empty < N) {
				if (sheet[empty] == 0)
					break;
				empty++;
			}
		}
	}

	for (int i = 0; i < N; i++)
		cout << sheet[i] << ' ';
	cout << endl;

	return 0;
}