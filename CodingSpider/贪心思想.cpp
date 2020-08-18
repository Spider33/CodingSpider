/*
̰��˼����Ҫ��֤ÿ�β������Ǿֲ����ţ��������õ��Ľ����ȫ�����ŵ�
*/

#include<iostream>
#include<vector>
#include<list>
#include<algorithm>

using namespace std;

/////////////////1.�������_455//////////////
int findContentChildren(vector<int>& g, vector<int>& s) {
	sort(g.begin(), g.end());
	sort(s.begin(), s.end());
	int sum = 0;
	int i = 0;
	int j = 0;
	while (i < g.size() && i < s.size()) {
		if (g[i] <= s[j]) {
			sum++;
			i++;
			j++;
		}
		else
			j++;
	}
	return sum;
}


/////////////2. ���ص�����_435/////////////////////////////
//��Ҫ�Ƴ��������С����
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
	if (intervals.empty())	return 0;
	sort(intervals.begin(), intervals.end());
	int left = intervals[0][1];
	int res = 0;
	for (int i = 1; i < intervals.size(); i++) {
		if (intervals[i][0] < left) {
			res++;
			left = min(left, intervals[i][1]);	//ѡ���С�������յ�
		}
		else
			left = intervals[i][1];	//�����ĵ���
	}
	return res;
}

//////////////////3. Ͷ���ڴ�������_452/////////////////////////
//�����������ļ���������
//ת��Ϊ���ص�����
int findMinArrowShots(vector<vector<int>>& points) {
	if (points.empty())	return 0;
	sort(points.begin(), points.end());

	int n = points.size();
	int count = 0;
	int left = points[0][1];
	for (int i = 1; i < n; i++) {
		if (points[i][0] <= left) {
			count++;
			left = min(points[i][1], left);
		}
		else
			left = points[i][1];
	}
	return (n - count);
}

/////////////////4. ������ߺ�����������_406////////////////
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
	sort(people.begin(), people.end(), [](const auto& a, const auto& b) {
		return a[0] == b[0] ? a[1]<b[1] : a[0]>b[0];	//��߽�����������
		});
	int n = people.size();

	/*
	vector<vector<int>> res;
	for(auto &e:people){
		res.insert(res.begin() + e[1], e);
	}
	return res;
	*/

	list<vector<int>> tmp;
	for (int i = 0; i < n; i++) {
			auto pose = tmp.begin();
			advance(pose, people[i][1]);  //�ú����Ĺ����ǽ� it ������ǰ������� n ��λ��
			tmp.insert(pose, people[i]);
	}
	return vector<vector<int>>(tmp.begin(), tmp.end());
}


////////////////5. ��ֲ����_605/////////////////////////////
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
	int len = flowerbed.size();
	if (len / 2 + 1 < n)	return false;	//�жϺ�������Ƿ�����

	vector<int> index(len + 2, 0);
	for (int i = 1; i < len + 1; i++)
		index[i] = flowerbed[i - 1];
	for (int i = 1; i < len + 1; i++) {
		if (index[i - 1] == 0 && index[i] == 0 && index[i + 1] == 0) {
			n--;
			index[i] = 1;
		}
		if (n == 0)	return true;
	}
	return n <= 0;	
}


///////////////6. �ж��Ƿ�Ϊ������_392////////////////
bool isSubseque(string s, string t) {
	int cout = 0;
	for (int i = 0; i < t.size(); i++)
		if (t[i] == s[cout]) cout++;

	return cout == s.size();
}

///////////////7. �޸�һ����Ϊ�ǵݼ���////////////////////
 
bool checkPossibility(vector<int>& nums) {
	int cnt = 0;
	for (int i = 1; i < nums.size() && cnt < 2; i++) {
		if (nums[i] >= nums[i - 1])	continue;
		cnt++;
		if (i >= 2 && nums[i - 2] > nums[i])
			nums[i] = nums[i - 1];
		else
			nums[i - 1] = nums[i];
	}
	return cnt <= 1;

}


///////////////////8.������ĸ����_763///////////////
vector<int> partitionLabels(string s) {
	vector<int> res;
	int start = 0;
	int end = 0;
	for (int i = 0; i < s.size(); i++) {
		int pos = s.find_last_of(s[i]);
		if (pos == end && i == end) {
			res.push_back(end - start + 1);
			start = end + 1;
			end = start;
		}
		else if(pos > end)
			end = pos;
	}
	return res;
}


//�������ұߵ�λ��
vector<int> partitionLabels_(string s) {
	int n = s.size();
	vector<int> ends(26, -1);
	for (int i = 0; i < n; i++)
		ends[s[i] - 'a'] = i;
	vector<int> res;
	int i = 0;
	while (i < n) {
		int r = ends[s[i] - 'a'];
		for (int j = i + 1; j < r; j++)
			r = max(r, ends[s[j] - 'a']);
		res.push_back(r - i + 1);
		i = r + 1;
	}
	return res;
}





