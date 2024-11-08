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
	int isFull() { return (Top = maxSize - 1); };
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
void seqStack<elemType>::push(const elemType &e)
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