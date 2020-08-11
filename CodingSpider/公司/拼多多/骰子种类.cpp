//#define N2

#ifdef N2

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


//按哪个方向旋转，则对应两个数字不变，其余数字可以改变
//查看当前数字上下左右四个数字
void aroundNum(vector<int> arr, vector<int>& res, int pos)
{
    if (pos == 0)
    {
        res[0] = arr[5];
        res[1] = arr[4];
        res[2] = arr[2];
        res[3] = arr[3];
    }
    else if (pos == 1)
    {
        res[0] = arr[4];
        res[1] = arr[5];
        res[2] = arr[2];
        res[3] = arr[3];
    }
    else if (pos == 2)
    {
        res[0] = arr[0];
        res[1] = arr[1];
        res[2] = arr[5];
        res[3] = arr[4];
    }
    else if (pos == 3)
    {
        res[0] = arr[0];
        res[1] = arr[1];
        res[2] = arr[4];
        res[3] = arr[5];
    }
    else if (pos == 4)
    {
        res[0] = arr[0];
        res[1] = arr[1];
        res[2] = arr[2];
        res[3] = arr[3];
    }
    else if (pos == 5)
    {
        res[0] = arr[0];
        res[1] = arr[1];
        res[2] = arr[3];
        res[3] = arr[2];
    }
}

bool isSame(vector<int> arr1, vector<int> arr2)
{
    int pos1, pos2;
    vector<int> index1(4, 0);
    vector<int> index2(4, 0);
    for (int i = 0; i < 6; i++)
        if (arr1[i] == 1)
            pos1 = i;
    aroundNum(arr1, index1, pos1);
    for (int i = 0; i < 6; i++)
        if (arr2[i] == 1)
            pos2 = i;
    aroundNum(arr2, index2, pos2);

    if ((index1[0] == index2[0] && index1[1] == index2[1] && index1[2] == index2[2] && index1[3] == index2[3]) ||
        (index1[0] == index2[3] && index1[1] == index2[2] && index1[2] == index2[0] && index1[3] == index2[1]) ||
        (index1[0] == index2[1] && index1[1] == index2[0] && index1[2] == index2[3] && index1[3] == index2[2]) ||
        (index1[0] == index2[2] && index1[1] == index2[3] && index1[2] == index2[1] && index1[3] == index2[0]))
        return true;
    else
        return false;
}

int main()
{
    int num;
    cin >> num;
    vector<vector<int>> arr(num, vector<int>(6, 0));
    //读取数据
    for (int i = 0; i < num; i++)
        for (int j = 0; j < 6; j++)
            cin >> arr[i][j];

    vector<int> used(num, 0);
    vector<int> res;
    for (int i = 0; i < arr.size(); i++)
    {
        int times = 1;
        if (!used[i])
        {
            for (int j = i+1; j < arr.size(); j++)
            {
                if (isSame(arr[i], arr[j]) && used[j] == 0)
                {
                    used[j] = 1;
                    times++;
                }
            }
            res.push_back(times);
        }
    }

    cout << res.size() << endl;
    sort(res.begin(), res.end());
    for (int i = res.size() - 1; i >= 0; i--)
        cout << res[i] << " ";

    system("pause");
    return 0;
}

#endif