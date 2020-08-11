/*
1.基本框架

	# 初始化 base case
	dp[0][0]... = base

	# 进行状态转移
	for 状态1 in 状态1的所有取值：
		for 状态2 in 状态2的所有取值：
			for ...
				dp[状态1][状态2][...] = 求最值（选择1，选择2，...)

2.三种动态规划方案
	暴力递归
	带备忘录递归
	dp数组的迭代解法
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<unordered_map>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////1.背包问题//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/*
**0-1 背包问题 (0-1 knapsack problem)：**每种物品只有一个
**完全背包问题 (UKP, unbounded knapsack problem)：**每种物品都有无限个可用
**多重背包问题 (BKP, bounded knapsack problem)：**第 i 种物品有 n[i] 个可用

*/

//////////////1.1 0-1背包////////////////////
//有一个容量为 N 的背包，要用这个背包装下物品的价值最大，这些物品有两个属性：体积 w 和价值 v
int knapsack(int W, int N, vector<int>& wt, vector<int>& val) {
	//base case
	vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));	//定义dp数组，前i件物品体积不超过j的情况下最大价值

	for (int i = 1; i <= N; i++) {
		int w = wt[i - 1], v = val[i - 1];
		for (int j = 1; j <= W; j++) {
			if (j - w < 0)	dp[i][j] = dp[i - 1][j];
			else
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + v);
		}
	}
	return dp[N][W];
}

//空间优化
//dp[j] = max(dp[j], dp[j - w] + v);

int knapsack2(int W, int N, vector<int>& wt, vector<int>& val) {
	vector<int> dp(W + 1, 0);
	for (int i = 1; i <= N; i++) {
		int w = wt[i - 1],v = val[i - 1];
		for (int j = W; j >= w; j--) {
				dp[j] = max(dp[j], dp[j - w] + v);
		}
	}
	return dp[W];

}


////////////1.2 完全背包///////////////////////
////////////1.2.1 零钱兑换1///////////////////
///////////leetcode 322///////////////////////
int coinChange1(vector<int>& coins, int amount) {
	if (amount == 0)	return 0;
	vector<int> dp(amount + 1, amount + 1);	//总和为amount的最少硬币数
	
	dp[0] = 0;	

	for (int i = 1; i <= amount; i++) {
		for (int coin : coins) {
			if (i - coin < 0)	continue;
			dp[i] = min(dp[i], dp[i - coin] + 1);
		}
	}
	return dp[amount] == amount + 1 ? -1 : dp[amount];
}

/////////////1.2.2 零钱兑换2
//凑成固定数目的组合数
int coinChange(vector<int>& coins, int amount) {
	int n = coins.size();
	vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));	//n个硬币组合成amount数值的个数
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		dp[i][0] = 1;	//base case
		for (int j = 1; j < amount + 1; j++) {
			dp[i][j] = dp[i - 1][j] + (j >= coins[i - 1] ? dp[i][j - coins[i - 1]]:0);
		}
	}
	return dp[n][amount];
}

////////空间优化
int coinChange2(vector<int>& coins, int amount) {
	int n = coins.size();
	vector<long> dp(amount = 1, 0);
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = coins[i - 1]; j <= amount; j++) {
			dp[j] += dp[j - coins[i - 1]];
		}
	}
	return dp[amount];
}

//////////////1.3 多重背包//////////////////////////
//1.3.1 字符串构成最多的字符串——474
int findMaxForm(vector<string>& strs, int m, int n) {
	int s = strs.size();
	vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

	for (int i = 0; i < s; i++) {
		int zero = 0;
		int one = 0;
		//计算对应的string所含0 1 个数
		for (int j = 0; j < strs[i].size(); j++) {
			if (strs[i][j] == '0')	zero++;
			else one++;
		}
		//查看选取/不选取该string对应的dp最大值
		for (int i = m; i >= zero; i--) {
			for (int j = n; j >= one; j--) {
				dp[i][j] = max(dp[i][j], dp[i - zero][j - one] + 1);
			}
		}
	}
	return dp[m][n];
}

