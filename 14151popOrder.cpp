#include <iostream>

class illegalSize {};
class outOfBound { };

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


bool legal(int size, seqQueue<int>& q) 
{
	seqStack<int> s = seqStack<int>(size);
	int i = 1;
	bool end = false;
	while (true) {
		if (!end) s.push(i);
		if (i == size) end = true;
		if (s.isEmpty() && q.isEmpty()) return true;
		if (!s.isEmpty() && (q.front() < s.top())) return false;
		while(!q.isEmpty() && !s.isEmpty() && (s.top() == q.front())) {
			s.pop();
			q.deQueue();
		}
		if (!end) i++;
	}
}

int main()
{
    int orders;
    std::cin >> orders;
    for (int j = 0; j < orders; j++) {
		int size;
		std::cin >> size;
		seqQueue<int> q = seqQueue<int>(size);
		for (int i = 0; i < size; i++) {
			int tmp;
			std::cin >> tmp;
			q.enQueue(tmp);
		}
		if (legal(size, q)) std::cout << "Yes" << std::endl;
		else std::cout << "No" << std::endl;
    }
    return 0;
}

