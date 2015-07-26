#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <list>
//#define INT_MAX 2147483647  
//#define INT_MIN (-INT_MAX - 1) 
using namespace std;
bool less(int A, int B) {
	return A < B;
}
class BinaryTreeNode {
public:
	int m_val;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
	BinaryTreeNode(int val, BinaryTreeNode* left = NULL, BinaryTreeNode* right = NULL) {
		m_val = val;
		m_pLeft = left;
		m_pRight = right;
	}
};
BinaryTreeNode* Insert(BinaryTreeNode* root, int val)
{
	if(root == NULL)
	{
		root = new BinaryTreeNode(val, NULL, NULL);
		return root;
	}
	if(val < root->m_val)
		root->m_pLeft = Insert(root->m_pLeft, val);
	else
		root->m_pRight = Insert(root->m_pRight, val);
	return root;
}

//求二叉树中的节点个数
int GetNums(BinaryTreeNode* root) {
	if (root == NULL)
		return 0;
	return GetNums(root->m_pLeft) + GetNums(root->m_pRight) + 1;
}
// 求二叉树的深度
int GetDepth(BinaryTreeNode* root) {
	if (root == NULL)
		return 0;
	return max(GetDepth(root->m_pLeft), GetDepth(root->m_pRight)) + 1;
}
// 递归遍历：前序遍历，中序遍历，后序遍历
void visit(BinaryTreeNode* root) {
	cout << root->m_val << " ";
}
void PreOrderTravel(BinaryTreeNode* root) {
	if (root == NULL)
		return;
	visit(root);
	PreOrderTravel(root->m_pLeft);
	PreOrderTravel(root->m_pRight);
}
void InOrderTravel(BinaryTreeNode* root) {
	if (root == NULL)
		return;
	InOrderTravel(root->m_pLeft);
	visit(root);
	InOrderTravel(root->m_pRight);
}
void PostOrderTravel(BinaryTreeNode* root) {
	if (root == NULL)
		return;
	PostOrderTravel(root->m_pLeft);
	PostOrderTravel(root->m_pRight);
	visit(root);

}
// =================非递归遍历=================
void LevelOrderTravel(BinaryTreeNode* root) {
	if (root == NULL)
		return;
	queue<BinaryTreeNode*> q;
	q.push(root);
	while (q.empty() == false) {
		root = q.front();
		visit(root);
		q.pop();
		if (root->m_pLeft)
			q.push(root->m_pLeft);
		if (root->m_pRight)
			q.push(root->m_pRight);
	}
}
void PreOrderTravelRecur(BinaryTreeNode* root) {
	if (root == NULL)
		return;
	stack<BinaryTreeNode*> s;
	s.push(root);
	while (s.empty() == false) {
		root = s.top();
		visit(root);
		s.pop();
		if (root->m_pRight)
			s.push(root->m_pRight);
		if (root->m_pLeft)
			s.push(root->m_pLeft);
	}
}
void InOrderTravelRecur(BinaryTreeNode* root) {
	if (root == NULL)
		return;
	stack<BinaryTreeNode*> s;
	BinaryTreeNode* node  = root;
	while (node != NULL || s.empty() == false) {
		if (node) {
			s.push(node);
			node = node->m_pLeft;
		} else {
			node = s.top();
			s.pop();
			visit(node);
			node = node->m_pRight;
		}
	}
}
// 辅助栈：压根，压左，压右； 
// 栈：   压根，压右，压左；
void PostOrderTravelRecur(BinaryTreeNode* root) {
	if (root == NULL)
		return;
	stack<BinaryTreeNode*> s1;
	stack<BinaryTreeNode*> s2;
	BinaryTreeNode* node = root;
	s1.push(node);
	while (s1.empty() == false) {
		node = s1.top();
		s1.pop();
		s2.push(node);
		if (node->m_pLeft)
			s1.push(node->m_pLeft);
		if (node->m_pRight)
			s1.push(node->m_pRight);
	}
	while (s2.empty() == false) {
		node = s2.top();
		s2.pop();
		visit(node);
	}
}
// 将二叉查找树变为有序的双向链表
void CovertToList(BinaryTreeNode* root, BinaryTreeNode* &pFirst, BinaryTreeNode* &pLast) {
	BinaryTreeNode* pLeftFirst(NULL), *pLeftLast(NULL), *pRightFirst(NULL), *pRightLast(NULL);
	if (root == NULL) {
		pFirst = NULL;
		pLast = NULL;
		return;
	}

	if (root->m_pLeft == NULL) {
		pFirst = root;
	} else {
		CovertToList(root->m_pLeft, pLeftFirst, pLeftLast);
		pLeftLast->m_pRight = root; 
		root->m_pLeft = pLeftLast;
		pFirst = pLeftFirst;
	}

	if (root->m_pRight == NULL) {
		pLast = root;
	} else {
		CovertToList(root->m_pRight, pRightFirst, pRightLast);
		pRightFirst->m_pLeft = root;
		root->m_pRight = pRightFirst;
		pLast = pRightFirst;
	}

}
// 求二叉树第K层的节点个数
int GetNLevelNums(BinaryTreeNode* root, int k) {
	if (root == NULL || k == 0)
		return 0;
	if (k == 1)
		return 1;
	// 左右子树k-1层节点数的和
	return GetNLevelNums(root->m_pLeft, k-1) + GetNLevelNums(root->m_pRight, k-1);
}

