#include <iostream>

using namespace std;

class illegalSize {};
class outOfBound {};

template <class elemType>
class priorityQueue
{
private:
    elemType* array;
    int maxSize,currentLen;
    void doubleSpace(); //扩展队队列元素的存储空间             
    void adjust(int hole); //调整下标为hole的元素，使成为小顶堆
    void build(int r); //递归调整
public:
    priorityQueue(int size = 10); //建立空优先级队列
    priorityQueue(elemType a[], int n); //建立非空优先级队列，即建小顶堆
    bool isEmpty() { return currentLen == 0; }; //判断队空否
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

template <class elemType>
struct Node {
    elemType data;
    int state;  //0:empty 1:occupied 2:deleted
    Node() { state = 0; }
};

template <class elemType>
class hashTable
{
private:
    Node<elemType>* arr;
    int  size;
    int (*fun)(const elemType& x);
public:
    hashTable(int len, int (*f)(const elemType& x));
    ~hashTable() { delete[] arr; }
    bool find(const elemType& x) const;
    bool insert(const elemType& x);
    bool remove(const elemType& x);
};

template <class elemType>
hashTable<elemType>::hashTable(int len, int (*f)(const elemType& x))
{
    size = len;
    arr = new Node<elemType>[size];
    if (!arr) throw illegalSize();
    fun = f;
}

template <class elemType>
bool hashTable<elemType>::insert(const elemType& x)
{
    int initPos, pos;
    initPos = fun(x) % size;
    pos = initPos;
    do {
        if (arr[pos].state != 1) { // state==0 or state==2
            arr[pos].data = x;
            arr[pos].state = 1;
            return true;
        }
        if (arr[pos].state == 1) {
            if (arr[pos].data == x) return false;
            else pos = (pos + 1) % size;
        }
    } while (pos != initPos);
    return false;
}

template <class elemType>
bool hashTable<elemType>::remove(const elemType& x)
{
    int initPos, pos;
    initPos = fun(x) % size;
    pos = initPos;
    do {
        if (arr[pos].state == 0) return false;
        if (arr[pos].state == 1 && arr[pos].data == x) {
            arr[pos].state = 2;
            return true;
        }
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return false;
}

template <class elemType>
bool hashTable<elemType>::find(const elemType& x) const
{
    int initPos, pos;
    initPos = fun(x) % size;
    pos = initPos;
    do {
        if (arr[pos].state == 0) return false;
        if (arr[pos].state == 1 && arr[pos].data == x)
            return true;
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return false;
}

static int hashFunction(const int& x) {
    // 优化的哈希函数，考虑丑数的特性
    int hash = 0;
    int num = x;
    while (num % 2 == 0) {
        hash += 2;
        num /= 2;
    }
    while (num % 3 == 0) {
        hash += 3;
        num /= 3;
    }
    while (num % 5 == 0) {
        hash += 5;
        num /= 5;
    }
    return hash;
}


int main() {
    int n;
    cin >> n;
	priorityQueue<int> pq(n*2);
    hashTable<int> uglynumbers(n*2, hashFunction);
    pq.enQueue(1);
	uglynumbers.insert(1);
	int factors[3] = { 2, 3, 5 };
    int ugly = 0;
	for (int i = 0; i < n; i++) {
		ugly = pq.front();
		pq.deQueue();
		for (int j = 0; j < 3; j++) {
			int newUgly = ugly * factors[j];
			if (!uglynumbers.find(newUgly)) {
				pq.enQueue(newUgly);
				uglynumbers.insert(newUgly);
			}
		}
	}
	cout << ugly << endl;
    return 0;
}
