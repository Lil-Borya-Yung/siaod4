#include "RB-tree.h"
#include <iostream>
#include <stack>

template<typename Key, typename Info, typename C>
RB_Tree<Key, Info, C>::Node::Node() {}

template<typename Key, typename Info, typename C>
RB_Tree<Key, Info, C>::Node::Node(Key k, Info data, Node* parent, Node* left, Node* right, Colors color) :
	k(k),
	data(data),
	parent(parent),
	left(left),
	right(right),
	color(color) {}

template<typename Key, typename Info, typename C>
RB_Tree<Key, Info, C>::RB_Tree() {
	T = new Node();
	T->color = BLACK;
	root = T;
}

template<typename Key, typename Info, typename C>
Info* RB_Tree<Key, Info, C>::find(const Key& k) const {
	Node* q = root;
	while (q != T && q->k != k) {
		if (cmp(q->k, k))
			q = q->right;
		else
			q = q->left;
	}
	if (q != T) return &(q->data);
	else return nullptr;
}

template<typename Key, typename Info, typename C>
void RB_Tree<Key, Info, C>::left_rotate(Node* x) {
    ++rotations;
	Node* y = x->right;
	x->right = y->left;
	if (y->left != T)
		y->left->parent = x;
	y->parent = x->parent;
	if (T == x->parent)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
}

template<typename Key, typename Info, typename C>
void RB_Tree<Key, Info, C>::right_rotate(Node* x) {
    ++rotations;
	Node* y = x->left;
	x->left = y->right;
	if (y->right != T)
		y->right->parent = x;

	y->parent = x->parent;
	if (T == x->parent)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->right = x;
	x->parent = y;
}

template<typename Key, typename Info, typename C>
void RB_Tree<Key, Info, C>::insert_fixup(Node* z) {
	while (z->parent->color == RED) {
		if (z->parent == z->parent->parent->left) { //дядя z справа от деда
			Node* y = z->parent->parent->right;
			if (y->color == RED) { //имеем: отец и дядя z - красные, дед - черный
				z->parent->color = BLACK;
				y->color = BLACK;
				z = z->parent->parent;
				z->color = RED; //при окрашивании деда в красный могли возникнуть те же нарушения свойств
			}
			else { //дядя и дед - черные, отец - красный
				if (z == z->parent->right) {
					z = z->parent;
					left_rotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		}
		else {//дядя z слева
			Node* y = z->parent->parent->left;
			if (y->color == RED) {
				z->parent->color = BLACK;
				y->color = BLACK;
				z = z->parent->parent;
				z->color = RED;
			}
			else {
				if (z == z->parent->left) {
					z = z->parent;
					right_rotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}
	root->color = BLACK;
}


template<typename Key, typename Info, typename C>
bool RB_Tree<Key, Info, C>::insert(const Key& k, const Info& data) {
    ++addedcount;
	Node* y = T; //родитель x
	Node* x = root;
	while (x != T) {
		y = x;
		if (x->k == k) return false;//узел с таким ключем уже есть
		if (cmp(x->k, k))
			x = x->right;
		else
			x = x->left;
	}
	Node* z = new Node(k, data, y, T, T, RED); //новый узел, красный
	if (y == T)
		root = z;
	else if (y->k < k)
		y->right = z;
	else
		y->left = z;
	insert_fixup(z);
	return true;
}

template<typename Key, typename Info, typename C>
void RB_Tree<Key, Info, C>::transplant(Node* u, Node* v) {
	if (root == u)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	v->parent = u->parent;
}

template<typename Key, typename Info, typename C>
void RB_Tree<Key, Info, C>::erase_fixup(Node* x) {
	//здесь узел x дополнительно черный (дважды черный)
	while (x != root && x->color == BLACK) {
		if (x == x->parent->left) {
			Node* y = x->parent->right;
			if (y->color == RED) {
				y->color = BLACK;
				x->parent->color = RED;
				left_rotate(x->parent);
				y = x->parent->right;
			}
			if (y->left->color == BLACK && y->right->color == BLACK) {
				y->color = RED;
				x = x->parent;
			}
			else {
				if (y->right->color == BLACK) {
					y->left->color = BLACK;
					y->color = RED;
					right_rotate(y);
					y = x->parent->right;
				}
				y->color = x->parent->color;
				x->parent->color = BLACK;
				y->right->color = BLACK;
				left_rotate(x->parent);
				x = root;
			}
		}
		else {
			Node* y = x->parent->left;
			if (y->color == RED) {
				y->color = BLACK;
				x->parent->color = RED;
				right_rotate(x->parent);
				y = x->parent->left;
			}
			if (y->left->color == BLACK && y->right->color == BLACK) {
				y->color = RED;
				x = x->parent;
			}
			else {
				if (y->left->color == BLACK) {
					y->right->color = BLACK;
					y->color = RED;
					left_rotate(y);
					y = x->parent->left;
				}
				y->color = x->parent->color;
				x->parent->color = BLACK;
				y->left->color = BLACK;
				right_rotate(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

template<typename Key, typename Info, typename C>
bool RB_Tree<Key, Info, C>::erase(const Key& k) {
	Node* z = root;
	while (z != T && z->k != k) {
		if (cmp(z->k, k))
			z = z->right;
		else
			z = z->left;
	}
	if (z == T) return false;

	Node* y = z; //узел, по факту удаляемый
	Colors y_original_color = y->color;//цвет удаленного узла, если RED, то после удаления свойства rb-tree не будут нарушены
	Node* x; //узел, начиная с которого могут быть нарушены свойства rb-tree (ниже него всё ОК)
	if (z->left == T) {
		x = z->right;
		transplant(z, z->right);
	}
	else if (z->right == T) {
		x = z->left;
		transplant(z, z->left);
	}
	else {
		//ищем минимальный узел в правом поддереве
		y = z->right;
		while (y->left != T) y = y->left;
		y_original_color = y->color;
		//
		x = y->right;
		if (y->parent == z)
			x->parent = y; //x может быть T
		else {
			transplant(y, y->right);//здесь так же x->parent = y
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (y_original_color == BLACK)
		erase_fixup(x);
	return true;
}

template<typename Key, typename Info, typename C>
void RB_Tree<Key, Info, C>::print(Node* q, int h) const {
	if (q == T) return;
	print(q->right, h + 1);
	for (int i = 0; i < h; ++i)
		std::cout << '\t';
	std::cout << q->k << ' ' << q->data << ' ' << (q->color == RED ? 'R' : 'B') << '\n';
	print(q->left, h + 1);
}

template<typename Key, typename Info, typename C>
void RB_Tree<Key, Info, C>::print() const {
	std::cout << '\n';
	print(root);
	std::cout << '\n';
}

template<typename Key, typename Info, typename C>
RB_Tree<Key, Info, C>::~RB_Tree() {
	std::stack<Node*> S;
	if (root != T) S.push(root);
	while (!S.empty()) {
		Node* q = S.top();
		S.pop();
		if (q->left != T) S.push(q->left);
		if (q->right != T) S.push(q->right);
		delete q;
	}
	delete T;
}
template<typename Key, typename Info, typename C>
double RB_Tree<Key,Info, C>::get_average_rotations() {
    return rotations/addedcount;
}