// 求二叉树中叶子节点的个数; 叶子节点的定义是：自身非空，左右为NULL
int GetLeafNodeNums(BinaryTreeNode* root) {
	if (root == NULL)
		return 0;
	if (root->m_pLeft == NULL && root->m_pRight == NULL)
		return 1;
	int leftNums = GetLeafNodeNums(root->m_pLeft);
	int rightNums = GetLeafNodeNums(root->m_pRight);
	return leftNums+rightNums;
}

// 判断两棵二叉树是否结构相同
bool TreeStructCmp(BinaryTreeNode* root1, BinaryTreeNode* root2) {
	if (root1 == NULL && root2 == NULL)
		return true;
	if (root1 != root2)
		return false;
	bool leftResult = TreeStructCmp(root1->m_pLeft, root2->m_pLeft);
	bool rightResult = TreeStructCmp(root1->m_pRight, root2->m_pRight);
	return leftResult && rightResult;
}

// 判断二叉树是不是平衡二叉树
// http://zhedahht.blog.163.com/blog/static/25411174201142733927831/
// 后序遍历，只访问1次节点
bool IsAVLTree(BinaryTreeNode* root, int &depth) {
	if (root == NULL) {
		depth = 0;
		return true;
	} 
	int leftDepth, rightDepth;
	if (IsAVLTree(root->m_pLeft, leftDepth) && IsAVLTree(root->m_pRight, rightDepth)) {
		if (abs(leftDepth-rightDepth) <= 1) {
			depth = max(leftDepth, rightDepth)+1;
			return true;
		}
	}
	return false;
}
bool IsAVL(BinaryTreeNode* root) {
	int depth;
	return IsAVLTree(root, depth);
}

