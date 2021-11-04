#include "data-structure.h"
#include "file-application.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

FileApplication::FileRecord::FileRecord() {}

FileApplication::FileRecord::FileRecord(Key trail_number, std::string departure_point, std::string destination_point, int hour, int minute) :
	trail_number(trail_number),
	departure_point(departure_point),
	destination_point(destination_point) {
	time.hour = hour;
	time.minute = minute;
}

FileApplication::FileApplication(const std::string& filename, Data_structure<Key, long>* const DS) :
	filename(filename),
	file(filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate),
	DS(DS) {
	file.seekg(0, std::ios::beg);
	//if (!file) throw 's';
	while (!file.eof()) {
		long pos = file.tellg();
		std::string str;
		getline(file, str);
		if (str != "") DS->insert((strToRecord(str)).trail_number, pos); //условие необходимо, если в конце файла '\n'
	}
	file.clear();
}

bool FileApplication::insert(const FileApplication::FileRecord& r) {
	file.seekp(0, std::ios::end);
	long pos = file.tellp();

	if (!DS->insert(r.trail_number, pos)) return false;

	file << r << '\n';
	return true;
}

bool FileApplication::erase(const long& key) {
	if (!(DS->find(key))) return false; //в файле нет записи с ключем key
	std::vector<std::string> temp;
	file.seekg(0, std::ios::beg);
	while (!file.eof()) {
		std::string str;
		getline(file, str);
		if (str != "") temp.push_back(str);
	}
	file.close();

	file.open(filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
	for (long i = 0; i < temp.size(); ++i) {
		FileApplication::FileRecord r = strToRecord(temp[i]);
		if (r.trail_number != key) {
			if (DS->find(r.trail_number))
				*(DS->find(r.trail_number)) = file.tellp();
			else
				DS->insert(r.trail_number, file.tellp());
			file << temp[i] << '\n';
		}
		else
			DS->erase(r.trail_number);
	}
	return true;
}

FileApplication::FileRecord FileApplication::get(const Key& key) {
	FileApplication::FileRecord r;
	if (DS->find(key))
		r = read(*(DS->find(key)));
	return r;
}

FileApplication::FileRecord FileApplication::read(const long& pos) {
	std::string str;
	FileApplication::FileRecord r;
	try {
		file.seekg(pos, std::ios::beg);
		getline(file, str);
		r = strToRecord(str);
	}
	catch (...) {}

	file.clear();
	return r;
}

void FileApplication::print() {
	DS->print();
}

FileApplication::~FileApplication() {
	file.close();
	delete DS;
}


std::ostream& operator<<(std::ostream& out, const FileApplication::FileRecord& r) {
	out << r.trail_number << ' ' << r.departure_point << " -> " << r.destination_point <<
		' ' << r.time.hour << ':' << r.time.minute;
	return out;
}

std::fstream& operator<<(std::fstream& out, const FileApplication::FileRecord& r) {
	out << r.trail_number << '|' << r.departure_point << "|" << r.destination_point <<
		'|' << r.time.hour << ':' << r.time.minute;
	return out;
}

FileApplication::FileRecord strToRecord(const std::string& str) {
	FileApplication::FileRecord r;
	r.trail_number = 0;
	int i = 0;
	while ((i < str.size()) && (str[i] != '|'))
		r.trail_number = r.trail_number * 10 + str[i++] - '0';

	int pos = ++i;
	while ((i < str.size()) && (str[i] != '|')) ++i;
	r.departure_point = str.substr(pos, i - pos);

	pos = ++i;
	while ((i < str.size()) && (str[i] != '|')) ++i;
	r.destination_point = str.substr(pos, i - pos);

	++i;
	r.time.hour = 0;
	while ((i < str.size()) && (str[i] != ':'))
		r.time.hour = r.time.hour * 10 + str[i++] - '0';

	++i;
	r.time.minute = 0;
	while ((i < str.size()))
		r.time.minute = r.time.minute * 10 + str[i++] - '0';

	return r;
}