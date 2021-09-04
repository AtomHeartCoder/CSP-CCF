#include <iostream>
#include <stdio.h>

using namespace std;

int main(void)
{
	int n;
	short price[300 + 2];
	short price2[300 + 2];

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> price2[i];
		price[i] = -1;
	}
	price[0] = price2[1];
	price[n + 1] = price2[n];

	for (int i = 3; i <= n; i += 3) {


		
	}




	return 0;
}