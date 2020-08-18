#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<unordered_map>
using namespace std;

///////////////////////////////////////////////////////////////////
//////////////////////1. BFS//////////////////////////////////////////
///////////////////////////////////////////////////////////////////

/*
在程序实现 BFS 时需要考虑以下问题：
	队列：用来存储每一轮遍历得到的节点；
	标记：对于遍历过的节点，应该将它标记，防止重复遍历。
*/
////1.1 二进制矩阵中的最短路径_1091////////////////////
vector<vector<int>> dir = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1} };

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
	int n = grid.size();
	if (n == 0 || grid[0][0] || grid[n - 1][n - 1])	return -1;

	queue<pair<int, int>>	q;
	q.push(make_pair(0, 0));
	int length = 1;
	grid[0][0] = 2;	//访问过的节点标记为2
	while (!q.empty()) {
		int len = q.size();
		for (int i = 0; i < len; i++) {
			int x = q.front().first;
			int y = q.front().second;
			q.pop();
			if (x == n - 1 && y == n - 1)	return length;

			for (int j = 0; j < 8; j++) {
				int x1 = x + dir[j][0];
				int y1 = y + dir[j][1];
				if (x1 < 0 || y1 < 0 || x1 >= n || y1 >= n || grid[x1][y1])
					continue;
				grid[i][j] = 2;
				q.push(make_pair(x1, y1));
			}
		}
		length++;
	}
	return -1;
}

///1.2 组成整数的最小平方数数量_279/////////////////////////

int numSquares(int n) {
	int min_n = sqrt(n);
	queue<int>	q;
	q.push(0);
	int step = 0;
	while (!q.empty()) {
		step++;
		int len = q.size();
		for (int i = 0; i < len; i++) {
			int front = q.front();
			q.pop();
			for (int j = min_n; j >= 1; j--) {
				int sum = front + pow(j, 2);
				if (sum == n)	return step;
				if (sum > n)	continue;
				q.push(sum);
			}
		}
	}
	return -1;
}

///////////////////////1.3 最短单词路径_127/////////////////////////
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
	unordered_map<string, int>	freqs;
	for (const auto& word : wordList)
		freqs[word] = 0;
	if (freqs.count(endWord) == 0)	return 0;
	queue<string> q1({ beginWord }), q2({ endWord });
	int step = 1;
	for (freqs[beginWord] != 1, freqs[endWord] != 2; q1.size() && q2.size(); ++step) {
		bool first = q1.size() < q2.size();
		queue<string>& q = first ? q1 : q2;
		int flag = first ? 1 : 2;
		for (int size = q.size(); size--; q.pop()) {
			string& word = q.front();
			if (freqs[word] == 3)	return step;
			for (int i = 0; i < word.size(); i++) {
				for (char ch = 'a'; ch < 'z'; ch++) {
					string s = word;
					if (s[i] == ch)	continue;
					s[i] = ch;
					if (freqs.count(s) == 0 || freqs[s] & flag)	continue;
					freqs[s] |= flag;
					q.push(s);
				}
			}
		}
	}
	return -1;
}



////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////2.DFS///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
/*
在程序实现 DFS 时需要考虑以下问题：

	栈：用栈来保存当前节点信息，当遍历新节点返回时能够继续遍历当前节点。可以使用递归栈。
	标记：和 BFS 一样同样需要对已经遍历过的节点进行标记。

*/

//2.1 岛屿的最大面积_695
int dict1[] = { 0,0,1,-1 };
int dict2[] = { 1,-1,0,0 };

int areaDfs(vector<vector<int>>& grid, int row, int column, int r, int c) {
	if (r < 0 || c < 0 || r >= row || c >= column || grid[r][c] != 1)	return 0;
	int ans = 1;
	grid[r][c] = 2;
	for (int i = 0; i < 4; i++) {
		ans += areaDfs(grid, row, column, r + dict1[i], c + dict2[i]);
	}
	return ans;
}


int maxAreaOfIsland(vector<vector<int>>& grid) {
	int row = grid.size();
	if (row == 0)	return 0;
	int column = grid[0].size();
	int ans = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			if (grid[i][j] == 1)	ans = max(ans, areaDfs(grid, row, column, i, j));
		}
	}
	for (int i = 0; i < row; i++) 
		for (int j = 0; j < column; j++)
			if (grid[i][j] == 2)	grid[i][j] = 1;
	
		return ans;
}



