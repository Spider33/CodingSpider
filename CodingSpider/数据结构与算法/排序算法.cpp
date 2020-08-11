#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(nullptr){}
};


/*
选择排序	插入排序	冒泡排序	希尔排序	归并排序

快速排序	堆排序		计数排序	桶排序		基数排序
*/

///////////////////////////////////////////////////////////////
////////////////1、选择排序////////////////////////////////////
/*
找到数组中最小的那个元素，
将它和数组的第⼀一个元素交换位置
在剩下的元素中找到最⼩小的元素，将它与数组的第二个元素交换位置

1、时间复杂度：O(n2) 2、空间复杂度：O(1)   3、非稳定排序  4、原地排序

*/
void selectSort(vector<int>& arr) {
	int n = arr.size();
	for (int i = 0; i < n - 1; i++) {
		int min = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[min] > arr[j])	min = j;
		}
		int temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
	return;
}

///////////////////////////////////////////////////////////////
////////////////2、插入排序////////////////////////////////////
/*
1、时间复杂度：O(n2) 2、空间复杂度：O(1) 3、稳定排序4、原地排序

*/

void insertSort(vector<int>& arr) {
	if (arr.size() < 2)	return;

	int n = arr.size();
	for (int i = 1; i < n; i++) {
		int temp = arr[i];
		int k = i - 1;
		while (k >= 0 && arr[k] > temp)
			k--;
		//腾出位置插进去，要插入的位置是k+1
		for (int j = i; j > k + 1; j--) {
			arr[j] = arr[j - 1];
			arr[k + 1] = temp;
		}
	}
	return;
}

