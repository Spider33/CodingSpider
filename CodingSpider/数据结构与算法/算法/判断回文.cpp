//#include<iostream>
//#include<vector>
//#include<string>
//#include<algorithm>
//
//using namespace std;
//
///*
//   如果要求输出所有可能的解，使用深度优先搜索。
//   如果要找出最优的解，或者解的数量，往往可以使用动态规划。
//*/
//
//
//
//
/////////////1. 分割回文串_131/////////
//bool IsPalindrome1(const string& s) {
//    for (int i = 0; i < s.size() / 2; i++) {
//        if (s[i] != s[s.size() - i - 1])
//            return false;
//    }
//    return true;
//}
//
//void partition(const string& s, int start, vector<string>& temp, vector<vector<string>>& res) {
//    if (start >= s.size()) res.push_back(temp); //终止条件
//    string t;
//    for (int i = start; i < s.size(); i++) {
//        t.push_back(s[i]);
//        if (IsPalindrome1(t)) {  //如果t目前是回文，则可以继续往下进行回文，否则返回
//            temp.push_back(t);
//            partition(s, i + 1, temp, res);
//            temp.pop_back();
//        } 
//    }
//}
//
//vector<vector<string>> partition(string s) {
//    vector<vector<string>> res;
//    vector<string> temp;    //temp代表每一种分割的方法
//    partition(s, 0, temp, res);
//    return res;
//}
//
//
//
//////////////////////2.分割回文串2_132//////////////////////
///*
//最少分割数
//*/
//int minCut(string s) {
//    int n = s.size();
//    if (n < 1) return 0;
//
//    vector<int> dp(n,0);  //表示子串（0，i）的最小回文分割次数
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
//    vector<int> list(l + 1); // list[i]代表前i个字符需要划几次，特别地，list[0]=-1
//    for (int i = 0; i < l + 1; ++i) { // 初始化[-1, 0, 1, 2, 3...]
//        list[i] = i - 1;
//    }
//    for (int i = 0; i < l; ++i) { // 以每个字符为中心找最长回文子串
//        list[i + 1] = min(list[i + 1], list[i] + 1); // 初始化，最坏情况下就比左边的多划一次
//        if (i == l - 1) { // 最后一个了没必要找了
//            break;
//        }
//        // 先找偶数个的
//        int start = i, end = i + 1;
//        while (s[start] == s[end]) {
//            list[end + 1] = min(list[end + 1], list[start] + 1);
//            if (end == l - 1 || start == 0)       break;
//            --start, ++end;
//        }
//        // 再找奇数个的
//        start = i - 1, end = i + 1;
//        if (start < 0) {
//            continue;
//        }
//        while (s[start] == s[end]) {
//            list[end + 1] = min(list[end + 1], list[start] + 1);
//            if (end == l - 1 || start == 0)      break;
//            --start, ++end;
//        }
//        // 如果整个串都是回文串，那么就中断
//        if (list[l] == 0) {
//            return 0;
//        }
//    }
//    return list[l];
//}
//
//
////////////////////////3. 回文子串_647/////////////////////////
////计算字符串中有多少回文子串
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
///////////////////////4.最长回文子串_5/////////////////
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
//        int len1 = expandAroundCenter(s, i, i); //一个元素为中心
//        int len2 = expandAroundCenter(s, i, i + 1); //两个元素为中心
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
////马拉车算法
//
//
//
//
//////////////////////5.回文数_9//////////////
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