////1.3.2 单词拆分——139
bool wordBreak(string s, vector<string>& wordDict) {
	int n = s.size();
	vector<bool> dp(n + 1, false);
	dp[0] = true;
	for (int i = 1; i <= n; i++) {
		for (string word : wordDict) {
			int len = word.size();
			if (len <= i && s.substr(i - len, len) == word)
				dp[i] = dp[i] || dp[i - len];	//dp[0]  dp[len1] dp[len2] ...
		}
	}
	return dp[n];
}

////1.3.3 组合总和4
//给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数
int combinationSum4(vector<int>& nums, int target) {
	if (nums.size() == 0)	return 0;
	vector<unsigned int> dp(target + 1, 0);
	dp[0] = 1;

	for (int i = 0; i <= target; i++) {
		for (int j = 0; j < nums.size(); j++) {
			if (i - nums[j] > 0)
				dp[i] += dp[i - nums[j]];	//
		}
	}
	return dp[target];
}

////1.4 子集背包
//1.4.1 分割等和子集
bool canPartition(vector<int>& nums) {
	int sum = 0;
	for (int num : nums)	sum += num;
	if (sum % 2)	return false;
	int n = nums.size();
	sum = sum / 2;
	vector<vector<bool>>	dp(n + 1, vector<bool>(sum + 1, false));
	//base case
	for (int i = 0; i <= n; i++) {
		dp[i][0] = true;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= sum; j++) {
			if (j - nums[i - 1] < 0)
				dp[i][j] = dp[i - 1][j];	//背包容量不足
			else
				dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];	//装入或者不装入
		}
	}
	return dp[n][sum];
}

//////空间优化
int sum(vector<int>& nums) {
	int sum = 0;
	for (auto num : nums)
		sum += num;
	return sum;
}
bool canPartition1(vector<int>& nums) {
	int _sum = sum(nums);
	if (_sum == 0 || _sum & 1)	return false;
	_sum /= 2;
	vector<bool> dp(nums.size() + 1, false);
	dp[0] = true;
	for (int i = 1; i < nums.size(); i++) {
		for (int j = _sum; j >= nums[i]; j--) {
			dp[j] = dp[j] || dp[j - nums[i]];
			if (dp[j])	return true;
		}
	}
	return false;
}

//1.4.2 目标和
/*
给定一个非负整数数组，a1, a2, …, an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。
返回可以使最终数组和为目标数 S 的所有添加符号的方法数。

sum(P) - sum(N) = target
sum(P) -sum(N) + sum(P) + sum(N) = target + sum(P) + sum(N)
2*sum(P) = target + sum(nums)

*/
int findTargetSumWays(vector<int> nums, int s) {
	int _sum = sum(nums);
	if (_sum < s || (_sum + s) & 1)	return 0;

	int arr = (_sum + s) / 2;
	vector<int> dp(arr + 1, 0);
	dp[0] = 1;

	for (int num : nums) {
		for (int j = arr; j >= num; j--) {
			dp[j] = dp[j] + dp[j - num];
		}
	}
	return dp[arr];
}

//////递归方法
//前序遍历二叉树的实现，递归地+或-每个元素，到所有元素都遍历完成的时候，最后那个判断target是否等于零。
int findDfs(vector<int>& nums, int target, int left) {
	if (target == 0 && left == nums.size())	return 1;	//终止条件
	if (left >= nums.size())	return 0;
	int ans = 0;
	ans += findDfs(nums, target - nums[left], left + 1);
	ans += findDfs(nums, target + nums[left], left + 1);
	return ans;
}

int findTargetSumWays2(vector<int>& nums, int s) {
	return findDfs(nums, s, 0);
}



//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////2.打家劫舍//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//2.1 打家劫舍1
int rob1(vector<int>& nums) {
	int n = nums.size();
	if (n == 0)	return 0;
	if (n == 1)	return nums[0];
	vector<int> dp(n , 0);
	dp[0] = nums[0];
	dp[1] = max(nums[0], nums[1]);
	for (int i = 2; i < n; i++) {
		dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
	}
	return dp[n - 1];
}

////空间优化////
int rob1_(vector<int>& nums) {
	int n = nums.size();
	int pre = 0, cur = 0;
	for (int i = 0; i < n; i++) {
		int temp = max(pre + nums[i], cur);
		pre = cur;
		cur = temp;
	}
	return cur;
}


