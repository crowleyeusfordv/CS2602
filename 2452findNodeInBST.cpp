// 2452findNodeInBinarySearchTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

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
class seqStack
{
private:
	elemType* array;
	int Top;
	int maxSize;
	void doubleSpace();
public:
	seqStack(int initSize = 100);
	int isEmpty() { return (Top == -1); };
	int isFull() { return (Top == maxSize - 1); };
	elemType top();
	void push(const elemType& e);
	void pop();
	~seqStack() { delete[] array; };
};

template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
	array = new elemType[initSize];
	if (!array) throw illegalSize();
	Top = -1;//初始化时栈顶指针指向-1
	maxSize = initSize;
}

template <class elemType>
void seqStack<elemType>::doubleSpace()
{
	elemType* tmp;
	int i;

	tmp = new elemType[maxSize * 2];
	if (!tmp) throw illegalSize();//分配失败
	for (i = 0; i < maxSize; ++i)
		tmp[i] = array[i];
	maxSize *= 2;
	delete[] array;
	array = tmp;
}

template <class elemType>
elemType seqStack<elemType>::top() // 返回栈顶元素的值，不改变栈顶
{
	if (isEmpty()) throw outOfBound();
	return array[Top];
}

template <class elemType>
void seqStack<elemType>::push(const elemType& e)
{
	if (isFull()) doubleSpace();
	array[++Top] = e;
}

template <class elemType>
void seqStack<elemType>::pop()
{
	if (isEmpty()) throw outOfBound();
	Top--;
}

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
	Node() { left = NULL; right = NULL; };
	Node(const elemType& data_, Node* L = NULL, Node* R = NULL)
	{
		data = data_;
		left = L; right = R;
	};
	elemType getData() { return data; }
	Node* getLeft() { return left; }
	void setLeft(Node* L) { left = L; }
	Node* getRight() { return right; }
};

template <class elemType>
class BTree
{
private:
	Node<elemType>* root;
	int Size(Node<elemType>* t); //求以 t 为根的二叉树的结点个数
	int Height(Node<elemType>* t);//求以 t 为根的二叉树的高度
	void DelTree(Node<elemType>* t);//删除以 t 为根的二叉树
	void InOrder(Node<elemType>* t, seqStack<elemType>& s);

public:
	BTree(Node<elemType>* root_);
	BTree(int arr[]);
	Node<elemType>* createTree(int arr[]); //根据前序遍历创建一棵二叉树
	int isEmpty() { return (root == NULL); }// 二叉树为空返回 true, 否则返回 false
	Node<elemType>* GetRoot() { return root; }
	int Size();//求二叉树的结点个数
	int Height();//求二叉树的高度
	Node<elemType>* insertValue(int value, seqQueue<Node<elemType>*>& q);
	void levelOrder();
	void InOrder(seqStack<elemType>& s);
	~BTree();
};

template<class elemType>
BTree<elemType>::BTree(Node<elemType>* root_)
{
	root = root_;
}

template<class elemType>
BTree<elemType>::BTree(int arr[])
{
	root = createTree(arr);
}

template<class elemType>
Node<elemType>* BTree<elemType>::insertValue(int value, seqQueue<Node<elemType>*>& q)
{
	Node<elemType>* node = new Node<elemType>(value);
	if (root == NULL)
		root = node;

	// The left child of the current Node is
	// used if it is available.
	else if (q.front()->left == NULL)
		q.front()->left = node;

	// The right child of the current Node is used
	// if it is available. Since the left child of this
	// node has already been used, the Node is popped
	// from the queue after using its right child.
	else {
		q.front()->right = node;
		q.deQueue();
	}

	// Whenever a new Node is added to the tree, its
	// address is pushed into the queue.
	// So that its children Nodes can be used later.
	q.enQueue(node);
	return root;
}

template<class elemType>
Node<elemType>* BTree<elemType>::createTree(int arr[])
{
	root = NULL;
	seqQueue<Node<elemType>*> q;
	for (int i = 0; i < 7; i++)
		root = insertValue(arr[i], q);
	return root;
}

// This is used to verify the logic.
template<class elemType>
void BTree<elemType>::levelOrder()
{
	if (root == NULL)
		return;
	seqQueue<Node<elemType>*> n;
	n.enQueue(root);
	while (!n.isEmpty()) {
		std::cout << n.front()->data << " ";
		if (n.front()->left != NULL)
			n.enQueue(n.front()->left);
		if (n.front()->right != NULL)
			n.enQueue(n.front()->right);
		n.deQueue();
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
BTree<elemType>::~BTree()
{
	DelTree(root);
	root = NULL;
}

template <class elemType>
void BTree<elemType>::DelTree(Node<elemType>* t)
{
	if (t == NULL) return;
	DelTree(t->left);
	DelTree(t->right);
	delete t;
}

template <class elemType>
void BTree<elemType>::InOrder(seqStack<elemType> &s)
{
	InOrder(root, s);
}

template <class elemType>
void BTree<elemType>::InOrder(Node<elemType>* t, seqStack<elemType> &s)
{
	if (!t) return;
	InOrder(t->left, s);
	s.push(t->data);
	InOrder(t->right, s);
}

int main()
{
	int arr[7];
	for (int i = 0; i < 7; i++)
	{
		std::cin >> arr[i];
	}
	int cnt;
	std::cin >> cnt;
	BTree<int> tree = BTree<int>(arr);
	seqStack<int> s;
	tree.InOrder(s);
	for (int i = 1; i < cnt; i++)
	{
		s.pop();
	}
	std::cout << s.top();
	return 0;
}