//2.2 岛屿数量_200////////////////
void numDfs(vector<vector<int>>& grid, int row, int column) {
	if (row < 0 || column < 0 || row == grid.size() || column == grid[0].size() || grid[row][column] != '1') return;

	grid[row][column] = '#';
	for (int i = 0; i < 4; i++) {
		numDfs(grid, row + dict1[i], column + dict2[i]);
	}
	return;
}



int numIslands(vector<vector<int>>& grid) {
	int ans = 0;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[0].size(); j++) {
			if (grid[i][j] == 1) {
				ans++;
				numDfs(grid, i, j);
			}
		}
	}
	return ans;
}

//////并查集
class UnionFind {
public:
	UnionFind(vector<vector<char>>& grid) {
		count = 0;
		int m = grid.size();
		int n = grid[0].size();
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (grid[i][j] == '1') {
					parent.push_back(i * n + j);
					++count;
				}
				else parent.push_back(-1);
				rank.push_back(0);
			}
		}
	}

	int find(int i) { // path compression
		if (parent[i] != i) parent[i] = find(parent[i]);
		return parent[i];
	}

	void Union(int x, int y) { // union with rank
		int rootx = find(x);
		int rooty = find(y);
		if (rootx != rooty) {
			if (rank[rootx] > rank[rooty]) parent[rooty] = rootx;
			else if (rank[rootx] < rank[rooty]) parent[rootx] = rooty;
			else {
				parent[rooty] = rootx; rank[rootx] += 1;
			}
			--count;
		}
	}

	int getCount() const {
		return count;
	}

private:
	vector<int> parent;
	vector<int> rank;
	int count; // # of connected components
};

class Solution {
public:
	int numIslands(vector<vector<char>>& grid) {
		int nr = grid.size();
		if (!nr) return 0;
		int nc = grid[0].size();

		UnionFind uf(grid);
		int num_islands = 0;
		for (int r = 0; r < nr; ++r) {
			for (int c = 0; c < nc; ++c) {
				if (grid[r][c] == '1') {
					grid[r][c] = '0';
					if (r - 1 >= 0 && grid[r - 1][c] == '1') uf.Union(r * nc + c, (r - 1) * nc + c);
					if (r + 1 < nr && grid[r + 1][c] == '1') uf.Union(r * nc + c, (r + 1) * nc + c);
					if (c - 1 >= 0 && grid[r][c - 1] == '1') uf.Union(r * nc + c, r * nc + c - 1);
					if (c + 1 < nc && grid[r][c + 1] == '1') uf.Union(r * nc + c, r * nc + c + 1);
				}
			}
		}

		return uf.getCount();
	}
};



/////2.3 朋友圈_547/////////////////////////////
void numDfs(vector<vector<int>>& M, int i, vector<bool>& visit) {
	visit[i] = true;
	for (int j = 0; j < M.size(); j++) {
		if (M[i][j] == 1 && !visit[j])
			numDfs(M, j, visit);
	}
}


int findCircleNum(vector<vector<int>>& M) {
	int n = M.size();
	int num = 0;
	vector<bool>	visit(n, false);
	for (int i = 0; i < n; i++) {
		if (!visit[i]) {
			num++;
			numDfs(M, i, visit);
		}
	}
	return num;
}



///////////////////2.4 被围绕的区域_130////////////////////
void solveDfs(vector<vector<char>>& board, int i, int j) {
	if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || board[i][j] != '0')	return;
	board[i][j] = 'T';
	for (int k = 0; k < 4; k++)
		solveDfs(board, i + dict1[i], j + dict2[i]);
}
void solve(vector<vector<char>>& board) {
	int m = board.size();
	if (m < 3)	return;
	int n = board[0].size();
	if (n < 3)	return;

	for (int i = 0; i < m; i++) {
		solveDfs(board, i, 0);
		solveDfs(board, i, n - 1);
	}
	for (int i = 0; i < n; i++) {
		solveDfs(board, 0,i);
		solveDfs(board, m-1,i);
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == 'T')    board[i][j] = 'O';
			else if (board[i][j] == 'O')   board[i][j] = 'X';
		}
	}
	return;
}


