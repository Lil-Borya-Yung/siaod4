#ifndef TASK4_RB_TREE_H
#define TASK4_RB_TREE_H

#include "data-structure.h"
#include <functional>

template<typename Key, typename Info, typename C = std::less<Key>>
class RB_Tree : public Data_structure<Key, Info, C> {
	struct Node;

	Node* T;

	enum Colors { RED, BLACK };
	struct Node {
		Key k;
		Info data;
		Node* parent;
		Node* left;
		Node* right;
		Colors color;

		Node();

		Node(Key, Info, Node*, Node*, Node*, Colors);
	};

	Node* root;

	C cmp;
    double rotations = 0, addedcount = 0;

	void left_rotate(Node*); //x смещается вниз влево и x->right становится на место x

	void right_rotate(Node*); //x смещается вниз вправа и x->right становится на место x

	void insert_fixup(Node*);
	/*восстанавливается свойства красно-черного дерева, после вставки узла.
	ф-ция insert вставляет красный узел, могут быть нарушены два свойства RB-Tree:
		1. корень дерева является черным узлом (свойство восстанавливается root->color = BLACK)
		2. если узел красный, то оба его дочерних узла черные (предок узла - красный)
				(свойство восстанавливается путем перекрашивания узлов и поворотов поддеревьев)
	*/
	void transplant(Node*, Node*); //заменяет узел u на v

	void erase_fixup(Node*);
	/*если был удален черный узел, то могут быть нарушены три свойства RB-Tree:
		1. корень дерева является черным узлом (был удален черный корень, вместо него стоит красный элемент)
		2. если узел красный, то оба его дочерних узла черные
		3. любой простой путь от узла к его листьям содержит одно и тоже кол-во черных узлов
	*/

	void print(Node*, int h = 0) const;

public:
	RB_Tree();

	Info* find(const Key&) const; //находит элемент в дереве, возвращает его позицию в файле или -1, если эл не найден

	bool insert(const Key&, const Info&); //добавить элемент в дерево

	bool erase(const Key&); //удаляет элемент

	void print() const; //печатает дерево

    double get_average_rotations();

	~RB_Tree();
};

#endif //TASK4_RB_TREE_H
