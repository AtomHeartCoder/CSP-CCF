#include <iostream>

using namespace std;

#define TAX(x, rate)	((x) * (rate) / 100)
#define ATAX(x, rate)	((x) * (100 - (rate)) / 100)
#define BTAX(x, rate)	((x) * 100 / (100 - (rate)))

int main(void)
{
	int aftertax;
	cin >> aftertax;

	int beforetax;
	int exceed;
	if (aftertax <= 3500) {
		beforetax = aftertax;
	}
	else if (aftertax <= 3500 + ATAX(1500, 3)) {
		exceed = aftertax - 3500;
		beforetax = 3500 + BTAX(exceed, 3);
	}
	else if (aftertax <= 3500 + ATAX(1500, 3)
							  + ATAX(4500 - 1500, 10)) {
		exceed = aftertax - 3500 - ATAX(1500, 3);
		beforetax = 3500 + 1500 + BTAX(exceed, 10);
	}
	else if (aftertax <= 3500 + ATAX(1500, 3)
							  + ATAX(4500 - 1500, 10)
							  + ATAX(9000 - 4500, 20)) {
		exceed = aftertax - 3500 - ATAX(1500, 3) - ATAX(4500 - 1500, 10);
		beforetax = 3500 + 4500 + BTAX(exceed, 20);
	}
	else if (aftertax <= 3500 + ATAX(1500, 3)
							  + ATAX(4500 - 1500, 10)
							  + ATAX(9000 - 4500, 20)
							  + ATAX(35000 - 9000, 25)) {
		exceed = aftertax - 3500 - ATAX(1500, 3) - ATAX(4500 - 1500, 10) - ATAX(9000 - 4500, 20);
		beforetax = 3500 + 9000 + BTAX(exceed, 25);
	}
	else if (aftertax <= 3500 + ATAX(1500, 3)
							  + ATAX(4500 - 1500, 10)
							  + ATAX(9000 - 4500, 20)
							  + ATAX(35000 - 9000, 25)
							  + ATAX(55000 - 35000, 30)) {
		exceed = aftertax - 3500
						  - ATAX(1500, 3)
						  - ATAX(4500 - 1500, 10)
						  - ATAX(9000 - 4500, 20)
						  - ATAX(35000 - 9000, 25);
		beforetax = 3500 + 35000 + BTAX(exceed, 30);
	}
	else if (aftertax <= 3500 + ATAX(1500, 3)
							  + ATAX(4500 - 1500, 10)
							  + ATAX(9000 - 4500, 20)
							  + ATAX(35000 - 9000, 25)
							  + ATAX(55000 - 35000, 30)
							  + ATAX(80000 - 55000, 35)) {
		exceed = aftertax - 3500
						  - ATAX(1500, 3)
						  - ATAX(4500 - 1500, 10)
						  - ATAX(9000 - 4500, 20)
						  - ATAX(35000 - 9000, 25)
						  - ATAX(55000 - 35000, 30);
		beforetax = 3500 + 55000 + BTAX(exceed, 35);
	}
	else {
		exceed = aftertax - 3500
						  - ATAX(1500, 3)
						  - ATAX(4500 - 1500, 10)
						  - ATAX(9000 - 4500, 20)
						  - ATAX(35000 - 9000, 25)
						  - ATAX(55000 - 35000, 30)
						  - ATAX(80000 - 55000, 35);
		beforetax = 3500 + 80000 + BTAX(exceed, 45);
	}

	cout << beforetax << endl;

	return 0;
}