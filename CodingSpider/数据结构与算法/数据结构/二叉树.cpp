#include <iostream>
#include<vector>
#include<stack>
#include<math.h>
#include<algorithm>
#include<queue>
using namespace std;


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(NULL),right(NULL){}
};



/////////////////////////////////////////////////////////
//////////////////1、递归遍历////////////////////////////
/////////////////////////////////////////////////////////
void preorder(TreeNode* root, vector<int>& path) {
	if (root == NULL)	return;
	path.push_back(root->val);
	preorder(root->left, path);
	preorder(root->right, path);
}

void inorder(TreeNode* root, vector<int>& path) {
	if (root == NULL)	return;
	
	inorder(root->left, path);
	path.push_back(root->val);
	inorder(root->right, path);
}

void postorder(TreeNode* root, vector<int>& path) {
	if (root == NULL)	return;

	postorder(root->left, path);
	postorder(root->right, path);
	path.push_back(root->val);
}

//////////////////////////////////////////////////////
//////////////////2、非递归遍历//////////////////////////
//////////////////////////////////////////////////////

vector<int> preorder(TreeNode* root) {
	vector<int> path;
	if (root == NULL)	return path;

	stack<TreeNode*> s;
	s.push(root);
	while (!s.empty()) {
		TreeNode* temp = s.top();
		s.pop();
		path.push_back(temp->val);
		if (temp->right)	s.push(temp->right);
		if (temp->left)		s.push(temp->left);
	}
	return path;
}

vector<int> inorder(TreeNode* root) {
	vector<int> path;
	if (root == NULL)	return path;

	stack<TreeNode*> s;
	TreeNode* p = root;
	while (p || !s.empty()) {
		if (p) {
			s.push(p);		//入栈
			p = p->left;	//指向下一个左节点
		}
		else {	//左节点为空时
			p = s.top();
			path.push_back(p->val);	//访问栈顶元素
			s.pop();		//出栈
			p = p->right;	//指向右节点
		}
	}
	return path;
}

vector<int> postorder(TreeNode* root) {
	vector<int> path;
	if (root == NULL)	return path;

	stack<TreeNode*> s;
	s.push(root);

	while (!s.empty()) {
		TreeNode* temp = s.top();
		s.pop();
		path.push_back(temp->val);
		if (temp->left)		s.push(temp->left);
		if (temp->right)	s.push(temp->right);
	}

	reverse(path.begin(), path.end());
	return path;
}

/////////////////////////////////////////////////////
//////////////3、重建二叉树/////////////////////////////
/////////////////////////////////////////////////////
TreeNode* orderTree(vector<int>& preTree, vector<int>& inTree, int index, int start, int end) {

	if (start >= end)	return nullptr;

	int i = start;
	TreeNode* temp = new TreeNode(preTree[index]);
	while (i < end && preTree[start] != inTree[i])	i++;
	if (i > start)	temp->left = orderTree(preTree, inTree, index + 1, start, i - 1);
	if (i < end)	temp->right = orderTree(preTree, inTree, index + 1 + i - start, i + 1, end);
	return temp;

}

TreeNode* oringalTree(vector<int>& preTree, vector<int>& inTree) {
	if (preTree.size() == 0 || preTree.size() != inTree.size())	return nullptr;

	return orderTree(preTree, inTree, 0, 0, preTree.size() - 1);

}

/////////////////////////////4、判断二叉搜索树后序遍历是否合法/////////////////////////////////////////////
bool VerifySquenceOfBST(vector<int>& sequence, int length) {
	if (length <= 0)	return false;
	int root = sequence[length - 1];
	int i = 0;
	//在二叉搜索树中左子树的节点小于根节点
	for (; i < length - 1; i++) {
		if (sequence[i] > root) {
			break;
		}
	}

	//在二叉搜索树中右子树的节点大于根节点
	int j = i;
	for (; j < length - 1; j++) {
		if (sequence[j] < root) {
			return false;
		}
	}

	//判断左子树是不是二叉搜索树BST
	bool left = true;
	if (i > 0)
		left = VerifySquenceOfBST(sequence, i);
	bool right = true;
	if (i < length - 1)
		vector<int> temp(sequence.begin() + i, sequence.end());
		right = VerifySquenceOfBST(sequence, length - 1 - i);

	return left && right;
}

/////////////////////////5、二叉树中和为某一值的路径////////////////////////
void dfs(TreeNode* tree, int target, vector<int> path,vector<vector<int>> res) {
	if (tree == NULL)	return;
	target -= tree->val;
	path.push_back(tree->val);
	if (tree->left && tree->right && !target)	res.push_back(path);
	dfs(tree->left, target, path, res);
	dfs(tree->right, target, path, res);
	path.pop_back();

}

