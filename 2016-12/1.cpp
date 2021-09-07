#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
	int n;
	cin >> n;

	vector<int> nums(n);
	for (int i = 0; i < n; i++)
		cin >> nums[i];

	sort(nums.begin(), nums.end());

	int midnum;
	if (n & 0x1) {
		int idx = n / 2;
		midnum = nums[idx];
		for (int i = 1; i <= idx; i++) {
			if (nums[idx - i] != nums[idx + i]) {
				if (nums[idx - i] == midnum || nums[idx + i] == midnum)
					midnum = -1;
				break;
			}
		}
	} else {
		int i = n / 2 - 1;
		int j = n / 2;
		if (nums[i] != nums[j]) {
			midnum = -1;
		} else {
			midnum = nums[i];
			while (i >= 0 && j < n) {
				if (nums[i] != nums[j]) {
					if (nums[i] == midnum || nums[j] == midnum)
						midnum = -1;
					break;
				}
				i--;
				j++;
			}
		}
	}

	cout << midnum << endl;

	return 0;
}