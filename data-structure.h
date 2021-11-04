#ifndef TASK4_DATA_STRUCTURE_H
#define TASK4_DATA_STRUCTURE_H

#include <functional>

template<typename Key, typename Info, typename C = std::less<Key>>
class Data_structure {
protected:
	Data_structure() {}

public:
	virtual Info* find(const Key&) const { return nullptr; }//������� �������, ���������� ��������� �� ��� �������������� ����� ��� nullptr

	virtual bool insert(const Key&, const Info&) { return false; }//��������� �������

	virtual bool erase(const Key&) { return false; }//������� �������

	virtual void print() const {}//����������� ���� ������

	virtual ~Data_structure() {}
};

#endif //TASK4_DATA_STRUCTURE_H