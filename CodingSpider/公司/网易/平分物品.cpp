#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int sumN(vector<int>& arr) {
	int sum = 0;
	for (int i = 0; i < arr.size(); i++) {
		sum += arr[i];
	}
	return sum;
}

int pingFen(vector<int>& arr) {
	int _sum = sumN(arr);
	int aver = _sum / 2;
	int n = arr.size();
	sort(arr.begin(), arr.end());
	int left = 0, right = n-1;
	int summ = 0;
	return 0;
}
/*
int main() {
	int n;
	cin >> n;
	vector<vector<int>>  nums;
	for(int i=0;i<n;i++){
		int m;
		cin >> m;
		vector<int> path(m,0);
		for (int j = 0; j < m; j++) {
			cin >> path[j];
		}
		nums.push_back(path);
	}
	vector<int>  res(n, 0);
	for (int i = 0; i < n; i++) {
		int sum = 
	}

	return 0;
}
*/