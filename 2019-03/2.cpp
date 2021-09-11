#include <iostream>

using namespace std;

int main(void)
{
	int n;
	cin >> n;
	cin.ignore(100, '\n');

	char input[16];
	while (n-- > 0) {
		cin.getline(input, sizeof(input));

		char num[4] = {
			(char)(input[0] - '0'),
			(char)(input[2] - '0'),
			(char)(input[4] - '0'),
			(char)(input[6] - '0')
		};
		char op[3] = {
			input[1],
			input[3],
			input[5]
		};

		char split = '/';	// '+', '-' < split < 'x', '/'
		int res = num[0];
		int i = 0;
		while (i < 3) {
			if (op[i] < split) {
				// for +- we need to peek the next op
				if (i == 2 || op[i + 1] < split) {	// last op, or the next is also +-
					if (op[i] == '+')
						res += num[i + 1];
					else
						res -= num[i + 1];
				} else {	// do the next op first, and shift away
					if (op[i + 1] == 'x')
						num[i + 2] = num[i + 1] * num[i + 2];
					else
						num[i + 2] = num[i + 1] / num[i + 2];
					op[i + 1] = op[i];
				}
			}
			else {			// cal in order with x/
				if (op[i] == 'x')
					res *= num[i + 1];
				else
					res /= num[i + 1];
			}
			i++;
		}

		cout << (res == 24 ? "Yes" : "No") << endl;
	}

	return 0;
}