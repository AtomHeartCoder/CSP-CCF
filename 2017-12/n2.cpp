#include <iostream>

using namespace std;

struct Kid {
	int num;
	Kid *prev;
	Kid *next;
	void init(void) {
		this->prev = this->next = this;
	}
	void join(Kid *afterme) {
		this->prev = afterme;
		this->next = afterme->next;
		afterme->next = afterme->next->prev = this;
	}
	void leave(void) {
		this->prev->next = this->next;
		this->next->prev = this->prev;
	}
};

int main(void)
{
	int n, k;
	cin >> n >> k;

	Kid kids[1000];

	kids[0].num = 1;
	kids[0].init();
	for (int i = 1; i < n; i++) {
		kids[i].num = i + 1;
		kids[i].join(&kids[i - 1]);
	}

	Kid *cur = &kids[0];
	long long number = 1;
	while (n > 1) {
		if (number % k == 0 || number % 10 == k) {
			cur->leave();
			n--;
		}

		number++;
		cur = cur->next;
	}

	cout << cur->num << endl;

	return 0;
}