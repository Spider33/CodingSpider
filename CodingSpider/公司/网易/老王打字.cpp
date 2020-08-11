//#define N2 1

#ifdef  N2



#include <iostream>
#include<vector>
#include<algorithm>
//#include<math.h>

using namespace std;

int main1() {

	int m=100;

	vector<int>  dp(m + 1, m);   //m最少用m次
	
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
①即为上面，在输入了i个字符的基础上，再输入10 - i个，(i为从1到9)；
②第二种情况：输入了i个字符后，我复制这i个字符，取消选择，然后在后面进行多次粘贴，这里的i可以从1到10 / 2；循环取i，求最小值，需要注意的是，当10 % i不为0时，需要再加上F(10 % i)；
③第三种情况：输入了i个字符后，我还是复制粘贴这i个字符，但是上面②是复制之后，取消选择，在原来的后面继续粘贴；这里我复制之后，输入一个字符，将原来输入的都覆盖掉，然后再粘贴；

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
			dp[i] = min(dp[i], dp[i - j] + j); //情况①
		for (int j = 1; j <= i / 2; j++)
		{
			dp[i] = min(dp[i], dp[j] + i / j * 2 + 3 + dp[i % j]); //情况②
			//dp[i] = min(dp[i], dp[j] + i / j * 2 + 5); //情况③
		}
	}

	cout << dp[N] << endl;

	system("pause");
	return 0;
}

#endif