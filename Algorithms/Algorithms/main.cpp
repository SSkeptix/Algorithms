#include "HashTable.h"
#include "HashFunctions.h"
#include <iostream>
#include <fstream>

#define CONSOLE_OUTPUT 1

const std::string DataPath = "B:\\study_projects\\Algorithms\\Data\\";
const std::string JsonDataFileName = DataPath + "data.json";
const int VEC_SIZE = 10 * 1000;

int main() {

#if CONSOLE_OUTPUT
	std::ostream& out = std::cout;
#else
	std::ofstream myfile;
	myfile.open(JsonDataFileName);
	std::ostream& out = myfile;
#endif

	// Create test data.
	std::vector<int> testData(VEC_SIZE);
	for (int i = 0; i < VEC_SIZE; i++)
		testData[i] = rand() % 1000*1000;
	
	int realSize = 0;
	HashTable<int, int> table((unsigned)1.4 * VEC_SIZE, hashFunction);
	for (int i = 0; i < VEC_SIZE; i++)
		table[testData[i]] = -testData[i];

	// Retrive data.
	for (int i = 0; i < VEC_SIZE; i++)
		if (table[testData[i]] != -testData[i])
			out << "Error: " << table[testData[i]] << std::endl;

	out << "Finish" << std::endl;
	out << std::endl << std::endl;


	// Test 2 - generate json.
	int testData2length = 10;
	int* testData2 = new int[testData2length]{ 1, 4, 9, 3, 5, 15, 18, 21, 2, 56 };

	HashTable<int, int> table2(testData2length, hashFunction);
	for (int i = 0; i < testData2length; i++)
		table2[testData2[i]] = -testData2[i];
	table2.toJson(out);
	out << std::endl << std::endl;

	out << "Removed key(15): ";
	table2.remove(15);
	table2.toJson(out);
	out << std::endl << std::endl;

	out << "Removed key(1): ";
	table2.remove(1);
	table2.toJson(out);
	out << std::endl << std::endl;

	out << "Inserted key(1), value (100): ";
	table2[1] = 100;
	table2.toJson(out);
	out << std::endl << std::endl;

	out << "Inserted key(31), value (-31): ";
	table2[31] = -31;
	table2.toJson(out);
	out << std::endl << std::endl;


#if !CONSOLE_OUTPUT
	myfile.close();
#endif

	return 0;
}