// 求二叉树的镜像
BinaryTreeNode* MirrorTree(BinaryTreeNode* root) {
	if (root == NULL)
		return NULL;
	BinaryTreeNode* pLeft = MirrorTree(root->m_pLeft);
	BinaryTreeNode* pRight = MirrorTree(root->m_pRight);
	root->m_pLeft = pRight;
	root->m_pRight = pLeft;
	return root;
}
// 判断二叉树是不是完全二叉树
// 层序遍历，一旦一个节点含有空子树后，之后所有的节点必须只含有NULL
bool IsCompleteBinaryTree(BinaryTreeNode* root) {
	if (root == NULL)
		return true;
	queue<BinaryTreeNode* > q;
	bool HaveNULL = false;
	q.push(root);
	while (q.empty() == false) {
		root = q.front();
		q.pop();
		if (HaveNULL) {
			if (root->m_pLeft || root->m_pRight)
				return false;
		} else {
			if (root->m_pLeft && root->m_pRight) {
				// 左右非空
				q.push(root->m_pLeft);
				q.push(root->m_pRight);
			} else if (root->m_pLeft && root->m_pRight == NULL) {
				// 左非空，右空
				HaveNULL = true;
				q.push(root->m_pLeft);
			} else if (root->m_pLeft == NULL && root->m_pRight) {
				// 左空，右非空
				return false;
			} else {
				// 左右为空
				HaveNULL = true;
			}
		}
	}
	return true;
}
// 判断二叉树是否是搜索二叉树
// 中序遍历，判断遍历顺序是否是从小到大
bool IsBSTreeHelper(BinaryTreeNode* root, int &prev) {
	if (root == NULL)
		return true;
	if (IsBSTreeHelper(root->m_pLeft, prev)) {
		if (root->m_val >= prev) {
			prev = root->m_val;
			if (IsBSTreeHelper(root->m_pRight, prev))
				return true; // 此时左子树、根、右子树都满足要求
			else
				return false; // 右不满足
		} else {
			return false; // 根不满足
		}
	} else {
		return false; // 左不满足
	}
}
bool IsBST(BinaryTreeNode* root) {
	int prev = INT_MIN; // 比较元素，设为最小
	return IsBSTreeHelper(root, prev);
}
// 求二叉树中两个节点的最低公共祖先节点
bool GetPath(BinaryTreeNode* root, BinaryTreeNode* node, list<BinaryTreeNode*> &path) {
	if (root == node) {
		path.push_back(root);
		return true;
	}
	if (root == NULL)
		return false;
	bool found = false;
	path.push_back(root);
	found = GetPath(root->m_pLeft, node, path);
	if (!found)
		found = GetPath(root->m_pRight, node, path);
	if (!found)
		path.pop_back();
	return found;
}
BinaryTreeNode* GetLastCommonParent(BinaryTreeNode* root, BinaryTreeNode* node1, BinaryTreeNode* node2) {
	if (root == NULL || node1 == NULL || node2 == NULL)
		return NULL;
	list<BinaryTreeNode*> path1, path2;
	bool found1 = GetPath(root, node1, path1);
	bool found2 = GetPath(root, node2, path2);
	BinaryTreeNode* pLast = NULL;
	if (!found1 || !found2)
		return NULL;
	list<BinaryTreeNode*>::const_iterator iter1 = path1.begin();
	list<BinaryTreeNode*>::const_iterator iter2 = path2.begin();
	while (iter1 != path1.end() && iter2 != path2.end()) {
		if (*iter1 != *iter2)
			break;
		pLast = *iter1;
		iter1++;
		iter2++;
	}
	return pLast;
}

// 求二叉树中节点的最大距离maxDistance
// 树为空，距离为0；
// 最大距离有3中可能，左子树中的最大距离，右子树中的最大距离，从左子树到根然后到右子树的最大距离
// 同时记录左右子树到根的最大距离

