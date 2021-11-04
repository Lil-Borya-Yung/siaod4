#ifndef TASK4_BINARY_TREE_H
#define TASK4_BINARY_TREE_H

#include "data-structure.h"
#include <functional>

template<typename Key, typename Info, typename C = std::less<Key>>
class BinaryTree : public Data_structure<Key, Info, C> {
	struct Node;

	Node* T; //ограничитель

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

	Info* find(const Key&) const; //находит элемент в дереве, возвращает его позицию в файле или -1, если эл. не найден

	bool insert(const Key&, const Info&); //добавляет элемент в дерево

	bool erase(const Key&); //удаляет элемент

	void print() const; //печатает дерево (ключи)

	~BinaryTree();
};



#endif //TASK4_BINARY_TREE_H
