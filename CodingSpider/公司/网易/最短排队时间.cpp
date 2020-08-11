#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<limits.h>
#include<iomanip>

using namespace std;


/*
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int m;
		cin >> m;

		vector<int> path1(m, 0);
		vector<int> path2(m - 1, 0);
		for (int j = 0; j < m; j++) {
			cin >> path1[j];
		}
		for (int j = 0; j < m - 1; j++) {
			cin >> path2[j];
		}
		vector<int>   dp(m + 1, INT_MAX);

		dp[0] = 0;
		dp[1] = path1[0];
		for (int k = 2; k <= m; k++) {
			dp[k] = min(dp[k - 1] + path1[k - 1], dp[k - 2] + path2[k - 2]);
		}

		int hour = dp[m] / 60+8;
		int minute = dp[m] % 60;

		string s = " am";
		if (n >= 4)    s = " pm";
		cout << setw(2) << setfill('0') << hour <<":00£º"<< setw(2)<< setfill('0') << minute << s << endl;
	}
	system("pause");
	return 0;
}
*/
