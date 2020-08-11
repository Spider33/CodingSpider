#include<iostream>
#include<vector>
#include<string>

using namespace std;


////////////////1.KMP�㷨////////////////////////
void getNext(string p, vector<int>& next) {
    int i = 0, j = -1;
    next[0] = -1;
    while (i < (int)p.size()-1) {    //ʱ��O(N)
        if (j == -1 || p[i] == p[j]) {  //j==-1��ƥ��ʧ�ܣ�ƥ�䳤��Ϊ 0���޹�����    //p[i]==p[j]:��ĸ��ȣ�ƥ��ɹ���ƥ�䳤��+1
            next[++i] = ++j;
        }
        else {
            j = next[j];    //ƥ��ʧ�ܣ�������������û��ǰ׺�ͺ�׺��ȵĲ��֣��еĻ�����Ȳ��ֵĺ�һ����ĸ�Ƚ�
        }
    }
}

int KMP(string t, string p) {
    
    vector<int> next(p.size()+1, 0);    //��1λ��һ���ָ�λ��next[i]�����i����������Ӧ��ƥ��ֵ��������鳤��Ҫ+1
    getNext(p, next);
    int i = 0, j = 0;
    while (i < (int)t.size() && j < (int)p.size()) {    //ʱ��O(M)
        if (j==-1 || t[i] == p[j]) {    //j==-1��ƥ��ʧ�ܣ�ƥ�䳤��Ϊ 0���޹�����    //p[i]==p[j]:��ĸ��ȣ�ƥ��ɹ���ƥ�䳤��+1
            i++;
            j++;
        }
        else {  //ƥ��ʧ�ܣ�������������û��ǰ׺�ͺ�׺��ȵĲ��֣��еĻ�����Ȳ��ֵĺ�һ����ĸ�Ƚϣ�û�еĻ�֤����ǰ�ַ�����û����ģʽ��ǰ׺��ȵĲ���
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

////////////////////1.1 ��̻��Ĵ�///////////////////////////
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