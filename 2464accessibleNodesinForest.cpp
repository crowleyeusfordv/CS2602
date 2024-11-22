// 2464accessibleNodesinForest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
/*小蚂蚁在森林中觅食，它得知食物在森林中的某一个节点，请你帮它判断这个节点是否可达。
森林由若干二叉树组成，且每棵树都是满二叉树。在树上，小蚂蚁仅能从父节点出发，到达子节点，而不能反向。
除此之外，森林中还存在一些额外的单向路（称为“小道”），从一个节点指向另一个节点，使得蚂蚁可以在不同的树之间穿梭。*/

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
	seqQueue(int size = 10000);
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
	Node* left, * right, *path;
	bool visited;
public:
	Node() { left = NULL; right = NULL; path = NULL; visited = false; };
	Node(const elemType& e, Node* L = NULL, Node* R = NULL)
	{
		data = e;
		left = L; 
		right = R;
		path = NULL;
		visited = false;
	};
	elemType getData() { return data; }
	Node* getLeft() { return left; }
	Node* getRight() { return right; }
	Node* getPath() { return path; }
	bool getVisited() { return visited; }
	void setLeft(Node* L) { left = L; }
	void setRight(Node* R) { right = R; }
	void setPath(Node* P) { path = P; }
	void setVisited(bool V) { visited = V; }
};
template <class elemType>
class BTree
{
private:
	Node<elemType>* root;
	void DelTree(Node<elemType>* t);//删除以 t 为根的二叉树
public:
	BTree(Node<elemType>* root_) { root = root_; }
	bool isEmpty() { return (root == NULL); }// 二叉树为空返回 true, 否则返回 false
	Node<elemType>* GetRoot() { return root; }
	void DelTree();//删除二叉树
	void LevelOrder();// 按中序遍历输出二叉树的结点的数据值
	~BTree();
};



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


Node<int>* createTreeByLevelOrder(const int* datum, int size);
Node<int>* findNode(Node<int>* root, int target);
bool BFS(Node<int>* root, int target);
void setVisitedFalse(Node<int>* root);

int main()
{
	int treesnum;//number of trees in the forest
	cin >> treesnum;
	Node<int>** roots = new Node<int>*[treesnum];
	for (int i = 0; i < treesnum; i++)
	{
		int levelsnum;
		cin >> levelsnum;
		int* datum = new int[(1 << levelsnum) - 1];
		for (int j = 0; j < ((1 << levelsnum) - 1); j++)
		{
			cin >> datum[j];
		}
		roots[i] = createTreeByLevelOrder(datum, (1 << levelsnum) - 1);
	}
	int pathnum;
	cin >> pathnum;
	for (int i = 0; i < pathnum; i++)
	{
		int begin, end;
		cin >> begin >> end;
		Node<int>* beginNode = NULL;
		Node<int>* endNode = NULL;
		for (int j = 0; j < treesnum; j++)
		{
			if (findNode(roots[j], begin))
			{
				beginNode = findNode(roots[j], begin);
				break;
			}
		}
		for (int j = 0; j < treesnum; j++)
		{
			if (findNode(roots[j], end))
			{
				endNode = findNode(roots[j], end);
				break;
			}
		}
		beginNode->setPath(endNode);
	}
	int targetnum;
	cin >> targetnum;
	int target;
	for (int i = 0; i < targetnum; i++)
	{
		cin >> target;
		if (BFS(roots[0], target)) cout << "Yes" << endl;
		else cout << "No" << endl;
		for (int j = 0; j < treesnum; j++)
		{
			setVisitedFalse(roots[j]);
		}
	}
	//Release memory
	for (int i = 0; i < treesnum; i++)
	{
		BTree<int>* tree = new BTree<int>(roots[i]);
		tree->DelTree();
	}
    return 0;
}

Node<int>* createTreeByLevelOrder(const int* datum, int size)
{
	Node<int>* root = new Node<int>(datum[0]);
	seqQueue<Node<int>*> que;
	que.enQueue(root);

	int i = 1;

	while (!que.isEmpty() && i < size)
	{
		Node<int>* current = que.front();
		que.deQueue();

		//Create left child
		if (i < size)
		{
			Node<int>* left = new Node<int>(datum[i]);
			current->setLeft(left);
			que.enQueue(left);
			i++;
		}
		//Create right child
		if (i < size)
		{
			Node<int>* right = new Node<int>(datum[i]);
			current->setRight(right);
			que.enQueue(right);
			i++;
		}
	}
	return root;
}

Node<int>* findNode(Node<int>* root, int target)
{
	if (!root) return NULL;
	if (root->getData() == target) return root;
	Node<int>* leftResult = findNode(root->getLeft(), target);
	if (leftResult) return leftResult;
	return findNode(root->getRight(), target); 
}

bool BFS(Node<int>* root, int target)
{
	seqQueue<Node<int>*> que;
	que.enQueue(root);
	while (!que.isEmpty())
	{
		Node<int>* current = que.front();
		int x = current->getData();
		que.deQueue();
		if (current->getData() == target) return true;
		if (current->getLeft() && !current->getLeft()->getVisited())
		{
			que.enQueue(current->getLeft());
			current->getLeft()->setVisited(true);
		}
		if (current->getRight() && !current->getRight()->getVisited())
		{
			que.enQueue(current->getRight());
			current->getRight()->setVisited(true);
		}
		if (current->getPath() && !current->getPath()->getVisited())
		{
			que.enQueue(current->getPath());
			current->getPath()->setVisited(true);
		}
	}
	return false;
}

//set all the nodes visited false
void setVisitedFalse(Node<int>* root)
{
	if (!root) return;
	root->setVisited(false);
	setVisitedFalse(root->getLeft());
	setVisitedFalse(root->getRight());
}