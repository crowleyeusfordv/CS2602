// 14135mirrorOfBinaryTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//给定一棵二叉树，求出他的镜像树（即交换所有结点的左右子结点），并给出后序遍历的输出形式
/*
输入格式
第1行：1个正整数n，表示接下来输入n行；
第2行至输入结束：每行有3个正整数a、b和c，设分别为节点A、B和C的标记，表示A的左儿子节点是B，右儿子节点是C,如果输入的节点值为-1，则表示无此子结点。其中第一个输入的a,b,c中A是整棵树的根节点

输出格式
二叉树对应镜像的后序遍历输出
*/
// Btree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

class illegalSize {};
class outOfBound {};

template <class elemType>
class seqQueue
{
private:
	elemType* array;
	int maxSize;
	int Front, Rear;
	void doubleSpace();
public:
	seqQueue(int size = 10);
	bool isEmpty();
	bool isFull();
	elemType front();
	void enQueue(const elemType& x);
	void deQueue();
	~seqQueue();
};

template <class elemType>
seqQueue<elemType>::seqQueue(int size)
{
	array = new elemType[size];
	if (!array) throw illegalSize();
	maxSize = size;
	Front = Rear = 0;
}

template <class elemType>
bool seqQueue<elemType>::isEmpty()
{
	return Front == Rear;
}

template <class elemType>
bool seqQueue<elemType>::isFull()
{
	return (Rear + 1) % maxSize == Front;
}

template <class elemType>
elemType seqQueue<elemType>::front()
{
	if (isEmpty()) throw outOfBound();
	return array[Front];
}

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType& x)
{
	if (isFull()) doubleSpace();
	array[Rear] = x;
	Rear = (Rear + 1) % maxSize;
}

template <class elemType>
void seqQueue<elemType>::deQueue()
{
	if (isEmpty()) throw outOfBound();
	Front = (Front + 1) % maxSize;
}

template <class elemType>
seqQueue<elemType>::~seqQueue()
{
	delete[] array;
}

template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
	elemType* newArray;
	int i, j;

	newArray = new elemType[2 * maxSize];
	if (!newArray) throw illegalSize();

	for (i = 0, j = Front; j != Rear; i++, j = (j + 1) % maxSize)
		newArray[i] = array[j];

	delete[]array;
	array = newArray;
	Front = 0;
	Rear = j;
	maxSize = 2 * maxSize;
}

//BTree 类的前向说明
template <class elemType>
class BTree;

template <class elemType>
class Node
{
	friend class BTree<elemType>;
private:
	elemType data;
	Node* left, * right;
public:
	Node() { left = NULL; right = NULL;};
	Node(const elemType& e, Node* L = NULL, Node* R = NULL)
	{
		data = e;
		left = L; right = R;
	}
	elemType GetData() { return data; }
	Node* GetLeft() { return left; }
	Node* GetRight() { return right; }
	void SetData(const elemType& e) { data = e; }
	void SetLeft(Node* L) { left = L; }
	void SetRight(Node* R) { right = R; }
};
template <class elemType>
class BTree
{
private:
	Node<elemType>* root;
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
	BTree(Node<elemType>* node) { root =node; }
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

void Mirror(Node<int>* root);
int main()
{
	int n;
	cin >> n;//the number of nodes
	Node<int>** nodeArray = new Node<int>*[10000]; 
	int a, b, c;
	int index = 0;
	cin >> a >> b >> c;
	Node<int>* left = (b == -1) ? NULL : new Node<int>(b);
	Node<int>* right = (c == -1) ? NULL : new Node<int>(c);
	Node<int>* root = new Node<int>(a, left, right);
	if (b != -1) {
		nodeArray[index++] = left;
	}
	if (c != -1) {
		nodeArray[index++] = right;
	}
	//Read the remaining node information and build the tree
	for (int i = 1; i < n; ++i) {
		cin >> a >> b >> c;
		for (int j = 0; j < index; ++j) { 
			if (nodeArray[j]->GetData() == a) {
				if (b != -1) {
					Node<int>* left_ = new Node<int>(b);
					nodeArray[index++] = left_;
					nodeArray[j]->SetLeft(left_);
				}
				if (c != -1) {
					Node<int>* right_ = new Node<int>(c);
					nodeArray[index++] = right_;
					nodeArray[j]->SetRight(right_);
				}
				break;
			}
		}
	}
	BTree<int> tree = BTree<int>(root);
	Mirror(tree.GetRoot());
	tree.PostOrder();

	return 0;
}

void Mirror(Node<int>* root) {
	if (root == NULL) {
		return;
	}
	Node<int>* temp = root->GetLeft();
	root->SetLeft(root->GetRight());
	root->SetRight(temp);
	Mirror(root->GetLeft());
	Mirror(root->GetRight());
}

