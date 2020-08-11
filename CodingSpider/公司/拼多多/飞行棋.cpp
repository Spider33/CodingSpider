//#define N1

#ifdef N1


#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int len, step;
    cin >> len >> step;

    if (len == 0)
    {
        cout << "paradox" << endl;
        return 0;
    }

    vector<int> arr(step, 0);
    for (int i = 0; i < arr.size(); i++)
        cin >> arr[i];

    bool flag = false;
    int res = len;
    int back_step = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        len -= arr[i];
        if (len < 0)
        {
            back_step++;
            len = -len;
        }
        else if (len == 0 && i!=arr.size()-1)
        {
            flag = true;
            break;
        }
        else
            continue;
    }

    if (flag)
        cout << "paradox" << endl;
    else
        cout << len << " " << back_step << endl;

    return 0;
}





#endif // N1