//maxLeft, maxRight 左右子树中的节点到根的最大距离
int GetMaxDistRecur(BinaryTreeNode* root, int &maxLeft, int &maxRight) {
	if (root == NULL) {
		maxLeft = 0, maxRight = 0;
		return 0;
	}
	int maxLL, maxLR, maxRL, maxRR;
	int maxDistLeft, maxDistRight; // 左、右子树中的最大距离
	if (root->m_pLeft) {
		maxDistLeft = GetMaxDistRecur(root->m_pLeft, maxLL, maxLR);
		maxLeft = max(maxLL, maxRR) + 1;
	} else {
		maxDistLeft = 0;
		maxLeft = 0;
	}
	if (root->m_pRight) {
		maxDistRight = GetMaxDistRecur(root->m_pRight, maxRL, maxRR);
		maxRight = max(maxRL, maxRR) + 1;
	} else {
		maxDistRight = 0;
		maxRight = 0;
	}
	return max(maxLeft+maxRight, max(maxDistLeft, maxDistRight));
}
int GetMaxDistance(BinaryTreeNode* root) {
	int maxLeft = 0, maxRight = 0; // 左右子树到根的最大距离
	return GetMaxDistRecur(root, maxLeft, maxRight);
}
// 由前序遍历序列和中序遍历序列重建二叉树
BinaryTreeNode* RebuildBinaryTree(int* preorder, int* inorder, int nums) {
	if (preorder == NULL || inorder == NULL || nums <= 0)
		return NULL;
	BinaryTreeNode* root = new BinaryTreeNode(preorder[0]);
	int rootPositionOnInorder = -1;
	for (int i = 0; i < nums; i++) {
		if (inorder[i] == root->m_val) {
			rootPositionOnInorder = i;
			break;
		}
	}
	if (rootPositionOnInorder == -1) {
		cout << "Input Error." << endl;
	}
	// Rebuild Left Tree
	root->m_pLeft = RebuildBinaryTree(preorder+1, inorder, rootPositionOnInorder);
	// Rebuild Right Tree
	root->m_pRight = RebuildBinaryTree(preorder+1+rootPositionOnInorder, inorder+1+rootPositionOnInorder, nums-rootPositionOnInorder-1);
	return root;
}
int main()
{

	/*			 4
			3	     6	
		 2		  5	 7
							9
								10
	*/
	int vals[] = {4,6,3,7,5,2,9,10};
	BinaryTreeNode* root = NULL;
	for (int i = 0; i < sizeof(vals)/sizeof(vals[0]); i++) {
		root = Insert(root, vals[i]);
	}


	BinaryTreeNode* root2 = NULL;
	root2 = Insert(root2, 2);
	root2 = Insert(root2, 1);
	root2 = Insert(root2, 3);

	cout << "Nums: " << GetNums(root) << endl;
	cout << "Depth: " << GetDepth(root) << endl;
	cout << "PreOrderTravel: ";
	PreOrderTravel(root);
	cout << endl;
	cout << "InOrderTravel: ";
	InOrderTravel(root);
	cout << endl;
	cout << "PostOrderTravel: ";
	PostOrderTravel(root);
	cout << endl;    
	cout << "LevelOrderTravel: ";
	LevelOrderTravel(root);
	cout << endl;
	PreOrderTravelRecur(root);
	cout << endl;
	InOrderTravelRecur(root);
	cout << endl;
	PostOrderTravelRecur(root);
	cout << endl;


	cout << endl;
	cout << "k Level Nums: " << GetNLevelNums(root, 3) << endl;
	cout << "Is AVL : " << IsAVL(root) << endl;
	cout << "Is AVL : " << IsAVL(root2) << endl;
	cout << "Is IsCompleteBinaryTree : " << IsCompleteBinaryTree(root) << endl;
	cout << "Is IsCompleteBinaryTree : " << IsCompleteBinaryTree(root2) << endl;
	cout << "Is a Binary Search Tree : " << IsBST(root) << endl;
	BinaryTreeNode* lastCommonParentNode = GetLastCommonParent(root, root->m_pLeft, root->m_pRight->m_pRight->m_pRight);
	if (lastCommonParentNode)
		cout << "lastCommonParentNode: "<< lastCommonParentNode->m_val << endl;

	cout << "MaxDistance: " << GetMaxDistance(root) << endl;

	cout << "Mirror: " << endl;
	MirrorTree(root);
	PreOrderTravelRecur(root);

	// 树转为双向链表
	BinaryTreeNode *pFirst = NULL, *pLast = NULL;
	CovertToList(root, pFirst, pLast);
	for (BinaryTreeNode* node = pFirst; node != NULL; node = node->m_pRight)
		cout << node->m_val << " ";
	cout << endl;

	// 树的重建
	int preorder[] = {4,3,2,6,5,7,9,10};
	int inorder[] = {2,3,4,5,6,7,9,10};
	BinaryTreeNode* newTree = RebuildBinaryTree(preorder, inorder, 8);
	PreOrderTravelRecur(newTree);
	cout << endl;

}
