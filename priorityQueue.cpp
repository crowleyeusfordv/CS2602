class illegalSize {};
class outOfBound {};
template <class elemType>
class priorityQueue
{
private:
    elemType* array;
    int maxSize，currentLen;
    void doubleSpace(); //扩展队队列元素的存储空间             
    void adjust(int hole); //调整下标为hole的元素，使成为小顶堆
    void build(int r); //递归调整
public:
    priorityQueue(int size = 10); //建立空优先级队列
    priorityQueue(elemType a[], int n); //建立非空优先级队列，即建小顶堆
    bool isEmpty() { return currentLen == 0; };  //判断队空否
    bool isFull() { return (currentLen == maxSize - 1); };  //判断队满否
    elemType front(); //读取队首元素的值，队首不变
    void enQueue(const elemType& x); //将x进队，成为新的队尾
    void deQueue(); //将队首元素出队
    ~priorityQueue() { delete[]array; }; //释放队列元素所占据的动态数组
};

template <class elemType>
priorityQueue<elemType>::priorityQueue(int size)
{
	array = new elemType[size];
	if (!array) throw illegalSize();
	maxSize = size;
	currentLen = 0;
}

template <class elemType>
priorityQueue<elemType>::priorityQueue(elemType a[], int n)
{
	if (n < 1) throw illegalSize();
	array = new elemType[n + 10];//多分配10个空间,以便于后面的入队
	if (!array) throw illegalSize();
	maxSize = n + 10;
	currentLen = n;
	for (int i = 1; i <= n; i++)
		array[i] = a[i - 1];
	for (int i = n / 2; i > 0; i--)
		adjust(i);
}

template <class elemType>
void priorityQueue<elemType>::build(int r)
{
	if (r * 2 > currentLen) return;
	build(r * 2);
	build(r * 2 + 1);
	adjust(r);
}

template <class elemType>
void priorityQueue<elemType>::adjust(int hole)
//反复向下调整hole的位置
{
	int minChild;
	elemType x;
	x = array[hole];
	while (true)
	{
		minChild = hole * 2;//hole的左子下标
		if (minChild > currentLen) break;
		if (minChild + 1 <= currentLen && array[minChild + 1] < array[minChild])
			minChild++;//右子最小

		if (x < array[minChild]) break;
		array[hole] = array[minChild];
		hole = minChild;//继续向下调整
	}
	array[hole] = x;
}

template <class elemType>
elemType priorityQueue<elemType>::front()
{
	if (isEmpty()) throw outOfBound();
	return array[1];
}

template <class elemType>
void priorityQueue<elemType>::enQueue(const elemType& x)
{
	if (isFull())  doubleSpace();
	int hole; //hole位置向上调整
	currentLen++;
	for (hole = currentLen; hole > 1 && x < array[hole / 2]; hole /= 2)
		array[hole] = array[hole / 2];
	array[hole] = x;
}

template <class elemType>
void priorityQueue<elemType>::deQueue() //将队首元素出队
{
	if (isEmpty()) throw outOfBound();
	array[1] = array[currentLen];
	currentLen--;
	adjust(1);
}

template <class elemType>
void priorityQueue<elemType>::doubleSpace()
{
	elemType* tmp = array;
	array = new elemType[2 * maxSize];
	if (!array) throw illegalSize();
	for (int i = 1; i <= currentLen; i++)
		array[i] = tmp[i];
	maxSize *= 2;
	delete[]tmp;
}