#include<iostream>
#include<vector>
#include<string>

using namespace std;


////////////////1.KMP算法////////////////////////
void getNext(string p, vector<int>& next) {
    int i = 0, j = -1;
    next[0] = -1;
    while (i < (int)p.size()-1) {    //时间O(N)
        if (j == -1 || p[i] == p[j]) {  //j==-1：匹配失败，匹配长度为 0，无公共串    //p[i]==p[j]:字母相等，匹配成功，匹配长度+1
            next[++i] = ++j;
        }
        else {
            j = next[j];    //匹配失败，看看公共串有没有前缀和后缀相等的部分，有的话，相等部分的后一个字母比较
        }
    }
}

int KMP(string t, string p) {
    
    vector<int> next(p.size()+1, 0);    //第1位是一个恢复位，next[i]代表第i个数字所对应的匹配值，因此数组长度要+1
    getNext(p, next);
    int i = 0, j = 0;
    while (i < (int)t.size() && j < (int)p.size()) {    //时间O(M)
        if (j==-1 || t[i] == p[j]) {    //j==-1：匹配失败，匹配长度为 0，无公共串    //p[i]==p[j]:字母相等，匹配成功，匹配长度+1
            i++;
            j++;
        }
        else {  //匹配失败，看看公共串有没有前缀和后缀相等的部分，有的话，相等部分的后一个字母比较，没有的话证明当前字符串中没有与模式串前缀相等的部分
            j = next[j];
        }
    }
    return j == p.size() ? i - j : -1;
}
//
//int main() {
//    string t;
//    string p;
//    cin >> t >> p;
//    int i = KMP(t, p);
//    cout << i << endl;
//    system("pause");
//    return 0;
//}

////////////////////1.1 最短回文串///////////////////////////
string shortestPalindrome(string s) {
    int n = s.size();
    string res(s);
    reverse(res.begin(), res.end());

    string s_new = s + "#" + res;
    int n_new = s_new.size()+1;

    vector<int>  next(n_new, 0);
    next[0] = -1;
    int i = 0, j = -1;
    while (i < n_new - 1) {
        if (j == -1 || s_new[i] == s_new[j])
            next[++i] = ++j;
        else
            j = next[j];
    }
    return res.substr(0, n - next[n_new - 1]) + s;
}



//int main() {
//    string t;
//    cin >> t;
//    string i = shortestPalindrome(t);
//    cout << i << endl;
//    system("pause");
//    return 0;
//}