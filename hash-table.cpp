#include "hash-table.h"
#include <iostream>

template<typename Info>
HashTable<Info>::Record::Record() :
	free(true),
	del(false)
{}

template<typename Info>
HashTable<Info>::HashTable() :
	capacity(64),
	size(0),
	table(new Record[64])
{}

template<typename Info>
long HashTable<Info>::h1(const long& key) const {
	return (key % capacity);
}

template<typename Info>
long HashTable<Info>::h2(const long& key) const {
	long shift = (key / capacity) % capacity;
	shift += 1 - (shift % 2);//делаем сдвиг нечетным
	// 0 < shift < capacity
	return shift;
}

template<typename Info>
void HashTable<Info>::rehash() {
	Record* oldTable = table;
	long old_capacity = capacity;
	capacity <<= 1;
	size = 0;
	table = new Record[capacity];
	for (long i = 0; i < old_capacity; ++i)
		if (!oldTable[i].free) insert(oldTable[i].key, oldTable[i].data);

	delete[] oldTable;
}

template<typename Info>
bool HashTable<Info>::insert(const long& key, const Info& data) {
	if (find(key)) return false;
	long i = h1(key);
	long shift = h2(key);
	while (!table[i].free)
		i = (i + shift) % capacity;

	table[i].key = key;
	table[i].data = data;
	table[i].free = false;
	table[i].del = false;
	++size;
	if ((double)size / capacity > 0.75) rehash();
	return true;
}

template<typename Info>
bool HashTable<Info>::erase(const long& key) {
	long i = h1(key);
	long shift = h2(key);

	while ((!table[i].free && table[i].key != key) || table[i].del)
		i = (i + shift) % capacity;

	if (table[i].key == key) {
		table[i].free = true;
		table[i].del = true;
		return true;
	}
	else return false;
}

template<typename Info>
Info* HashTable<Info>::find(const long& key) const {
	long i = h1(key);
	long shift = h2(key);

	while ((!table[i].free && table[i].key != key) || table[i].del)
		i = (i + shift) % capacity;

	if (table[i].key == key) return &(table[i].data);
	else return nullptr;
}

template<typename Info>
void HashTable<Info>::print() const {
	std::cout << '\n';
	for (long i = 0; i < capacity; ++i)
		if (!(table[i].free)) std::cout << "index: " << i << " \tkey: " << table[i].key << " \tdata: " << table[i].data << '\n';
	std::cout << '\n';
}

template<typename Info>
HashTable<Info>::~HashTable() {
	delete[] table;
}