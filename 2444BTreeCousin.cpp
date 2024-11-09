// 2444BTreeCousin.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
/*在二叉树中，根节点的深度是 0，每个深度为 k 的节点的子节点位于深度 k+1 处。
如果二叉树的两个节点深度相同，但父节点不同，则它们是一对堂姐妹堂兄弟节点。
给定一个二叉树的前序遍历，空结点用 -1 补齐（即扩展二叉树）。
给定两个节点 x 和 y，当他们是堂姐妹堂兄弟节点时，返回 1。否则，返回 0。二叉树的节点值不重复。*/

#include <iostream>

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

template <class elemType>
class BTree;

template <class elemType>
class Node
{
	friend class BTree<elemType>;
private:
	elemType data, parentdata;
	int depth;
	Node *left, *right;
public:
	Node() { left = NULL; right = NULL; };
	Node(const elemType& data_, const elemType& parentdata_, int depth_,  Node* L = NULL, Node* R = NULL)
	{
		data = data_;
		parentdata = parentdata_;
		depth = depth_;
		left = L; right = R;
	};
	elemType getData() { return data; }
	elemType getParentData() { return parentdata; }
	int getDepth() { return depth; }
	Node* getLeft() { return left; }
	Node* getRight() { return right; }
};

template <class elemType>
class BTree
{
private:
	Node<elemType>* root;
	elemType stopFlag;
	int Size(Node<elemType>* t); //求以 t 为根的二叉树的结点个数
	int Height(Node<elemType>* t);//求以 t 为根的二叉树的高度
	void PreOrder(Node<elemType>* t);//前序遍历以 t 为根的二叉树
	void DelTree(Node<elemType>* t);//删除以 t 为根的二叉树
public:
	BTree(Node<elemType>* root_, const elemType& stopflag_);
	void createTree(seqQueue<elemType> &q, Node<elemType> *r); //根据前序遍历创建一棵二叉树
	int isEmpty() { return (root == NULL); }// 二叉树为空返回 true, 否则返回 false
	Node<elemType>* GetRoot() { return root; }
	int Size();//求二叉树的结点个数
	int Height();//求二叉树的高度
	Node<elemType>* findNode(Node<elemType>* t, elemType x);//找到x并返回它的地址
	void PreOrder();//前序遍历二叉树
	void DelTree();//删除二叉树
};

template<class elemType>
BTree<elemType>::BTree(Node<elemType> *root_, const elemType &stopflag_)
{
	root = root_;
	stopFlag = stopflag_;
}
template<class elemType>
void BTree<elemType>::createTree(seqQueue<elemType> &q, Node<elemType> *r)
{
	if (!r) return;
	if (q.isEmpty()) return;

	elemType el, er;
	el = q.front();
	q.deQueue();
	if (el != stopFlag)
	{
		r->left = new Node<elemType>(el, r->data, r->getDepth() + 1);
		createTree(q, r->left);
	}

	if (q.isEmpty()) return;
	er = q.front();
	q.deQueue();
	if (er != stopFlag)
	{
		r->right = new Node<elemType>(er, r->data, r->getDepth() + 1);
		createTree(q, r->right);
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

//找到x并返回它的地址
template <class elemType>
Node<elemType>* BTree<elemType>::findNode(Node<elemType>* t, elemType x)
{
	if (!t) return NULL;
	if (t->getData() == x) return t;
	Node<elemType>* leftResult = findNode(t->getLeft(), x);
	if (leftResult) return leftResult;
	return findNode(t->getRight(), x); // Return the result of the right subtree search
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
	std::cout << t->data << ' ';
	PreOrder(t->left);
	PreOrder(t->right);
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


int main()
{
	int n;//查询的个数
	std::cin >> n;
	int* search = new int[2 * n];
	for (int i = 0; i < 2 * n; i++)
	{
		std::cin >> search[i];
	}
	seqQueue<int> preOrder = seqQueue<int>(1000);
	//preOrder存储用户输入的值，直到用户按回车
	int temp;
	while (std::cin >> temp)
	{
		preOrder.enQueue(temp);
		if (std::cin.get() == '\n')
			break;
	}
	int rootdata = preOrder.front();
	BTree<int> tree = BTree<int>(new Node<int>(rootdata, -1, 0), -1);//第一个-1表示根节点的父节点是-1，第二个-1表示树创建结束标志
	preOrder.deQueue();
	tree.createTree(preOrder, tree.GetRoot());

	for (int i = 0; i < n; i++)
	{
		int x = search[2 * i];
		int y = search[2 * i + 1];
		Node<int>* nodeX = tree.findNode(tree.GetRoot(), x);
		Node<int>* nodeY = tree.findNode(tree.GetRoot(), y);
		if (nodeX && nodeY && nodeX->getDepth() == nodeY->getDepth() && nodeX->getParentData() != nodeY->getParentData())
			std::cout << 1 << std::endl;
		else
			std::cout << 0 << std::endl;
	}
	//tree.PreOrder();
	tree.DelTree();
	delete[] search;
	return 0;
}