//2.2 打家劫舍2
int robCri(vector<int>& nums, int start, int end) {
	int pre = 0, cur = 0;
	for (int i = start; i <= end; i++) {
		int temp = max(pre + nums[i], cur);
		pre = cur;
		cur = temp;
	}
	return cur;
}

int rob2(vector<int>& nums) {
	int n = nums.size();
	if (n == 0)	return 0;
	if (n == 1)	return nums[0];
	return max(robCri(nums, 0, n - 2), robCri(nums, 1, n - 1));
}

//2.3 打家劫舍3
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

pair<int,int> robDfs(TreeNode* root) {
	if (root == NULL)	return { 0,0 };
	pair<int, int>	res(0, 0);	//first没抢，second抢了
	pair<int, int> left = robDfs(root->left);
	pair<int, int>  right = robDfs(root->right);

	res.first = max(left.first, left.second) + max(right.first, right.second);
	res.second = root->val + left.first + right.first;

	return res;
}

int rob3(TreeNode* root) {
	pair<int, int>	res = robDfs(root);
	return max(res.first, res.second);
}



//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////3.高楼扔鸡蛋 887//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//3.1 动态规划+二分搜索
/*
dp[a][b]: 当前k个鸡蛋，b层楼最少扔几次
时间复杂度：O(K∗NlogN)。我们需要计算 O(K * N) 个状态，每个状态计算时需要 O(logN) 的时间进行二分搜索。

空间复杂度：O(K∗N)。我们需要 O(K∗N) 的空间存储每个状态的解。
*/

int dpEggDrop(int K, int N,unordered_map<int,int>& memo) {
	//边界条件处理
	if (K == 1)	return N;
	if (N == 0)	return 0;
	if (memo.find(N * 100 + K) != memo.end())	return memo[N * 100 + K];

	//二分搜索降低时间复杂度
	int res = N;
	int lo = 1, hi = N;
	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		int broken = dpEggDrop(K - 1, mid - 1, memo);
		int not_broken = dpEggDrop(K, N - mid, memo);

		if (broken > not_broken) {
			hi = mid - 1;
			res = min(res, broken+1);
		}
		else {
			lo = mid + 1;
			res = min(res, not_broken + 1);
		}
	}
	//备忘录记录
	memo[N * 100 + K] = res;
	return res;

}

int superEggDrop(int K, int N) {
	unordered_map<int, int> memo;
	return dpEggDrop(K, N,memo);

}


//3.2 数学法
/*
dp[k][m] = n				k个鸡蛋可以尝试m次鸡蛋，最坏情况下最多测试n层楼
时间复杂度：O(KN)

空间复杂度：O(K∗N)->O(K)
*/

int superEggDrop2(int K, int N) {
	vector<vector<int>> dp(K + 1, vector<int>(N + 1, 0));
	int m = 0;
	//临界条件k个鸡蛋n层楼
	while (dp[K][m] < N) {
		m++;
		//状态转移
		for (int j = 1; j <= K; j++) {
			dp[j][m] = dp[j - 1][m - 1] + dp[j][m - 1] + 1;	//dp[j-1][m-1]摔碎了，测楼下    dp[j][m-1]没摔碎，测楼上
		}
	}
	return m;
}

////空间优化
int superEggDrop2_(int K, int N) {
	if (N == 0)	return 0;
	if (K==1)	return N;

	vector<int>	dp(K + 1, 0);
	int res = 0;
	for (; dp[K] < N; res++) { 
		for (int i = K; i > 0; i--) {
			dp[i] = dp[i - 1] + dp[i] + 1;
		}
	}
	return res;
}

// 3.3 决策单调性(没理解)
int superEggDrop3(int K, int N) {
	vector<int>  dp(N+1,0);
	for (int i = 0; i <= N; ++i) dp[i] = i;

	for (int k = 2; k <= K; ++k) {
		vector<int> dp2(N+1,0);
		int x = 1;
		dp2[0] = 0;
		for (int n = 1; n <= N; ++n) {
			while (x < n && max(dp[x - 1], dp2[n - x]) >= max(dp[x], dp2[n - x - 1])) x++;
			dp2[n] = 1 + max(dp[x - 1], dp2[n - x]);
		}
		for (int n = 1; n <= N; ++n) dp[n] = dp2[n];
	}
	return dp[N];
}



