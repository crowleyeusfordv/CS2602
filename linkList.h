#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED


class outOfBound {}; // �쳣�࣬Խ��

template <class elemType>
class linkList;// ǰ������

template <class elemType>
class node {
	friend class linkList<elemType>;
private:
	elemType data;
	node<elemType>* next;
public:
	node() :next(NULL) {};
	node(const elemType& e, node<elemType>* N = NULL) {
		data = e;
		next = N;
	}
};

template <class elemType>
class linkList {
	private:
		node<elemType>* head;
	public:
		linkList();
		bool isEmpty() const;
		bool isFull() const { return false; };
		int length() const;
		elemType get(int i) const;
		int find(const elemType& e) const;
		void insert(int i, const elemType& e);
	    //���� i ��Ԫ�ش��ڣ�ɾ��������ֵ���� e ָ��Ŀռ�
		void remove(int i, elemType& e);
		void reverse() const;
		void clear();
		~linkList();
};

#endif