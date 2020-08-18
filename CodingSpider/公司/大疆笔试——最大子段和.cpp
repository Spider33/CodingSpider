//#include<iostream>
//#include<vector>
//#include<string>
//#include<algorithm>
//using namespace std;
//
//
//int findMax(vector<int>& nums, int start, int end) {
//	int pre = nums[start];
//	int res = pre;
//	for (int i = start+1; i <= end; i++) {
//		pre = pre > 0 ? pre + nums[i] : nums[i];
//		res = max(res, pre);		
//	}
//	return res;
//}
//
//int  main() {
//	int n;
//	cin >> n;
//	string s;
//	getline(cin, s);
//	while (n--) {
//		//输入数据
//		int len;
//		cin >> len;
//		//cout << len << endl;
//		vector<int> nums(len, 0);
//		for (int i = 0; i < len; i++) {
//			cin >> nums[i];
//			//cout << nums[i];
//		}
//		getline(cin, s);
//
//		if (len == 2)
//		{
//			cout << nums[0] + nums[1] << endl;
//			break;
//		}
//		//处理数据
//		int res = -20001;
//
//		for (int i = 0; i < len-1; i++) {
//			res = max(res,findMax(nums, 0, i)+findMax(nums, i + 1, len - 1));
//		}
//		cout << res << endl;
//	}
//	system("pause");
//	return 0;
//}