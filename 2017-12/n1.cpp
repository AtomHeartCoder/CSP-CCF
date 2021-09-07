#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
	int n;
	cin >> n;

	vector<short> nums(n);

	for (int i = 0; i < n; i++)
		cin >> nums[i];

	sort(nums.begin(), nums.end());
	
	short min = 0x7fff;
	for (int i = 0; i < n - 1; i++) {
		short d = nums[i + 1] - nums[i];
		if (d < min)
			min = d;
	}

	cout << min << endl;

	return 0;
}