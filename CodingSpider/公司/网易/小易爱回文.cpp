//#include<iostream>
//#include<vector>
//#include<string>
//#include<algorithm>
//using namespace std;
//
//
///*
//һ���ַ�������������ĸʹ���Ϊ��̻����Ӵ�
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
//    //��������
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
