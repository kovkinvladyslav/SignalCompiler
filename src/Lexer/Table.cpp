#include <Lexer/Table.h>
#include <algorithm>

void Table::fill_table()
{
	for (const std::string& reservedField : reservedFields) {
		append(reservedField);
	}
}

int Table::get(const std::string& token) const
{
	auto Entry = table.find(token);
	if (Entry != table.end()) {
		return Entry->second;
	}
	else {
		return -1;
	}
}

int Table::append(const std::string& token)
{
	auto newEntry = table.find(token);
	if (newEntry == table.end() && range.current <= range.end) {
		table[token] = range.current++;
	}
	return table[token];
}

Table::Table(Range range, const std::vector<std::string>& reservedFieldList)

	: range(range), reservedFields(reservedFieldList)
{
	fill_table();
}

bool comparator(const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2) {
	return p1.second < p2.second;
}

void Table::OutputTable()
{
	std::vector<std::pair<std::string, int>> ExtractedArray;
	for (auto field : table) {
		ExtractedArray.push_back(field);
	}
	std::sort(ExtractedArray.begin(), ExtractedArray.end(),
		[](const auto& a, const auto& b) {
			return a.second < b.second;
		});
	for (auto Field : ExtractedArray) {
		std::printf("%10s%10d\n", Field.first.c_str(), Field.second);
	}

}



void Tables::OutputAllTables()
{
	printf("\nInformational tables:\n");
	printf("\nKeywords:\n%10s%10s\n", "Identifier", "Code");
	Keywords.OutputTable();

	printf("\nIdentifiers:\n%10s%10s\n", "Identifier", "Code");
	Identifiers.OutputTable();


	printf("\nDelimiters:\n%10s%10s\n", "Delimiter", "Code");
	Delimiters.OutputTable();
}