/////////////////////2.5 太平洋大西洋_417//////////////////////
void paDfs(vector<vector<int>>& matrix,int i,int j,vector<vector<bool>>& canReach) {
	if (canReach[i][j])	return;
	canReach[i][j] = true;
	for (int k = 0; k < 4; k++) {
		int next_x = i + dict1[k], next_y = j + dict2[k];
		if (next_x < 0 || next_y<0 || next_x >= matrix.size() || next_y >= matrix[0].size() || matrix[i][j]>matrix[next_x][next_y])	continue;
		paDfs(matrix, next_x, next_y, canReach);
	}
}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
	int m = matrix.size();
	if (m == 0)    return matrix;
	int n = matrix[0].size();

	vector<vector<int>> path;
	vector<vector<bool>>	canP(m, vector<bool>(n, false)), canA(m, vector<bool>(n, false));

	for (int i = 0; i < m; i++) {
		paDfs(matrix, i, 0, canP);
		paDfs(matrix, i, n - 1, canA);
	}
	for (int i = 0; i < n; i++) {
		paDfs(matrix, 0, i, canP);
		paDfs(matrix, m-1, i, canA);
	}

	for (int i = 0; i < m; i++) {
		for (int j = n-1; j >= 0; j--) {
			if (canA[i][j] && canP[i][j])
				path.push_back({ i,j });
		}
	}
	return path;

}


//////////////////////3.回溯////////////////////////////////
/*
在访问一个新元素进入新的递归调用时，需要将新元素标记为已经访问
但是在递归返回时，需要将元素标记为未访问

*/

//3.1 电话号码的数字组合_17
vector<string> table = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };

void letterDfs(const string& digits,string& str, int index,vector<string>& res) {
	if (index = digits.size()) {
		res.push_back(str);
		return;
	}

	string s = table[digits[index] - '2'];
	for (auto c : s) {
		str.push_back(c);
		letterDfs(digits, str, index + 1, res);
		str.pop_back();
	}
}
vector<string> letterCombinations(string digits) {
	vector<string> res;
	string str;
	if (digits.size() == 0)	return res;

	letterDfs(digits, str, 0, res);
	return res;
}


///////////////////////////3.2 IP地址划分_93
bool isValidIP(string ip) {
	int num = stoi(ip);
	if (num > 255)	return false;
	if (ip.size() >= 2 && ip[0] == '0')	return false;
	return true;

}

void ipDfs(string& s, int index,vector<string>& path, vector<string>& res) {
	//剪枝
	int maxLen = (4 - path.size()) * 3;
	if (s.size() - index > maxLen)	return;
	//输入结果
	if (path.size() == 4 && index == s.size()) {
		string temp = "";
		for (int i = 0; i < 3; i++) {
			temp += path[i];
			temp += ".";
		}
		temp += path[3];
		res.push_back(temp);
		return;
	}
	for (int i = index; i < s.size(); i++) {
		string ip = s.substr(index, i - index + 1);
		if (!isValidIP(ip))	continue;
		path.push_back(ip);
		ipDfs(s, i + 1, path, res);
		path.pop_back();
	}
}

vector<string> restoreIpAddresses(string s) {
	vector<string> res;
	vector<string> path;
	if (s.size() < 4)	return res;
	ipDfs(s, 0,path, res);
	return res;
}

//3.3 单词搜索_79
int dit[4][2] = { 1,0,-1,0,0,1,0,-1 };

bool existDfs(vector<vector<char>>& board, vector<vector<bool>>& visit, string& word, int index, int i, int j) {
	if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size()|| visit[i][j])   return false;
	if (board[i][j] != word[index])       return false;
	if (word.size() - 1 == index)           return true;
	visit[i][j] = true;
	index++;
	for (auto d : dit) {
		if (existDfs(board, visit, word, index, i + d[0], j + d[1]))   return true;
	}
	visit[i][j] = false;
	return false;
}

bool exist(vector<vector<char>>& board, string word) {
	int m = board.size();
	int n = board[0].size();
	if (m == 0 || n == 0)	return false;
	vector<vector<bool>> visit(m, vector<bool>(n, false));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == word[0]) {
				if (existDfs(board, visit, word, 0, i, j))
					return true;
			}
		}
	}
	return false;

}

//3.4 二叉树的所有路径_257
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) :val(x), left(NULL), right(NULL) {}
};

void backtrack(TreeNode* root,string& path,vector<string>& res) {
	if (!root) return;
	int len = path.size();                          // 记录初始状态（记住长度）
	path += (path.empty() ? "" : "->") + to_string(root->val);  // 改变状态（增加长度）
	if (!root->left && !root->right) res.push_back(path);       // 符合条件则添加至 res
	else backtrack(root->left, path, res), backtrack(root->right, path, res);         // 否则递归进入左右子树
	path.erase(path.begin() + len, path.end());     // 恢复初始状态（擦去新增的长度）
}

vector<string> binaryTreePaths(TreeNode* root) {
	vector<string> res;
	string path;
	backtrack(root,path,res);
	return res;
}

