#include <iostream>
#include <vector>
using namespace std;
class MemoryBlock
{
public:
    int start;
    int size;
    MemoryBlock* next;
	MemoryBlock() :start(-1), size(0), next(nullptr) {};
	MemoryBlock(int start, int size, MemoryBlock* next = nullptr)
	{
		this->start = start;
		this->size = size;
		this->next = next;
	}
};

class FreeList
{
public:
	MemoryBlock* head;
	FreeList() { head = new MemoryBlock(); }

	void allocate(int request_size)
	{
		MemoryBlock* p = head;
		MemoryBlock* q = head->next;
		while (q)
		{
			if (q->size == request_size)
			{
				p->next = q->next;
				delete q;
				break;
			}
			else if (q->size > request_size)
			{
				q->start += request_size;
				q->size -= request_size;
				break;
			}
			p = q;
			q = q->next;
		}
	}

	void release(int start, int size) 
	{
		MemoryBlock* p = head;
		bool merge = false;
		while (p->next)
		{
			if (p && p->next->start > start)
			{
				if (p->size > 0 && p->start + p->size == start)
				{
					p->size += size;
					merge = true;
				}
				if (start + size == p->next->start)
				{
					//merged before
					if (merge)
					{
						p->size += p->next->size;
						MemoryBlock* q = p->next;
						if (q->next) {p->next = q->next;}
						else { p->next = nullptr; }
						delete q;
						return;
					}
					p->next->start = start;
					p->next->size += size;
					return;
				}
				if (!merge)
				{
					MemoryBlock* q = new MemoryBlock(start, size, p->next);
					p->next = q;
					return;
				}
			}
			p = p->next;
		}
		//insert at the end
		if (p->size > 0 && p->start + p->size == start)
		{
			p->size += size;
		}
		else
		{
			MemoryBlock* q = new MemoryBlock(start, size);
			p->next = q;
		}
	}

	~FreeList()
	{
		MemoryBlock *p, *q;
		p = head->next;
		head->next = nullptr;
		while (p)
		{
			q = p->next;
			delete p;
			p = q;
		}
	}
};


int main()
{
	int length;
	cin >> length;
	vector<int> starts(length); 
	vector<int> sizes(length);
	for (int i = 0; i < length; ++i) {
		cin >> starts[i];
	}

	for (int i = 0; i < length; ++i) {
		cin >> sizes[i];
	}

	// initialize the free list
	FreeList freeList = FreeList();
	MemoryBlock* add;
	for (int i = length - 1; i >= 0; i--) {
		add = new MemoryBlock(starts[i], sizes[i], freeList.head->next);
		freeList.head->next = add;
	}

	int m; 
	cin >> m;

	for (int i = 0; i < m; ++i) {
		int op;
		cin >> op;

		if (op == 1) {
			int request_size;
			cin >> request_size;
			freeList.allocate(request_size);
		}
		else if (op == 2) {
			int start, size;
			cin >> start >> size;
			freeList.release(start, size);
		}
	}

	// output the free list
	MemoryBlock* p = freeList.head->next;
	while (p)
	{
		cout << "(" << p->start << "," << p->size << ") ";
		p = p->next;
	}

	return 0;
}

