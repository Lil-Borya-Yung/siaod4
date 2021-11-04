#ifndef TASK4_BINARY_TREE_H
#define TASK4_BINARY_TREE_H

#include "data-structure.h"
#include <functional>

template<typename Key, typename Info, typename C = std::less<Key>>
class BinaryTree : public Data_structure<Key, Info, C> {
	struct Node;

	Node* T; //������������

	struct Node {
		Key k;
		Info data;
		Node* parent;
		Node* left;
		Node* right;

		Node();

		Node(Key, Info, Node*, Node*, Node*);
	};

	Node* root;

	C cmp;

	void print(Node*, int h = 0) const;

public:

	BinaryTree();

	Info* find(const Key&) const; //������� ������� � ������, ���������� ��� ������� � ����� ��� -1, ���� ��. �� ������

	bool insert(const Key&, const Info&); //��������� ������� � ������

	bool erase(const Key&); //������� �������

	void print() const; //�������� ������ (�����)

	~BinaryTree();
};



#endif //TASK4_BINARY_TREE_H
