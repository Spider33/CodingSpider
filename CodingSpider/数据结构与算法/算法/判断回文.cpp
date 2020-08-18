//#include<iostream>
//#include<vector>
//#include<string>
//#include<algorithm>
//
//using namespace std;
//
///*
//   ���Ҫ��������п��ܵĽ⣬ʹ���������������
//   ���Ҫ�ҳ����ŵĽ⣬���߽����������������ʹ�ö�̬�滮��
//*/
//
//
//
//
/////////////1. �ָ���Ĵ�_131/////////
//bool IsPalindrome1(const string& s) {
//    for (int i = 0; i < s.size() / 2; i++) {
//        if (s[i] != s[s.size() - i - 1])
//            return false;
//    }
//    return true;
//}
//
//void partition(const string& s, int start, vector<string>& temp, vector<vector<string>>& res) {
//    if (start >= s.size()) res.push_back(temp); //��ֹ����
//    string t;
//    for (int i = start; i < s.size(); i++) {
//        t.push_back(s[i]);
//        if (IsPalindrome1(t)) {  //���tĿǰ�ǻ��ģ�����Լ������½��л��ģ����򷵻�
//            temp.push_back(t);
//            partition(s, i + 1, temp, res);
//            temp.pop_back();
//        } 
//    }
//}
//
//vector<vector<string>> partition(string s) {
//    vector<vector<string>> res;
//    vector<string> temp;    //temp����ÿһ�ַָ�ķ���
//    partition(s, 0, temp, res);
//    return res;
//}
//
//
//
//////////////////////2.�ָ���Ĵ�2_132//////////////////////
///*
//���ٷָ���
//*/
//int minCut(string s) {
//    int n = s.size();
//    if (n < 1) return 0;
//
//    vector<int> dp(n,0);  //��ʾ�Ӵ���0��i������С���ķָ����
//    for (int i = 0; i < n; i++) {
//        if (IsPalindrome1(s.substr(0, i + 1))) {
//            continue;
//        }
//        else
//            dp[i] = i;
//        for (int j = 1; j <= i; j++) {
//            string sub = s.substr(j, i-j + 1);
//            if (IsPalindrome1(sub))
//                dp[i] = min(dp[i], dp[j - 1] + 1);
//            else
//                dp[i] = min(dp[i], dp[j - 1] + i + 1 - j);
//        }
//    }
//    return dp[n - 1];
//}
//
/////////
//int minCut1(string s) {
//    int l = s.length();
//    vector<int> list(l + 1); // list[i]����ǰi���ַ���Ҫ�����Σ��ر�أ�list[0]=-1
//    for (int i = 0; i < l + 1; ++i) { // ��ʼ��[-1, 0, 1, 2, 3...]
//        list[i] = i - 1;
//    }
//    for (int i = 0; i < l; ++i) { // ��ÿ���ַ�Ϊ������������Ӵ�
//        list[i + 1] = min(list[i + 1], list[i] + 1); // ��ʼ���������¾ͱ���ߵĶ໮һ��
//        if (i == l - 1) { // ���һ����û��Ҫ����
//            break;
//        }
//        // ����ż������
//        int start = i, end = i + 1;
//        while (s[start] == s[end]) {
//            list[end + 1] = min(list[end + 1], list[start] + 1);
//            if (end == l - 1 || start == 0)       break;
//            --start, ++end;
//        }
//        // ������������
//        start = i - 1, end = i + 1;
//        if (start < 0) {
//            continue;
//        }
//        while (s[start] == s[end]) {
//            list[end + 1] = min(list[end + 1], list[start] + 1);
//            if (end == l - 1 || start == 0)      break;
//            --start, ++end;
//        }
//        // ������������ǻ��Ĵ�����ô���ж�
//        if (list[l] == 0) {
//            return 0;
//        }
//    }
//    return list[l];
//}
//
//
////////////////////////3. �����Ӵ�_647/////////////////////////
////�����ַ������ж��ٻ����Ӵ�
//int countSubstring(string s) {
//    if (s.empty())   return 0;
//    int n = s.size();
//    vector<vector<bool>>    dp(n, vector<bool>(n, false));
//    int res = 0;
//    for (int i = n - 1; i >= 0; i--) {
//        for (int j = i; j < n; j++) {
//            dp[i][j] = (s[i] == s[j]) && (j - i <= 2 || dp[i + 1][j - 1]);
//            if (dp[i][j])    res++;
//        }
//    }
//    return res;
//}
//
///////////////////////4.������Ӵ�_5/////////////////
//int expandAroundCenter(string& s, int left,int right) {
//    int L = left, R = right;
//    while (L >= 0 && R < s.size() && s[R] == s[L]) {
//        L--;
//        R++;
//    }
//    return R-L - 1;
//}
//
//
//string longestPalindrome(string s) {
//    int len = s.size();
//    if (len < 2)   return s;
//    int start = 0;
//    int end = 0;
//    int max_len = 0;
//    for (int i = 0; i < len; i++) {
//        int len1 = expandAroundCenter(s, i, i); //һ��Ԫ��Ϊ����
//        int len2 = expandAroundCenter(s, i, i + 1); //����Ԫ��Ϊ����
//        max_len = max(max_len, max(len1, len2));
//        if (max_len > end - start + 1) {
//            start = i - (max_len - 1) / 2;
//            end = i + max_len / 2;
//        }
//    }
//    return s.substr(start, max_len);
//}
//
//
////�������㷨
//
//
//
//
//////////////////////5.������_9//////////////
//bool isPalindromeNum(int x) {
//    if (!x)  return true;
//    if (x < 0 || x % 10 == 0)   return false;
//    int s = 0;
//    while (x > s) {
//        s = s * 10 + x % 10;
//        x /= 10;
//    }
//    return x == s || x == s / 10;
//}