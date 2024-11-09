// binarySearchTree.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

template<class elemType>
class binarySearchTree;

template <class elemType>
class Node
{
    friend class binarySearchTree<elemType>;
private:
    elemType data;
    Node* left, * right;      int factor; //平衡因子
public:
    Node() { left = NULL; right = NULL; }
    Node(const elemType& x, Node* l = NULL, Node* r = NULL)
    {
        data = x; left = l; right = r;
    }
};

template <class elemType>
class binarySearchTree
{
private:
    Node<elemType>* root;
    bool search(const elemType& x, Node<elemType>* t) const;
    void insert(const elemType& x, Node<elemType>*& t);
    void remove(const elemType& x, Node<elemType>*& t);
public:
    binarySearchTree() { root = NULL; }
    bool search(const elemType& x) const;
    void insert(const elemType& x);
    void remove(const elemType& x);
    void levelTravese() const;//层次遍历,用于验证插入、删除操作
    ~binarySearchTree();
};

template <class elemType>
bool binarySearchTree<elemType>::search(const elemType& x) const {
    return search(x, root);
}

template <class elemType>
bool binarySearchTree<elemType>::search(const elemType& x, Node<elemType>* t) const
{
    if (!t) return false;
    if (x == t->data) return true;
    if (x < t->data)
        return search(x, t->left);
    else
        return search(x, t->right);
}