////3.5 全排列_46
void permuteDfs(vector<int>& nums, vector<vector<int>>& res, vector<int>& path, vector<bool>& visit) {
	if (path.size() == nums.size()) {
		res.push_back(path);
		return;
	}

	for (int i = 0; i < nums.size(); i++) {
		if (visit[i])	continue;
		path.push_back(nums[i]);
		visit[i] = true;
		permuteDfs(nums, res, path, visit);
		visit[i] = false;
		path.pop_back();
	}
}


vector<vector<int>> permute(vector<int>& nums) {
	vector<vector<int>> res;
	vector<int> path;
	vector<bool> visit(nums.size(), false);
	permuteDfs(nums, res, path,visit);
	return res;
}

//3.6 全排列2_47

void permuteUniqueDfs(vector<int>& nums, vector<vector<int>>& res, vector<int>& path, vector<bool>& visit) {
	if (path.size() == nums.size()) {
		res.push_back(path);
		return;
	}

	for (int i = 0; i < nums.size(); i++) {
		if (visit[i])	continue;
		if (i != 0 && nums[i] == nums[i - 1] && !visit[i-1])	continue;
		path.push_back(nums[i]);
		visit[i] = true;
		permuteDfs(nums, res, path, visit);
		visit[i] = false;
		path.pop_back();
	}
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
	vector<vector<int>> res;
	vector<int> path;
	vector<bool> visit(nums.size(), false);
	sort(nums.begin(), nums.end());
	permuteUniqueDfs(nums, res, path, visit);
	return res;
}

//3.7 组合_77
void combineDfs(int n, int k, int index, vector<int>& path,vector<vector<int>>& res) {
	if (k==0) {
		res.push_back(path);
		return;
	}

	for (int i = index; i <=n-k+1; i++) {
		path.push_back(i);
		combineDfs(n, k - 1, i + 1, path, res);
		path.pop_back();
	}
}


vector<vector<int>> combine(int n, int k) {
	vector<vector<int>> res;
	vector<int>	path;
	if (n <= 0 || k <= 0 || n < k)	return res;

	combineDfs(n, k, 1,path,res);

	return res;

}

//3.8 组合总和_39

void sumDfs(vector<vector<int>>& res, vector<int>& path, vector<int>& candidates, int target, int index) {
	if (target == 0) {
		res.push_back(path);
		return;
	}

	for (int i = index; i < candidates.size(); i++) {
		if (candidates[i] <= target) {
			path.push_back(candidates[i]);
			sumDfs(res, path, candidates, target - candidates[i], i);
			path.pop_back();
		}
	}
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int>>  res;
	vector<int>  path;
	sumDfs(res, path, candidates, target, 0);
	return res;
}

//3.9 组合总和2_40
void sumDfs2(vector<vector<int>>& res, vector<int>& path, vector<int>& candidates, int target, int index) {
	if (target == 0) {
		res.push_back(path);
		return;
	}

	for (int i = index; i < candidates.size(); i++) {
		if (i != 0 && candidates[i] == candidates[i - 1])	continue;
		if (candidates[i] <= target) {
			path.push_back(candidates[i]);
			sumDfs(res, path, candidates, target - candidates[i], i+1);
			path.pop_back();
		}
	}
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
	vector<vector<int>>  res;
	vector<int>  path;
	sort(candidates.begin(), candidates.end());
	sumDfs2(res, path, candidates, target, 0);
	return res;
}

//3.10 组合总和3_216
void sumDfs3(vector<vector<int>>& res, vector<int>& path, int k, int target, int index) {
	if (target == 0 && k==0) {
		res.push_back(path);
		return;
	}

	for (int i = index; i <= 9; i++) {
		if (i <= target && k>0) {
			path.push_back(i);
			sumDfs3(res, path,k-1, target - i, i + 1);
			path.pop_back();
		}
	}
}

vector<vector<int>> combinationSum3(int k, int n) {
	vector<vector<int>>  res;
	vector<int>  path;
	sumDfs3(res, path, k, n, 1);
	return res;
}


//3.10 子集_78
void subSetsDfs(vector<int>& nums, vector<int>& path, vector<vector<int>>& res, int index) {
	if (path.size() > nums.size())	return;
	res.push_back(path);
	for (int i = index; i < nums.size(); i++) {
		path.push_back(nums[i]);
		subSetsDfs(nums, path, res, i + 1);
		path.pop_back();
	}
}

vector<vector<int>> subsets(vector<int>& nums) {
	vector<int> path;
	vector<vector<int>> res;
	subSetsDfs(nums,path,res,0);
	return res;
}

