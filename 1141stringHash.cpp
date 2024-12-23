// 1141stringHash.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <iostream>
using namespace std;

class illegalSize {};
class outOfBound {};

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
    int  size;
    int (*fun)(const elemType& x);
public:
    Node<elemType>* arr;
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


int BKDRHash(const std::string& str) {
    int seed = 131; // 31, 131, 1313, 13131, 131313, etc.
    unsigned int hash = 0;
    for (char ch : str) {
        hash = hash * seed + ch;
    }
    return hash & 0x7FFFFFFF;
}

int main()
{
	int n;
	cin >> n;
    hashTable<std::string> table(n, BKDRHash);
	std::string str;
	for (int i = 0; i < n; i++) {
		cin >> str;
		if (table.find(str)) {
            continue;
		}
		else {
			table.insert(str);
		}
	}
	// Calculate how many different strings are there
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (table.arr[i].state == 1) {
			count++;
		}
	}
	cout << count << endl;
	return 0;
}