vector<vector<int>> findPath(TreeNode* tree, int target) {
	vector<int> path;
	vector<vector<int>>		res;
	if (tree==NULL)			return res;
	dfs(tree, target,path,res);
	return res;
}


//////////////////////////6、二叉搜索树转为双向链表////////////////////////

/////////////方法1///////////////////////////////////
void inroder1(TreeNode* root, vector<TreeNode*> path) {
	if (root == NULL)	return;
	inroder1(root->left, path);
	path.push_back(root);
	inroder1(root->right, path);
}

TreeNode* treeToDoublyList(TreeNode* root) {
	if (root == NULL)	return root;
	vector<TreeNode*> path;
	inroder1(root,path);
	for (int i = 0; i < path.size()-1; i++) {
		path[i]->right = path[i + 1];
		path[i+1]->left = path[i];
	}
	path[0]->left = path[path.size() - 1];
	path[path.size() - 1]->right = path[0];
	return path[0];
}
//////////////方法2///////////////////////////////
void inorder2(TreeNode* root,TreeNode* pre,TreeNode* head) {
	if (root == NULL)return;
	inorder2(root->left,pre,head);
	if (pre == NULL)head = root;
	else pre->right = root;
	root->left = pre;
	pre = root;
	inorder2(root->right,pre,head);
}

TreeNode* treeToDoublyList2(TreeNode* root) {
	TreeNode* pre=NULL, * head=NULL;
	if (root == NULL)return NULL;
	inorder2(root,pre,head);
	head->left = pre;
	pre->right = head;
	return head;
}




///////////////////////////7、求二叉树的深度////////////////////
int maxDepth(TreeNode* root) {
	if (root == NULL)	return 0;
	return 1 + max(maxDepth(root->left), maxDepth(root->right));
}



/////////////////////////8、判断是否是二叉平衡树////////////////
int getHeight(TreeNode* root) {
	if (root == NULL)	return 0;
	int lt = getHeight(root->left);
	int rt = getHeight(root->right);
	return max(lt,rt)+1;
}


/*
使用后序遍历的方式遍历二叉树的每个节点，那么在遍历到一个节点之前我们就已经
遍历了它的左右子树。只要在每个节点的时候记录它的深度(某一节点的深度等于它到叶节点的路径的长度）
就可以判断每个节点是不是平衡的
*/
bool isBalanced(TreeNode* root, int& pDepth) {
	if (root == nullptr) { pDepth = 0; return true; }
	int left = 0, right = 0;
	if (isBalanced(root->left, left) && isBalanced(root->right, right))
	{
		int diff = left - right;
		if (abs(diff) <= 1)
		{
			pDepth = 1 + max(left,right);
			return true;
		}
	}
	return false;
}

bool isBalancedTree(TreeNode* root) {
	if (root == NULL)	return true;
	/*
	int depth = 0;
	return isBalanced(root, depth);
	*/
	if (abs(getHeight(root->left) - getHeight(root->right)) > 1)	return false;
	return isBalancedTree(root->left) && isBalancedTree(root->right);
}


///////////////////////////9、二叉树第k层节点个数///////////////////////////////
int GetNodeNumKLevel(TreeNode* root, int k) {
	if (root == NULL || k < 1)	return 0;
	if (k == 1)	return 1;
	int numLeft = GetNodeNumKLevel(root->left, k - 1);
	int numRight = GetNodeNumKLevel(root->right, k - 1);
	return (numLeft + numRight);
}


//////////////////////10、两个节点的最低公共祖先节点////////////////////////////
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (root == NULL)	return root;
	if (p == root || q == root)	return root;

	TreeNode* lt = lowestCommonAncestor(root->left, p, q);
	TreeNode* rt = lowestCommonAncestor(root->right, p, q);

	if (!lt)   return rt;
	if (!rt)  return lt;
	return root;
}


///////////////////////11、求二叉树中两个节点的最大距离///////////////////////////

int GetMaxDistance(TreeNode* root, int& res) {
	if (root == NULL)  return 0;

	int l = GetMaxDistance(root->left,res);
	int r = GetMaxDistance(root->right,res);
	res = max(l + r, res);
	return max(l, r) + 1;
}

int GetMaxDistance(TreeNode* root) {
	int res=0;
	GetMaxDistance(root, res);
	return res;
}





///////////////////////12、判断是否为完全二叉树///////////////////////////////
bool isCompleteBinary(TreeNode* root) {
	if (root == NULL)	return true;
	queue<TreeNode*> q;
	q.push(root);
	bool isLeaf = false;

	while (!q.empty()) {
		TreeNode* temp = q.front();
		q.pop();
		if (temp->right && !temp->left)	return false;	//有右没有左则错

		if (isLeaf) {
			if (temp->right || temp->left)	return false;	//已经是叶子节点了，还有子节点则错
		}
		if (temp->left)		q.push(temp->left);	//先进左节点
		if (temp->right)	q.push(temp->right);	
		else isLeaf = true;		//右节点不存在则是叶子节点
	}
	return true;
}

