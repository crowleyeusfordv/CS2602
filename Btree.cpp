// Btree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

//BTree 类的前向说明
template <class elemType>
class BTree;

template <class elemType>
class Node
{
	friend class BTree<elemType>;
private:
	elemType data;
	Node *left, *right;
	int leftFlag; //用于标识是否线索，0 时 left 为左孩子结点，1 时为前驱线索
	int rightFlag; //用于标识是否线索，0 时 right 为右孩子结点，1 时为后继线索
public:
	Node() { left = NULL; right = NULL; leftFlag = 0; rightFlag = O; };
	Node(const elemType& e, Node* L = NULL, Node* R = NULL)
	{
		data = e;
		left = L; right = R; leftFlag = 0; rightFlag = O;
	}；
};
template <class elemType>
	class BTree
	{
	private:
		Node<elemType>* root;
		elemType stopFlag;
		int Size(Node<elemType>* t); //求以 t 为根的二叉树的结点个数
		int Height(Node<elemType>* t);//求以 t 为根的二叉树的高度
		void DelTree(Node<elemType>* t);//删除以 t 为根的二叉树
		void PreOrder(Node<elemType>* t);
		// 按前序遍历输出以 t 为根的二叉树的结点的数据值
		void InOrder(Node<elemType>* t);
		//按中序遍历输出以 t 为根的二叉树的结点的数据值
		void PostOrder(Node<elemType>* t);
		//按后序遍历输出以 t 为根的二叉树的结点的数据值
	public:
		BTree() { root = NULL; }
		void createTree(const elemType& flag); //创建一棵二叉树
		bool isEmpty() { return (root == NULL); }// 二叉树为空返回 true, 否则返回 false
		Node<elemType>* GetRoot() { return root; }
		int Size();//求二叉树的结点个数
		int Height();//求二叉树的高度
		void DelTree();//删除二叉树
		void PreOrder();// 按前序遍历输出二叉树的结点的数据值
		void InOrder();// 按中序遍历输出二叉树的结点的数据值
		void PostOrder();// 按后序遍历输出二叉树的结点的数据值
		void LevelOrder();// 按中序遍历输出二叉树的结点的数据值
		~BTree();
	};

template <class elemType>
void BTree<elemType>::createTree(const elemType& flag)//flag 为二叉树中的一个特殊值，用来标识二叉树的结束

{
	seqQueue<Node<elemType>*> que;
	elemType e, el, er;
	Node<elemType>* p, *pl, *pr;

	cout << "Please input the root";
	cin >> e;

	if (e == flag) { root = NULL; return; }

	p = new Node<elemType>(e);
	root = p;//根节点为该新创建结点

	que.enQueue(p);//根节点入队
	while (!que.isEmpty())
	{
		p = que.front();//获得队首元素并出队
		que.deQueue();

		cout << "Please input the left child and the right child of" << p->data << "using" << flag << "as no child";
		cin >> el >> er;
		if (el != flag)//该结点有左孩子
		{
			pl = new Node<elemType>(el);
			p->left = pl;
			que.enQueue(pl);
		}
		if (er != flag)//该结点有右孩子
		{
			pr = new Node<elemType>(er);
			p->right = pr;
			que.enQueue(pr);
		}
	}
}

template <class elemType>
int BTree<elemType>::Size()
{
	return Size(root);
}

template <class elemType>
int BTree<elemType>::Size(Node<elemType>* t)
//求以 t 为根的二叉树的结点个数,递归算法实现
{
	if (!t) return 0;
	return 1 + Size(t->left) + Size(t->right);
}

template <class elemType>
int BTree<elemType>::Height()
{
	return Height(root);
}

template <class elemType>
int BTree<elemType>::Height(Node<elemType>* t)
{
	if (!t) return 0;

	int hl = Height(t->left);
	int hr = Height(t->right);

	return 1 + (hl > hr ? hl : hr);
}

template <class elemType>
void BTree<elemType>::DelTree()
{
	DelTree(root);
	root = NULL;
}

template <class elemType>
void BTree<elemType>::DelTree(Node<elemType>* t)
{
	if (!t) return;
	DelTree(t->left);
	DelTree(t->right);
	delete t;
}

template <class elemType>
void BTree<elemType>::PreOrder()
{
	PreOrder(root);
}

template <class elemType>
void BTree<elemType>::PreOrder(Node<elemType>* t)
{
	if (!t) return;
	cout << t->data << ' ';
	PreOrder(t->left);
	PreOrder(t->right);
}

template <class elemType>
void BTree<elemType>::InOrder()
{
	InOrder(root);
}

template <class elemType>
void BTree<elemType>::InOrder(Node<elemType>* t)
{
	if (!t) return;
	InOrder(t->left);
	cout << t->data << ' ';
	InOrder(t->right);
}

template <class elemType>
void BTree<elemType>::PostOrder()
{
	PostOrder(root);
}

template <class elemType>
void BTree<elemType>::PostOrder(Node<elemType>* t)
{
	if (!t) return;
	PostOrder(t->left);
	PostOrder(t->right);
	cout << t->data << ' ';
}

template <class elemType>
void BTree<elemType>::LevelOrder()
{
	seqQueue<Node<elemType>*> que;
	Node<elemType>* p;

	if (!root) return;

	que.enQueue(root);
	while (!que.isEmpty())
	{
		p = que.front();
		que.deQueue();
		cout << p->data << ' ';
		if (p->left) que.enQueue(p->left);
		if (p->right) que.enQueue(p->right);
	}
}

template <class elemType>
BTree<elemType>::~BTree()
{
	DelTree();
}
