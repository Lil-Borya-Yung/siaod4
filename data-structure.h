#ifndef TASK4_DATA_STRUCTURE_H
#define TASK4_DATA_STRUCTURE_H

#include <functional>

template<typename Key, typename Info, typename C = std::less<Key>>
class Data_structure {
protected:
	Data_structure() {}

public:
	virtual Info* find(const Key&) const { return nullptr; }//находит элемент, возвращает указатель на его информационную часть или nullptr

	virtual bool insert(const Key&, const Info&) { return false; }//добавляет элемент

	virtual bool erase(const Key&) { return false; }//удаляет элемент

	virtual void print() const {}//отображение базы данных

	virtual ~Data_structure() {}
};

#endif //TASK4_DATA_STRUCTURE_H