//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////4.最长递增子序列//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//4.1 最长上升子序列
/*
时间复杂度：O(N^2)
空间复杂度：O(N)
*/
int lengthOfLis(vector<int>& nums) {
	int n = nums.size();
	if (n == 0)	return 0;

	//base case
	vector<int> dp(n, 1);
	int res = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if(nums[j]<nums[i])
				dp[i] = max(dp[i], dp[j] + 1);
		}
		res = max(res, dp[i]);
	}
	return res;
}

////时间优化
int lengthOfLis_(vector<int>& nums) {
	int len = 1, n = nums.size();
	if (n == 0)	return 0;

	vector<int> dp(n + 1, 0);
	dp[len] = nums[0];
	
	for (int i = 1; i < n; i++) {
		if (nums[i] > dp[len])	dp[++len] = nums[i];
		else {
			//不递增则二分查找
			int l = 1, r = len, pos = 0;	//如果找不到说明所有数逗比nums[i]大，要更新 d[1]，所以这里将 pos 设为 0
			while (l <= r) {
				int mid = l + (r - l) / 2;
				if (dp[mid] < nums[i]) {
					pos = mid;
					l = mid + 1;
				}
				else r = mid - 1;
			}
			dp[pos + 1] = nums[i];
		}
	}
	return len;
}

//4.2 最长数对链
int findLongestChain(vector<vector<int>>& pairs) {
	if (pairs.empty())	return 0;

	//区间排序：按照右端点进行排序，若右端点不相等——从小到大；若相等左端点——从小到大
	sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
		return (a[1] < b[1] || (a[1] == b[1] && a[0] == b[0]));
		});

	int n = pairs.size();
	int res = 0;
	vector<int> dp(n, 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (pairs[j][1] < pairs[i][0]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		res = max(res, dp[i]);
	}
	return res;
}

////动态规划+二分查找
int findLongestChain_1(vector<vector<int>>& pairs) {
	if (pairs.empty())	return 0;

	//区间排序：按照右端点进行排序，若右端点不相等——从小到大；若相等左端点——从小到大
	sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
		return (a[1] < b[1] || (a[1] == b[1] && a[0] == b[0]));
		});

	vector<vector<int>> dp;
	for (auto& p : pairs) {
		//二分查找>=p[0]的最小值dp[i][1]
		int left = 0, right = dp.size();
		while (left < right) {
			int mid = left + ((right - left) >> 1);
			if (dp[mid][1] >= p[0])	right = mid;
			else left = mid + 1;
		}
		//dp[size-1][1] <p[0]   update
		if (left >= dp.size())	dp.emplace_back(p);
		else if (dp[left][1] > p[1])	dp[left] = p;
	}
	return dp.size();
}

////区间贪心法
int findLongestChain_2(vector<vector<int>>& pairs) {
	if (pairs.empty())	return 0;

	//区间排序：按照右端点进行排序，若右端点不相等——从小到大；若相等左端点——从小到大
	sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
		return (a[1] < b[1] || (a[1] == b[1] && a[0] == b[0]));
		});

	int cnt = 1, end = pairs[0][1];

	for (const auto& p : pairs) {
		if (p[0] > end) {//区间不相交，需要更新边界以及不重复区间个数，注意不能有等号，即区间端点不能连续
			cnt++;
			end = p[1];
		}
	}
	return cnt;
}

//4.3 摆动序列
int wiggleMaxLength(vector<int>& nums) {
	if (nums.size() == 0) 		return 0;

	int n = nums.size();
	vector<int> up(n, 1);
	vector<int> down(n, 1);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++)
			if (nums[j] > nums[i])
				down[i] = max(down[i], up[j] + 1);
			else if (nums[j] < nums[i])
				up[i] = max(up[i], down[j] + 1);
	int ret = 1;
	for (int i = 0; i < n; i++) {
		ret = max(ret, down[i]);
		ret = max(ret, up[i]);
	}
	return ret;
}

