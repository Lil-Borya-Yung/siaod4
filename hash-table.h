#ifndef TASK4_HASH_TABLE_H
#define TASK4_HASH_TABLE_H
#include "data-structure.h"

template<typename Info>
class HashTable : public Data_structure<long, Info> {
	struct Record {
		long key;
		Info data;
		bool free; //флаг "свободна ли €чейка?"
		bool del; //флаг "была ли удалена €чейка?"

		Record();
	};
	long capacity;
	long size;
	Record* table;

	long h1(const long&) const; //хеш-функци€, преобразующа€ значение ключа в индекс таблицы

	long h2(const long&) const; //хеш-фукци€, расчитывающа€ смещение при коллизии

	void rehash(); //ф-ци€, рехешировани€ таблицы, размер таблицы увеличиваетс€ в 2 раза

public:
	HashTable();

	Info* find(const long&) const;

	bool insert(const long&, const Info&);

	bool erase(const long&);

	void print() const;

	~HashTable();
};

#endif
