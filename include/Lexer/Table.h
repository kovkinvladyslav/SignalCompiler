#pragma once
#include <string>
#include <unordered_map>
#include <climits>
#include <vector>

class Range {
public:
	int start;
	int current;
	int end;
	Range(int start, int end) : start(start), current(start), end(end) {}
};

class Table {
protected:
	std::unordered_map<std::string, int> table;
	Range range;
	const std::vector<std::string> reservedFields;
	void fill_table();
public:
	int get(const std::string& token) const;
	int append(const std::string& token);
	Table(Range range, const std::vector<std::string>& reservedFieldList);
	void OutputTable();
};




class Tables {
private:
public:

	Table Keywords;
	Table Identifiers;
	Table Delimiters;
	Tables()
		: 
		Keywords(
			Range(401, 500),
			{
				"PROGRAM", "BEGIN", "END", "PROCEDURE" 
			}
		),
		Identifiers(
			Range(1001, INT_MAX),
			{
				"SIGNAL", "COMPLEX", "INTEGER", "FLOAT",
				"BLOCKFLOAT", "EXT"
			}
		),
		Delimiters(
			Range(0, 255),
			{
				";", ",", ":","(", ")"
			}
		)
	{}
	void OutputAllTables();
};