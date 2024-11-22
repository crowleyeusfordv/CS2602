//存储Huffman结点
template <class elemType>
struct HuffmanNode
{
    elemType data;
    double weight;
    int parent;
    int left, right;
};

//在所有父亲为0的元素中找最小值的下标
template <class elemType>
int minIndex(HuffmanNode<elemType> Bt[], int k, int m)
{
    int i, min, minWeight = 9999;//用一个不可能且很大的权值

	for (i = 1; i <= m; i++)
	{
		if (Bt[i].parent == 0 && Bt[i].weight < minWeight)
		{
			minWeight = Bt[i].weight;
			min = i;
		}
	}
	return min;
}

template <class elemType>
HuffmanNode<elemType>* BestBinaryTree(elemType a[], double w[], int n)
{
	HuffmanNode<elemType>* BBTree;
	int first_min, second_min;
	int m = n * 2;//共2n-1个结点，下标为0处不放结点
	int i, j;
	//从数组中从后往前存储叶子结点
	BBTree = new HuffmanNode<elemType>[m];
	for (j = 0; j < n; j++)
	{
		i = m - 1 - j;
		BBTree[i].data = a[j];
		BBTree[i].weight = w[j];
		BBTree[i].parent = 0;
		BBTree[i].left = 0;
		BBTree[i].right = 0;
	}
	i = n - 1;//i is the position which is ready for the first new node
	while (i != 0)//数组左侧尚有未用空间，即新创建的结点个数还不足
	{
		first_min = minIndex(BBTree, i, m);
		BBTree[first_min].parent = i;
		second_min = minIndex(BBTree, i, m);
		BBTree[second_min].parent = i;

		BBTree[i].weight = BBTree[first_min].weight + BBTree[second_min].weight;
		BBTree[i].parent = 0;
		BBTree[i].left = first_min;
		BBTree[i].right = second_min;
		i--;
	}
	return BBTree;
}

template <class elemType>
char** HuffmanCode(HuffmanNode<elemType> BBTree[], int n)
//n为待编码元素的个数，BBTree数组为Huffman树，数组长度为2n
{
	seqStack<char> s;
	char** HFCode;
	char zero = '0', one = '1';
	int m, i, j, parent, child;

	//为HFCode分配空间
	HFCode = new char* [n];
	for (i = 0; i < n; i++)
	{
		HFCode[i] = new char[n + 1];
	}
	m = 2 * n;//BBTree数组长度
	if (n == 0) return HFCode;//没有元素
	if (n == 1)//只有一个元素
	{
		HFCode[0][0] = '0';
		HFCode[0][1] = '\0';
		return HFCode;
	}
	for (i = m - 1; i >= n; i--)
	{
		child = i;
		parent = BBTree[child].parent;
		while (parent != 0)
		{
			if (BBTree[parent].left == child)
			{
				s.push(zero);
			}
			else
			{
				s.push(one);
			}
			child = parent;
			parent = BBTree[child].parent;
		}
		j = 0;
		while (!s.isEmpty())
		{
			HFCode[m - i - 1][j] = s.top();
			s.pop();
			j++;
		}
		HFCode[m - i - 1][j] = '\0';
	}
	return HFCode;
}