//3.11 子集2_90
void subDfs(vector<int>& nums, vector<int>& path, vector<vector<int>>& res, int index) {
	if (path.size() > nums.size())	return;
	res.push_back(path);
	for (int i = index; i < nums.size(); i++) {
		if (i>index && nums[i] == nums[i - 1])	continue;
		path.push_back(nums[i]);
		subSetsDfs(nums, path, res, i + 1);
		path.pop_back();
	}
}


vector<vector<int>> subsetsWithDup(vector<int>& nums) {
	vector<int> path;
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());
	subDfs(nums, path, res, 0);
	return res;
}

//3.12 分割回文串_131

bool IsPalindrome(const string& s)
{
	for (int i = 0; i < s.size() / 2; ++i)
	{
		if (s[i] != s[s.size() - i - 1])
			return false;
	}
	return true;
}

void partitionDfs(const string& s, int index, vector<string>& tmp, vector<vector<string>>& res)
{
	if (index >= s.size())
	{
		res.push_back(tmp);
	}
	string temp;
	for (int i = index; i < s.size(); ++i)
	{
		temp.push_back(s[i]);
		if (IsPalindrome(temp))
		{
			tmp.push_back(temp);
			partitionDfs(s, i + 1, tmp, res);
			tmp.pop_back();
		}
	}
}


vector<vector<string>> partition(string s) {
	vector<vector<string>> res;
	vector<string> tmp;
	partitionDfs(s, 0, tmp, res);
	return res;
}

//3.13 解数独_37
void backtrace(vector<vector<char>>& board,vector<vector<int> >& rows,vector<vector<int> >& cols,
	vector<vector<int> >& cells,int i, int j, bool& done,vector<vector<char>>& res) {
	if (done) return;
	if (i * 9 + j == 81) {
		done = true;
		res = board;
		return;
	}
	int k = i / 3 * 3 + j / 3;
	int t = i * 9 + j + 1;
	int r = t / 9;
	int c = t % 9;
	if (board[i][j] != '.') {
		backtrace(board, rows, cols, cells, r, c, done, res);
		return;
	}
	for (int u = 1; u <= 9; ++u) {
		if (rows[i][u] != 1 && cols[j][u] != 1 && cells[k][u] != 1) {
			rows[i][u] = cols[j][u] = cells[k][u] = 1;
			board[i][j] = u + '0';
			backtrace(board, rows, cols, cells, r, c, done, res);
			rows[i][u] = cols[j][u] = cells[k][u] = 0;
			board[i][j] = '.';
		}
	}
}
void solveSudoku(vector<vector<char>>& board) {
	const int N = 10;
	vector<vector<int> > rows(N, vector<int>(N, 0));
	vector<vector<int> > cols(N, vector<int>(N, 0));
	vector<vector<int> > cells(N, vector<int>(N, 0));
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (board[i][j] == '.') continue;
			int n = board[i][j] - '0';
			int k = i / 3 * 3 + j / 3;
			cells[k][n] = 1;
			rows[i][n] = 1;
			cols[j][n] = 1;
		}
	}
	vector<vector<char> > res(board);
	bool done = false;
	backtrace(board, rows, cols, cells, 0, 0, done, res);
	swap(res, board);
}

//3.14 N皇后_51
	bool isQueenOK(vector<string>& grid, int row, int col)
	{
		// 按照横向遍历的，所以横向一定是合法的，纵向合法性校验
		for (int i = 0; i < row; i++) {
			if (grid[i][col] == 'Q') return false;
		}
		// 主对角线合法性校验
		int x = row;
		int y = col;
		while ((--x) >= 0 && (--y) >= 0) {
			if (grid[x][y] == 'Q') return false;
		}
		// 副对角线合法性校验
		x = row;
		y = col;
		while ((--x) >= 0 && (++y) < grid.size()) {
			if (grid[x][y] == 'Q') return false;
		}
		return true;
	}

	void queenDFS(vector<vector<string>>& ans, vector<string>& grid, int index, int n)
	{
		if (index == n) {
			// 输出数据
			ans.push_back(grid);
			return;
		}
		for (int i = 0; i < n; i++) {
			// 检查(index, i)位是否能放Q
			if (isQueenOK(grid, index, i)) {
				grid[index][i] = 'Q';
				queenDFS(ans, grid, index + 1, n);
				grid[index][i] = '.';
			}
		}
	}
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> ans;
		string s;
		for (int i = 0; i < n; i++) 
			s += '.';
		vector<string> grid(n, s);
		queenDFS(ans, grid, 0, n);
		return ans;
	}
