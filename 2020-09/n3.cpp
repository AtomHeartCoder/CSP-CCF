#include <iostream>
#include <vector>

using namespace std;

struct Gate {
	vector<int *> in;
	int out;
	int (*func)(vector<int *> &input);
};

int _not(vector<int *> &input) {
	int res = *input[0];
	return res < 0 ? -1 : !res;
}
int _and(vector<int *> &input) {
	for (int *in : input) {
		if (*in == 0)
			return 0;
		if (*in < 0)
			return -1;
	}
	return 1;
}
int _or(vector<int *> &input) {
	for (int *in : input) {
		if (*in == 1)
			return 1;
		if (*in < 0)
			return -1;
	}
	return 0;
}
int _xor(vector<int *> &input) {
	int res = 0;
	for (int *in : input) {
		if (*in < 0)
			return -1;
		res ^= *in;
	}
	return res;
}
int _nand(vector<int *> &input) {
	int res = _and(input);
	return res < 0 ? -1 : !res;
}
int _nor(vector<int *> &input) {
	int res = _or(input);
	return res < 0 ? -1 : !res;
}

void gateinit(Gate &gate, const char *func)
{
	switch (func[0]) {
	case 'A':
		gate.func = _and; break;
	case 'O':
		gate.func = _or; break;
	case 'X':
		gate.func = _xor; break;
	default:
		gate.func = (func[2] == 'T') ? _not :
					(func[2] == 'N') ? _nand : _nor;
	}
}

void run(void)
{
	/* Part 1 */
	int M, N;
	cin >> M >> N;

	vector<Gate> gates(N);
	vector<int> input(M);

	for (int n = 0; n < N; n++) {
		char buf[8];
		int k;
		cin >> buf >> k;
		Gate &gate = gates[n];
		gateinit(gate, buf);
		while (k-- > 0) {
			cin >> buf;
			int idx = atoi(buf + 1) - 1;
			int *in = (buf[0] == 'I') ? &input[idx] : &gates[idx].out;
			gate.in.push_back(in); 
		}
	}

	/* Part 2 */
	int S;
	cin >> S;
	vector<vector<int>> shadows(S, vector<int>(M));
	vector<vector<int>> output(S, vector<int>(N));
	for (int s = 0; s < S; s++)
		for (int m = 0; m < M; m++)
			cin >> shadows[s][m];

	bool loop = false;
	for (int s = 0; s < S; s++) {
		// init
		for (int m = 0; m < M; m++)
			input[m] = shadows[s][m];
		for (int n = 0; n < N; n++)
			gates[n].out = -1;
		// run
		bool done = false;
		while (!done && !loop) {
			done = true;
			loop = true;
			for (Gate &gate : gates) {
				if (gate.out >= 0)
					continue;
				gate.out = gate.func(gate.in);
				if (gate.out < 0)
					done = false;
				else
					loop = false;
			}
		}
		if (!loop) {
			for (int n = 0; n < N; n++)
				output[s][n] = gates[n].out;
		}
	}

	/* output */
	if (loop) {
		cout << "LOOP" << endl;
	}
	for (int s = 0; s < S; s++) {
		int si;
		cin >> si;
		while (si-- > 0) {
			int idx;
			cin >> idx;
			if (!loop) {
				cout << output[s][idx - 1];
				if (si == 0)
					cout << endl;
				else
					cout << ' ';
			}
		}
	}
}

int main(void)
{
	int Q;
	cin >> Q;
	while (Q-- > 0)
		run();
	return 0;
}