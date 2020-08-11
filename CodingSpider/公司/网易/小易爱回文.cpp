//#include<iostream>
//#include<vector>
//#include<string>
//#include<algorithm>
//using namespace std;
//
//
///*
//一个字符串后面增加字母使其成为最短回文子串
//*/
//string shortestPalindrome(string s)
//{
//    int n = s.size();
//    string rev(s);
//    reverse(rev.begin(), rev.end());
//    for (int i = 0; i < n; i++) {
//        if (s.substr(i) == rev.substr(0, n - i))
//            return  s + rev.substr(n-i);
//    }
//    return "";
//}
//
///*
//int main() {
//    //数据输入
//    string s1 = "abcdefgg";
//    string s2 = shortestPalindrome(s1);
//        cout << s2 << endl;
//
//
//    system("pause");
//    return 0;
//}
//
//*/
//
//
//
//
//