////////////////////////13、对称二叉树///////////////////////
bool box(TreeNode* rootL, TreeNode* rootR) {
	if (!rootL && !rootR)	return true;
	if (!rootL || !rootR)	return false;
	return (rootL->val == rootR->val) &&
		box(rootL->left, rootR->right) &&
		box(rootL->right, rootR->left);
}

bool isSymmetric(TreeNode* root) {
	if (!root)	return true;
	return box(root->left, root->right);
}


bool isSymmetric1(TreeNode* root) {
	queue<TreeNode*> q;
	q.push(root);
	q.push(root);

	while (!q.empty()) {
		TreeNode* t1 = q.front();
		q.pop();
		TreeNode* t2 = q.front();
		q.pop();
		if (!t1 && !t2)	continue;
		if (!t1 || !t2)	return false;
		if (t1->val != t2->val)	return false;

		q.push(t1->left);
		q.push(t2->right);
		q.push(t1->right);
		q.push(t2->left);
	}
	return true;
}

//////////////////14、层序遍历//////////////////////
vector<vector<int>> levelOrder(TreeNode* root) {
	if (!root)	return {};

	vector<vector<int>> res;

	queue<TreeNode*> q;
	q.push(root);

	while (!q.empty()) {
		vector<int> path;
		int len = q.size();
		for (int i = 0; i < len; i++) {
			TreeNode* temp = q.front();
			q.pop();

			path.push_back(temp->val);
			if (temp->left)	q.push(temp->left);
			if (temp->right)	q.push(temp->right);
		}
		res.push_back(path);
	}
	return res;
}


void pre(TreeNode* root, int layer, vector<vector<int>>& res) {

	if (!root)	return;

	if (layer >= res.size())	res.push_back(vector<int> {});
	res[layer].push_back(root->val);

	pre(root->left, layer + 1, res);
	pre(root->right, layer + 1, res);
}

vector<vector<int>> levelOrder1(TreeNode* root) {
	vector<vector<int>> res;
	pre(root, 0, res);
	return res;
}




/////////////////////////15、最大路径和//////////////////////
int maxPathSum(TreeNode* root, int& val) {
	//终止条件
	if (!root)	return 0;
	//递归
	int l = maxPathSum(root->left, val);
	int r = maxPathSum(root->right, val);
	//赋值操作
	int res1 = root->val + max(0, l) + max(0, r);	//节点的最大路径和取决于该节点的值与该节点的左右子节点的最大贡献值
	int res2 = root->val + max(l, r);				//返回节点的最大贡献值
	//更新最大值
	val = max(val, max(res1, res2));
	//返回当前值
	return res2;
}

int maxPathSum(TreeNode* root) {
	if (!root)	return 0;
	int val = INT_MIN;
	maxPathSum(root, val);
	return val;
}



/////////////////////16、二叉树右视图///////////////////////
void dfsRight(TreeNode* root, int level, vector<int>& res) {
	if (!root)	return;
	if (level == res.size())	res.push_back(root->val);

	dfsRight(root->right, level + 1, res);
	dfsRight(root->left, level + 1, res);

}

vector<int> rightSideView(TreeNode* root) {
	vector<int> res;
	dfsRight(root, 0,res);
	return res;
}



vector<int> rightSideView2(TreeNode* root) {
	if (!root)	return {};

	queue<TreeNode*> q;
	q.push(root);
	vector<int> res;

	while (!q.empty()) {
		int len = q.size();

		/*
		for (int i = 0; i < len; i++) {
			TreeNode* temp = q.front();
			q.pop();
			if (i == len - 1)	res.push_back(temp->val);
			if (temp->left)		q.push(temp->left);
			if (temp->right)	q.push(temp->right);
			
		}
		*/
		res.push_back(q.front()->val);

		while (len--) {
			TreeNode* temp = q.front();
			q.pop();
			if (temp->right)	q.push(temp->right);
			if (temp->left)		q.push(temp->left);
		}
	}
	return res;
}

//////////////////////////17、有序数组转换为二叉搜索树////////////////////
TreeNode* sortedArrayToBST(vector<int>& nums) {
	if (nums.size() == 0) return NULL;

	int mid = nums.size() / 2;
	TreeNode* root = new TreeNode(nums[mid]);

	vector<int> left_n, right_n;
	for (int i = 0; i < mid; i++)
		left_n.push_back(nums[i]);
	for (int i = mid + 1; i < nums.size(); i++)
		right_n.push_back(nums[i]);

	root->left = sortedArrayToBST(left_n);
	root->right = sortedArrayToBST(right_n);

	return root;
}