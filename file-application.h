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
	FileApplication(const std::string&, Data_structure<Key, long>* const); //конструктор, прочитывает файл и заполняет дерево

	bool insert(const FileRecord&); //добавить запись в файл (0 - удачно, -1 - запись с таким ключем уже есть в файле)

	bool erase(const long&); //удалить запись из файла

	FileRecord get(const Key&); //возвращает запись по ключу

	FileRecord read(const long&); //возращает запись по позиции в файле

	void print(); //печатает структуру данных, используемую для файла

	~FileApplication();
};

std::ostream& operator<<(std::ostream&, const FileApplication::FileRecord&); //оператор вывода записи, в стандартный поток вывода

std::fstream& operator<<(std::fstream&, const FileApplication::FileRecord&); //оператор вывода записи, в файл

FileApplication::FileRecord strToRecord(const std::string&); //преобразует строку в запись

#endif

