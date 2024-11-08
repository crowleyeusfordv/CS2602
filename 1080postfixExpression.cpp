#include <iostream>

using namespace std;

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


int main() {
    char input[10000];
	cin >> input;

    seqStack<int> s = seqStack<int>(10000);
    int number = 0;

    int i = 0;

    while (input[i] != '@') {
		if (input[i] >= '0' && input[i] <= '9') { // 如果是数字
			while (input[i] >= '0' && input[i] <= '9') { // 读取整个数字
				number = number * 10 + input[i] - '0';
				i++;
			}
			s.push(number); // 将数字压入栈中
		}
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') { // 如果是运算符
			int num1, num2;
			num2 = s.top(); s.pop(); // 弹出第二个数字
			num1 = s.top(); s.pop(); // 弹出第一个数字
			switch (input[i]) { // 根据运算符进行运算
			case '+':
				s.push(num1 + num2);
				break;
			case '-':
				s.push(num1 - num2);
				break;
			case '*':
				s.push(num1 * num2);
				break;
			case '/':
				s.push(num1 / num2);
				break;
			}
			i++; // 移动到下一个字符
		}
        else
        {
            number = 0;
            i++;
        }
    }

        cout << s.top();

    return 0;
}
