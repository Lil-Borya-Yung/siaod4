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

	void left_rotate(Node*); //x ��������� ���� ����� � x->right ���������� �� ����� x

	void right_rotate(Node*); //x ��������� ���� ������ � x->right ���������� �� ����� x

	void insert_fixup(Node*);
	/*����������������� �������� ������-������� ������, ����� ������� ����.
	�-��� insert ��������� ������� ����, ����� ���� �������� ��� �������� RB-Tree:
		1. ������ ������ �������� ������ ����� (�������� ����������������� root->color = BLACK)
		2. ���� ���� �������, �� ��� ��� �������� ���� ������ (������ ���� - �������)
				(�������� ����������������� ����� �������������� ����� � ��������� �����������)
	*/
	void transplant(Node*, Node*); //�������� ���� u �� v

	void erase_fixup(Node*);
	/*���� ��� ������ ������ ����, �� ����� ���� �������� ��� �������� RB-Tree:
		1. ������ ������ �������� ������ ����� (��� ������ ������ ������, ������ ���� ����� ������� �������)
		2. ���� ���� �������, �� ��� ��� �������� ���� ������
		3. ����� ������� ���� �� ���� � ��� ������� �������� ���� � ���� ���-�� ������ �����
	*/

	void print(Node*, int h = 0) const;

public:
	RB_Tree();

	Info* find(const Key&) const; //������� ������� � ������, ���������� ��� ������� � ����� ��� -1, ���� �� �� ������

	bool insert(const Key&, const Info&); //�������� ������� � ������

	bool erase(const Key&); //������� �������

	void print() const; //�������� ������

    double get_average_rotations();

	~RB_Tree();
};

#endif //TASK4_RB_TREE_H
