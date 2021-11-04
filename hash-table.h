#ifndef TASK4_HASH_TABLE_H
#define TASK4_HASH_TABLE_H
#include "data-structure.h"

template<typename Info>
class HashTable : public Data_structure<long, Info> {
	struct Record {
		long key;
		Info data;
		bool free; //���� "�������� �� ������?"
		bool del; //���� "���� �� ������� ������?"

		Record();
	};
	long capacity;
	long size;
	Record* table;

	long h1(const long&) const; //���-�������, ������������� �������� ����� � ������ �������

	long h2(const long&) const; //���-������, ������������� �������� ��� ��������

	void rehash(); //�-���, ������������� �������, ������ ������� ������������� � 2 ����

public:
	HashTable();

	Info* find(const long&) const;

	bool insert(const long&, const Info&);

	bool erase(const long&);

	void print() const;

	~HashTable();
};

#endif