///////////////////////////////////////////////////////////////
////////////////3、冒泡排序////////////////////////////////////
/*
1、时间复杂度：O(n2) 2、空间复杂度：O(1) 3、稳定排序4、原地排序

*/
void bubbleSort(vector<int>& arr) {
	if (arr.size() < 2)	return;

	int n = arr.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n-i-1; j++) {
			if (arr[j + 1] < arr[i]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return;
}


///////////////////////////////////////////////////////////////
////////////////4、希尔排序////////////////////////////////////
/*
采⽤用插入排序的方法，先让数组中任意间隔为h 的元素有序，
刚开始h 的⼤小可以是h = n / 2,接着让h = n / 4，
让h一直缩⼩小，当h = 1 时，数组中任意间隔为1的元素有序

1、时间复杂度：O(nlogn) 2、空间复杂度：O(1) 3、⾮稳定排序4、原地排序

*/

void insertI(vector<int>& arr, int width, int j) {
	int temp = arr[j];
	int k=0;
	for ( k = j - width; k > 0 && temp < arr[k]; k -= width) {
		arr[k + width] = arr[k];
	}
	arr[k + width] = temp;
}

void shellSort(vector<int>& arr) {
	if (arr.size() < 2)	return;

	int n = arr.size();
	for (int i = n / 2; i > 0; i /= 2) {
		for (int j = i; j < n; j++) {
			insertI(arr, i, j);
		}
	}
	return;
}


///////////////////////////////////////////////////////////////
////////////////5、计数排序////////////////////////////////////
/*
计数排序是一种适合于最⼤值和最小值的差值不是很大的排序
********************************************************************
数组元素作为数组的下标，然后⽤用⼀个临时数组统计该元素出现的次数
例如temp[i] = m, 表示元素i 一共出现了m 次。
把临时数组统计的数据从小到大汇总起来
*********************************************************************
1、时间复杂度：O(n+k) 2、空间复杂度：O(k) 3、稳定排序4、非原地排序	*K表示临时数组的⼤小*

*/

void countSort(vector<int>& arr) {
	if (arr.size() < 2)	return;

	int n = arr.size();
	int _max = arr[0];
	int _min = arr[0];
	//寻找数组的最大值
	for (int i = 1; i < n; i++) {
		if (_max < arr[i])	_max = arr[i];
		if (_min > arr[i])	_min = arr[i];
	}
	//创建大小为max的临时数组
	vector<int> temp(_max-_min + 1, 0);
	//统计元素i出现的次数
	for (auto i : arr) 		temp[i-_min]++;
	
	int k = 0;
	//把临时数组统计好的数据汇总到原数组
	for (int i = 0; i <= _max-_min+1; i++) {
		for (int j = temp[i]; j > 0; j--) {
			arr[k++] = i+_min;
		}
	}
}

///////////////////////////////////////////////////////////////
////////////////6、桶排序////////////////////////////////////
/*
********************************************************************
桶排序就是把最大值和最小值之间的数进⾏瓜分
例如分成10 个区间，10个区间对应10个桶
各元素放到对应区间的桶中去，再对每个桶中的数进行排序
可以采⽤用归并排序，也可以采⽤用快速排序
*********************************************************************
1、时间复杂度：O(n+k) 2、空间复杂度：O(n+k) 3、稳定排序4、非原地排序

*/
void bucketSort(vector<int>& arr) {
	if (arr.size() < 2)	return;

	int n = arr.size();
	int _max = arr[0], _min = arr[0];
	for (auto i : arr) {
		_max = max(i, _max);
		_min = min(i, _min);
	}
	int d = _max - _min;
	//创建d / 5 + 1 个桶，第i 桶存放5*i ~ 5*i+5-1范围的数
	int bucketNum = d / 5 + 1;
	vector<vector<int>>	vl(bucketNum, vector<int>());
	//遍历原数组，将每个元素放入桶中
	for (int i = 0; i < n; i++) {		
		vl[arr[i] / d].push_back(arr[i] - _min);
	}
	//对桶内进行排序
	for (int i = 0; i < bucketNum; i++) {
		sort(vl[i].begin(), vl[i].end());
	}

	int k = 0;
	for (int i = 0; i < bucketNum; i++) {
		for (auto t : vl[i]) {
			arr[k++] = t + _min;
		}
	}
}

///////////////////////////////////////////////////////////////
////////////////7、基数排序////////////////////////////////////
/*
*********************************************************************
先以个位数的⼤小来对数据进⾏排序
以十位数的⼤小来多数进⾏
以百位数的⼤小......
*********************************************************************
1、时间复杂度：O(kn) 2、空间复杂度：O(n+k) 3、稳定排序4、非原地排序


*/
void  readioSort(vector<int> arr) {
	if (arr.size() < 2)	return;

	int n = arr.size();
	int _max = arr[0];
	//找出最大值
	for (auto a : arr) 	_max = max(_max, a);
	
	//计算最大值是几位数
	int cnt = 1;
	while (_max / 10 > 0) {
		cnt++;
		_max /= 10;
	}

	//创建10个桶
	vector<vector<int>>  num(10, vector<int>());
	//进行每一趟排序，从个位数开始排
	for (int i = 1; i <= cnt; i++) {
		for (int j = 0; j < n; j++) {
			//获取每个数最后第i位是数组
			int radio = arr[j] / (int)pow(10, i - 1) % 10;
			//放进对应的桶里
			num[radio].push_back(arr[j]);
		}
		//合并放回原数组
		int k = 0;
		for (int j = 0; j < 10; j++) {
			for (auto i : num[j]) {
				arr[k++] = i;
			}
			num.clear();
		}
	}
}





/////////////////////////1、快速排序/////////////////////////
/////////////////////////////////////////////////////////////
/*
1、时间复杂度：O(nlogn) 2、空间复杂度：O(logn) 3、非稳定排序4、原地排序

*/
int partition(vector<int>& arr, int left, int right) {
	int x = arr[left];
	int l = left, r = left + 1;
	for (r; r <= right; r++) {
		if (arr[r] < x)
			swap(arr[++l], arr[r]);
	}
	swap(arr[left], arr[l]);
	return l;
}

int randomPartition(vector<int>& arr, int left, int right) {
	int i = rand() % (right - left + 1) + left;
	swap(arr[i], arr[left]);
	return partition(arr, left, right);
}

void quickSort(vector<int>& arr, int left, int right) {
	//base case
	if (left >= right)	return;

	//int p = partition(arr, left, right);	//确定中间点进行前后划分
	int p = randomPartition(arr, left, right);

	quickSort(arr, left, p - 1);
	quickSort(arr, p + 1, right);
}






/////////////////////2、堆排序//////////////////////////////////
////////////////////////////////////////////////////////////////
/*
大顶堆：arr[i] >= arr[2i+1] && arr[i] >= arr[2i+2]
小顶堆：arr[i] <= arr[2i+1] && arr[i] <= arr[2i+2]


步骤一：建立大根堆--将n个元素组成的无序序列构建一个大根堆，
步骤二：交换堆元素--交换堆尾元素和堆首元素，使堆尾元素为最大元素；
步骤三：重建大根堆--将前n-1个元素组成的无序序列调整为大根堆


1、时间复杂度：O(nlogn) 2、空间复杂度：O(1) 3、非稳定排序4、原地排序

*/

// 递归方式构建大根堆(len是arr的长度，idx是第一个非叶子节点的下标)
void adjust(vector<int>& arr, int len, int idx) {
	int left = 2 * idx + 1;			//idx的左子节点
	int right = 2 * idx + 2;		//idx的右子节点

	int maxIdx = idx;
	if (left<len && arr[left]>arr[maxIdx])	maxIdx = left;
	if (right<len && arr[right]>arr[maxIdx])	maxIdx = right;

	if (maxIdx != idx) {
		swap(arr[maxIdx], arr[idx]);
		adjust(arr, len, maxIdx);
	}
}

void adjust1(vector<int>& arr, int len, int idx) {
	int curParent = arr[idx];
	int child = 2 * idx + 1;	//左孩子
	while (child < len) {	//没有孩子
		if (child < len && arr[child] < arr[child + 1])	child++;	//较大孩子的下标

		if (curParent < arr[child]) {
			//父节点下沉
			arr[idx] = arr[child];
			idx = child;
			child = 2 * idx + 1;
		}
		else break;
	}
	arr[idx] = curParent;	//完成互换
}

// 堆排序
void heapSort(vector<int>& arr, int size) {
	//构建大根堆
	for (int i = size / 2 - 1; i >= 0; i--) {
		adjust1(arr, size,i);
	}
	//调整大根堆
	for (int i = size - 1; i >= 1; i--) {
		swap(arr[0], arr[i]);	// 将当前最大的放置到数组末尾
		adjust(arr, i, 0);		// 将未完成排序的部分继续进行堆排序
	}

}

/*
int main() {
	vector<int> arr = { 4,6,8,5,9 };
	heapSort(arr, arr.size());
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << endl;
	system("pause");
	return 0;
}
*/

/////////////////////////////////3、归并排序/////////////////////////////////////
/*
1、将数组从中间分开，对两边分别排序。
2、将两个有序的数组进行合并。

1、时间复杂度：O(nlogn) 2、空间复杂度：O(n) 3、稳定排序4、⾮非原地排序


*/

void merge2(vector<int>& arr, int L, int mid, int R) {
	vector<int> help(R-L + 1,0);
	int p1 = L, p2 = mid + 1, i = 0;

	while (p1 <= mid && p2 <= R) {
		help[i++] = arr[p1] > arr[p2] ? arr[p2++] : arr[p1++];
	}
	while (p1 <= mid)	help[i++] = arr[p1++];
	while (p2 <= R)	help[i++] = arr[p2++];

	for (int i = 0; i < R - L + 1; i++) {
		arr[L + i] = help[i];
	}
}

void sortProcess(vector<int>& arr, int L, int R) {
	if (L < R) {
		int mid = L + (R - L) / 2;
		//递归实现分别排序
		sortProcess(arr, L, mid);
		sortProcess(arr, mid + 1, R);
		//排序后并合并
		merge2(arr, L, mid, R);
	}
}

void mergeSort(vector<int>& arr, int L, int R) {
	if (arr.size() < 2)	return;
	sortProcess(arr, L, R);
}

void mergeSort(vector<int>& arr) {
	int n = arr.size();
	if (n < 2)	return;

	for (int i = 1; i < n; i+=i) {
		int left = 0;
		int mid = left + i - 1;
		int right = mid + i;
		//进行合并
		while (right < n) {
			merge2(arr, left,mid, right);
			//更新
			left = right + 1;
			mid = left + i - 1;
			right = mid + i;
		}

		//   n/i不为0时还有数据么有归并
		if (left < n && mid < n) {
			merge2(arr, left, mid, n - 1);
		}
	}
}
/*
int main() {
	vector<int> arr = { 4,6,8,5,9,10,2,33,11 };
	mergeSort(arr, 0, arr.size()-1);
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << endl;
	system("pause");
	return 0;
}
*/

////////////////3、前k个高频元素//////////////
vector<int> ropKFrequent(vector<int>& nums, int k) {
	if (nums.size() < k)	return {};
	
	unordered_map<int, int>  record;	//元素——频率

	for (auto i : nums) {
		record[i]++;
	}
	int n = record.size();


	//扫描record。维护当前出现频率最多的k个元素
	//最小堆。如果当前元素的频率大于优先队列中最小频率元素的频率，则替换
	//优先队列中，按频率排序，所以数据对是(频率，元素)形式
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>  pq;
	for (auto it : record) {
		if (pq.size() == k) {
			if (it.second > pq.top().first) {
				pq.pop();
				pq.push(make_pair(it.second, it.first));
			}
			else
				pq.push(make_pair(it.second, it.first));
		}
	}

	vector<int> res;
	while (pq.size())
	{
		res.push_back(pq.top().second);
		pq.pop();
	}

	//reverse(res.begin(), res.end());
	return res;
}


/////////////////////////4、返回数组第k大的数///////////////////////////////

int quickSort(vector<int>& nums, int left, int right, int index) {
	int cur_idx = randomPartition(nums, left, right);
	if (cur_idx == index)	return nums[cur_idx];
	else
		return cur_idx<index ? quickSort(nums, cur_idx+1, right,index) : quickSort(nums, left, cur_idx-1,index);
}

int findKLargest(vector<int>& nums, int k) {
	if (nums.size() < k)	return -1;

	//return quickSort(nums, 0, nums.size() - 1, nums.size() - k);
	priority_queue<int, vector<int>, greater<int>> p;

	for (auto num : nums) {
		p.push(num);
		if (p.size() == k + 1)
			p.pop();
	}

	return p.top();
}


///////////////////////////5、排序链表///////////////
ListNode* merge3(ListNode* l1, ListNode* l2) {
	ListNode* dummy = new ListNode(0);
	ListNode* p = dummy;
	while (l1 && l2) {
		if (l1->val < l2->val) {
			p->next = l1;
			l1 = l1->next;
		}
		else {
			p->next = l2;
			l2 = l2->next;
		}
		p = p->next;
	}
	p->next = l1 ? l1 : l2;
	return dummy->next;
}

ListNode* sortList(ListNode* head) {
	if (!head || !head->next)    return head;
	ListNode* pre = head, * slow = head, * fast = head;
	while (fast && fast->next) {
		pre = slow;
		slow = slow->next;
		fast = fast->next->next;
	}
	pre->next = NULL;
	return merge3(sortList(head), sortList(slow));
}
