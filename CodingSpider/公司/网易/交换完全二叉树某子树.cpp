//#define N1 1

#ifdef N1




#include<iostream>
#include<vector>

using namespace std;

void dfs(vector<int>& arr, int left, int right) {
	if (left > arr.size() - 1 || right > arr.size() - 1)	return;
	else {
		dfs(arr, 2 * left + 1, 2 * right + 1);
		dfs(arr, 2 * (left + 1), 2 * (right + 1));
		swap(arr[left], arr[right]);
		return;
	}

}

void dffs(vector<int>& arr, int left, int right) {
	int m = left, n = right;
	while (m <= arr.size()  && n <= arr.size()) {
		int len = (n - m + 1) / 2;
		for (int i = 0; i < len; i++) {
			swap(arr[m+i-1], arr[m + i + len-1]);
		}
		m = m * 2;
		n = n * 2 + 1;
	}
	return;
}

int main() {
	vector<int> arr = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 };
	int n = 3;

	//dfs(arr, 2 * n - 1, 2 * n);
	dffs(arr, 2 * n , 2 * n+1);

	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}

#endif // 