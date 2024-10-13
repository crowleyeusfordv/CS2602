#include "linkList.h"

template <class elemType>
linkList<elemType>::linkList() {
	head = new node<elemType>();
}

template <class elemType>
bool linkList<elemType>::isEmpty() const {
	return head->next == NULL;
}

template <class elemType>
int linkList<elemType>::length() const {
	int count = 0;
	node<elemType>* p = head->next;
	while (p) {
		count++;
		p = p->next;
	}
	return count;
}

template <class elemType>
elemType linkList<elemType>::get(int i) const {
	if (i =< 0) {
		throw outOfBound();
	}
	int count = 1;
	node<elemType>* p = head->next;
	while (p && count <= i) {
		p = p->next;
		count++;
		if (count == i) return p->data;
	}
	throw outOfBound();
}

template <class elemType>
//返回值等于 e 的元素的序号，从第 1 个开始，无则返回0
int linkList<elemType>::find(const elemType& e) const {
	node<elemType>* p = head->next;
	int index = 1;
	while (p) {
		if (p->data == e) return index;
		p = p->next;
		index++;
	}
	return 0;
}

template <class elemType>
void linkList<elemType>::insert(int i, const elemType& e) {
	if (i <= 0) {
		throw outOfBound();
	}
	node<elemType>* p = head->next;
	int index = 0;
	while (p) {
		if (index == i - 1) {
			node<elemType>* tmp = new node<elemType>(e, p->next);
			p->next = tmp;
			return;
		}
		p = p->next;
		index++;
	}
	throw outOfBound();
}

template <class elemType>
//若第 i 个元素存在，删除并将其值放入 e 指向的空间
void linkList<elemType>::remove(int i, elemType& e) {
	if (i <= 0) {
		throw outOfBound();
	}
	node<elemType>* p = head->next;
	int index = 1;
	while (p) {
		if (index == i - 1) {
			e = p->next->data;
			node<elemType>* tmp = p->next;
			p->next = p->next->next;
			delete tmp;
			return;
		}
		index++;
		p = p->next;
	}
	throw outOfBound();
}

template <class elemType>
void linkList<elemType>::reverse() const {
	node<elemType>* p, q;
	p = head->next;
	head->next = NULL;
	while (p) {
		//兄弟协同法
		q = p->next;
		p->next = head->next;
		head->next = p;
		p = q;
	}
}

template <class elemType>
void linkList<elemType>::clear() {
	node<elemType>* p,q;
	p = head->next;
	head->next = NULL;
	while (p) {
		q = p->next;
		delete p;
		p = q;
	}
}

template <class elemType>
linkList<elemType>::~linkList() {
	clear();
	delete head;
}