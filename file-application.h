#ifndef TASK4_FILE_APPLICATION_H
#define TASK4_FILE_APPLICATION_H

#include <iostream>
#include <string>
#include <fstream>
#include "data-structure.h"

struct FileApplication {
	struct FileRecord {
		struct T {
			int hour = 0;
			int minute = 0;
		};

		typedef long Key;
		Key trail_number = 0;
		std::string departure_point = "A";
		std::string destination_point = "B";
		T time;
		FileRecord();
		FileRecord(Key trail_number, std::string departure_point, std::string destination_point, int hour, int minute);
	};
	typedef long Key;

private:
	std::string filename;
	std::fstream file;
	Data_structure<Key, long>* const DS;
public:
	FileApplication(const std::string&, Data_structure<Key, long>* const); //�����������, ����������� ���� � ��������� ������

	bool insert(const FileRecord&); //�������� ������ � ���� (0 - ������, -1 - ������ � ����� ������ ��� ���� � �����)

	bool erase(const long&); //������� ������ �� �����

	FileRecord get(const Key&); //���������� ������ �� �����

	FileRecord read(const long&); //��������� ������ �� ������� � �����

	void print(); //�������� ��������� ������, ������������ ��� �����

	~FileApplication();
};

std::ostream& operator<<(std::ostream&, const FileApplication::FileRecord&); //�������� ������ ������, � ����������� ����� ������

std::fstream& operator<<(std::fstream&, const FileApplication::FileRecord&); //�������� ������ ������, � ����

FileApplication::FileRecord strToRecord(const std::string&); //����������� ������ � ������

#endif

