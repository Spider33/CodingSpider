//#define N2 1

#ifdef  N2



#include <iostream>
#include<vector>
#include<algorithm>
//#include<math.h>

using namespace std;

int main1() {

	int m=100;

	vector<int>  dp(m + 1, m);   //m������m��
	
	for (int i = 0; i < 7; i++) {
		dp[i] = i;
	}

	for (int i = 7; i <= m; i++) {
		for (int j = 1; j < i/2;j++) {
			if (i % j == 0) {
				dp[i] = min(dp[j] + 2 * (i / j - 1) + 5, dp[i]);
			}
		}
	}

	cout << dp[m] << endl;

	system("pause");
	return 0;
}

/*
�ټ�Ϊ���棬��������i���ַ��Ļ����ϣ�������10 - i����(iΪ��1��9)��
�ڵڶ��������������i���ַ����Ҹ�����i���ַ���ȡ��ѡ��Ȼ���ں�����ж��ճ���������i���Դ�1��10 / 2��ѭ��ȡi������Сֵ����Ҫע����ǣ���10 % i��Ϊ0ʱ����Ҫ�ټ���F(10 % i)��
�۵����������������i���ַ����һ��Ǹ���ճ����i���ַ�������������Ǹ���֮��ȡ��ѡ����ԭ���ĺ������ճ���������Ҹ���֮������һ���ַ�����ԭ������Ķ����ǵ���Ȼ����ճ����

*/
int main()
{
	int N;
	cin >> N;
	vector<int> dp(N + 1, 99999);
	dp[0] = 0;
	dp[1] = 1;
	for (int i = 2; i <= N; i++)
	{
		for (int j = 1; j <= i; j++)
			dp[i] = min(dp[i], dp[i - j] + j); //�����
		for (int j = 1; j <= i / 2; j++)
		{
			dp[i] = min(dp[i], dp[j] + i / j * 2 + 3 + dp[i % j]); //�����
			//dp[i] = min(dp[i], dp[j] + i / j * 2 + 5); //�����
		}
	}

	cout << dp[N] << endl;

	system("pause");
	return 0;
}

#endif