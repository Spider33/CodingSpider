//#define N3

#ifdef N3

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
	//数据输入//////////////////////////////////////////////
	int n,m,t;
	cin >> n>>m>>t;

	vector<pair<int, int>> lunch;
	vector<pair<int, int>> diner;

	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		lunch.push_back(make_pair(x,y));
	}
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		diner.push_back(make_pair(x, y));
	}

	//////////////////处理函数/////////////////////////////
	//按照热量高低进行升序
	sort(lunch.begin(), lunch.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		return a.first == b.first ? a.second < b.second : a.first < b.first;
		});
	sort(diner.begin(), diner.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		return a.first == b.first ? a.second < b.second : a.first < b.first;
		});

	int flag1, flag2;
	int res = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (lunch[i].second >= t) {
			res = min(res, lunch[i].first);
			break;
		}
	}
	for (int i = 0; i < m; i++) {
		if (diner[i].second >= t) {
			res = min(res, diner[i].first);
			break;
		}
	}

	for (int i = 0; i < n; i++) {
		if (lunch[i].second < t) {
			for (int j = 0; j < m; j++) {
				if ((lunch[i].second + diner[j].second >= t) && (diner[j].second < t)) {
					res = min(res, lunch[i].first + diner[j].first);
					break;
				}
			}
		}
	}

	cout << (res == INT_MAX ? -1 : res) << endl;

	return 0;
}




#endif