//#define N3 1

#ifdef  N3



#include <iostream>
#include<vector>
#include<algorithm>
//#include<math.h>

using namespace std;

int main() {

    int N, K;
    cin >> N >> K;
    vector<int> arr(N, 0);
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    int flag = 0;
    int res = 0;

    sort(arr.begin(), arr.end());
    while (arr[N-K])
    {

        for (int i = N - 1; i >= N - K; i--)
            arr[i]--;
        sort(arr.begin(), arr.end());
        res++;
    }

    cout << res << endl;

	system("pause");
	return 0;
}


#endif