//空间优化
int wiggleMaxLength_(vector<int>& nums) {
	if (nums.size() == 0) {
		return 0;
	}
	int up = 1, down = 1;
	for (int i = 1; i < nums.size(); i++) {
		if (nums[i] > nums[i - 1]) {
			up = down + 1;
		}
		else if (nums[i] < nums[i - 1]) {
			down = up + 1;
		}
	}
	return max(up, down);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////5.最长公共子序列//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/////迭代法
int longestDfs(string& s1, string& s2,int a,int b,vector<vector<int>>& dp) {
	//int a = s1.size(), b = s2.size();
	if (a == 0 || b == 0)	return 0;
	if (dp[a][b] != -1)		return dp[a][b];

	dp[a][b] = max(longestDfs(s1, s2,a-1,b,dp), longestDfs(s1, s2,a,b, dp));
	//动态规划
	if (s1[a - 1] == s2[b - 1])
		dp[a][b] = max(longestDfs(s1, s2, a - 1, b - 1, dp) + 1, dp[a][b]);
	return dp[a][b];
}


int longestCommSubsequence(string text1, string text2) {
	vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, -1));

	return longestDfs(text1, text2,text1.size()-1,text2.size()-1, dp);
}

////自底向上，动态规划
int longestCommSubsequence_(string text1, string text2) {
	int a = text1.size(), b = text2.size();
	vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));

	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			if (text1[i - 1] == text2[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[a][b];
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////6.字符串编辑//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//6.1 删除两个字符串的字符使其相等
/*
求两个字符串的最长公共子序列
*/
int minDistance(string text1, string text2) {
	int a = text1.size(), b = text2.size();
	vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));

	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			if (text1[i - 1] == text2[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return a+b -2*dp[a][b];
}

//6.2 编辑距离——（最少插入、删除、替换）
int minDistanceB(string s1, string s2) {
	int a = s1.size(), b = s2.size();
	vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));

	for (int i = 0; i <= a; i++)	dp[i][0] = i;
	for (int i = 0; i <= b; i++)	dp[0][i] = i;

	for (int i = 1; i <= a; i++) {
		for (int j = 1; j <= b; j++) {
			if (s1[i - 1] == s2[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
		}
	}
	return dp[a][b];
}


//6.3 复制粘贴
int minSteps(int n) {
	vector<int> dp(n + 1, 0);
	for (int i = 2; i <= n; i++) {
		int minCount = INT_MAX;
		for (int j = 1; j < i; j++) {
			if (i % j == 0)
				minCount = min(dp[j] + i / j, minCount);	//复制+粘贴==i/j
		}
		dp[i] = minCount;
	}
	return dp[n];
}




//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////7.矩阵路径//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//7.1 最小路径和
int minPathSum(vector<vector<int>>& grid) {
	int m = grid.size();
	if (m == 0)	return 0;
	int n = grid[0].size();

	vector<vector<int>> dp(m, vector<int>(n, 0));
	dp[0][0] = grid[0][0];
	for (int i = 1; i < m; i++)	dp[i][0] = dp[i - 1][0] + grid[i][0];
	for (int i = 1; i < n; i++)	dp[0][i] = dp[0][i-1] + grid[0][i];

	for (int i = 1; i < m; i++) {
		for (int j = 1; i < n; j++) {
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
		}
	}
	return dp[m - 1][n - 1];
}

////空间优化
int minPathSum_(vector<vector<int>>& grid) {
	int m = grid.size(), n = grid[0].size();
	vector<int> dp = grid[0];
	for (int j = 1; j < n; ++j)            dp[j] += dp[j - 1];

	for (int i = 1; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (j == 0) 		dp[j] = dp[j] + grid[i][j];
			else 				dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
		}
	}
	return dp[n - 1];
}

//7.2 解码方法——分割整数构成字母字符串
int numDecoding(string s) {
	if (s[0] == '0')	return 0;
	int pre = 1, cur = 1;
	for (int i = 1; i < s.size(); i++) {
		int temp = cur;
		if (s[i] == '0'){
			if(s[i-1]=='1'|| s[i-1]=='2')	cur = pre;
			else return 0;
		}
		else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6')) {
			cur += pre;
		}
		pre = temp;
	}
	return cur;
}



