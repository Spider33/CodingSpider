#include<iostream>
using namespace std;

//////////////1.����ƽ����_633//////////////////////////
bool judgeSquareSum(int c) {
	int s = 0, e = sqrt(c);
	while (s <= e) {
		int sum = pow(s, 2) + pow(e, 2);
		if (sum > c)	e--;
		else if (sum < c)	s++;
		else return true;
	}
	return false;
}


////////////////////2.�����ַ���_680//////////////////////
//���ɾ��һ���ַ�
bool isPalindrome1(string& s, int start, int end) {
	while (start <= end) {
		if (s[start] != s[end])	return false;
		start++;
		end--;
	}
	return true;
}

bool validPalindrome(string s) {
	int left = 0;
	int right = s.size() - 1;
	while (left <= right) {
		if (s[left] != s[right]) {
			return isPalindrome1(s, left + 1, right) || isPalindrome1(s, left, right - 1);
		}
		left++;
		right--;
	}
	return true;
}