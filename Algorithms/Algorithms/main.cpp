#include <iostream>
#include <fstream>
#include "AsymptoticAnalyst.h"
#include "Tree/BinaryTree.h"
#include "Tree/BlackRedTree.h"
#include "HashTable.h"
#include "HashFunctions.h"

#define CONSOLE_OUTPUT 1
const std::string DataPath = "B:\\study_projects\\Algorithms\\Data\\";
const std::string JsonDataFileName = DataPath + "data.json";
static ull iterationCount;
static int randomSize = 2500000;
static std::vector<ull> randomValues(randomSize);


void BinaryTreeSequentialInsert(std::ostream& out, std::vector<ull>& iterations)
{
	out << "=== Binary tree, sequential insert ===" << std::endl;
	AsymptoticAnalyst analist;

	for (unsigned i = 0; i < iterations.size(); i++)
	{
		iterationCount = iterations[i];
		analist.measure(iterationCount, [](std::function<void()> start, std::function<void()> end) {
			BinaryTree<ull> binaryTree;
			start();
			for (ull i = 0; i < iterationCount; i++)
				binaryTree.insert(i);
			end();
		});
	}

	analist.getResult(out);
	out << std::endl << std::endl;
}

void BinaryTreeRandomInsert(std::ostream& out, std::vector<ull>& iterations)
{
	out << "=== Binary tree, random insert ===" << std::endl;
	AsymptoticAnalyst analist;

	for (unsigned i = 0; i < iterations.size(); i++)
	{
		iterationCount = iterations[i];
		analist.measure(iterationCount, [](std::function<void()> start, std::function<void()> end) {
			BinaryTree<ull> binaryTree;
			start();
			for (ull i = 0; i < iterationCount; i++)
				binaryTree.insert(randomValues[i]);
			end();
		});
	}

	analist.getResult(out);
	out << std::endl << std::endl;
}

void BinaryTreeRandomFind(std::ostream& out, std::vector<ull>& iterations)
{
	out << "=== Binary tree, find from random insert ===" << std::endl;
	AsymptoticAnalyst analist;

	for (unsigned i = 0; i < iterations.size(); i++)
	{
		iterationCount = iterations[i];
		analist.measure(iterationCount, [](std::function<void()> start, std::function<void()> end) {
			BinaryTree<ull> binaryTree;
			for (ull i = 0; i < iterationCount; i++)
				binaryTree.insert(randomValues[i]);
			start();
			for (ull i = 0; i < iterationCount; i++)
				binaryTree.find(randomValues[i]);
			end();
		});
	}

	analist.getResult(out);
	out << std::endl << std::endl;
}


void RedBlackTreeSequentialInsert(std::ostream& out, std::vector<ull>& iterations)
{
	out << "=== Red black tree, sequential insert ===" << std::endl;
	AsymptoticAnalyst analist;

	for (unsigned i = 0; i < iterations.size(); i++)
	{
		iterationCount = iterations[i];
		analist.measure(iterationCount, [](std::function<void()> start, std::function<void()> end) {
			BlackRedTree<ull> blackRedTree;
			start();
			for (ull i = 0; i < iterationCount; i++)
				blackRedTree.insert(i);
			end();
		});
	}

	analist.getResult(out);
	out << std::endl << std::endl;
}

void RedBlackTreeRandomInsert(std::ostream& out, std::vector<ull> iterations)
{
	out << "=== Red black tree, random insert ===" << std::endl;
	AsymptoticAnalyst analist;

	for (unsigned i = 0; i < iterations.size(); i++)
	{
		iterationCount = iterations[i];
		analist.measure(iterationCount, [](std::function<void()> start, std::function<void()> end) {
			BlackRedTree<ull> blackRedTree;
			start();
			for (ull i = 0; i < iterationCount; i++)
				blackRedTree.insert(randomValues[i]);
			end();
		});
	}

	analist.getResult(out);
	out << std::endl << std::endl;
}

void RedBlackTreeRandomFind(std::ostream& out, std::vector<ull> iterations)
{
	out << "=== Red black tree, find from random insert ===" << std::endl;
	AsymptoticAnalyst analist;

	for (unsigned i = 0; i < iterations.size(); i++)
	{
		iterationCount = iterations[i];
		analist.measure(iterationCount, [](std::function<void()> start, std::function<void()> end) {
			BlackRedTree<ull> blackRedTree;
			for (ull i = 0; i < iterationCount; i++)
				blackRedTree.insert(randomValues[i]);
			start();
			for (ull i = 0; i < iterationCount; i++)
				blackRedTree.find(randomValues[i]);
			end();
		});
	}

	analist.getResult(out);
	out << std::endl << std::endl;
}


THash hf(ull key) {
	return (THash)key;
}

void HashTableSequentialInsert(std::ostream& out, std::vector<ull> iterations)
{
	out << "=== Hash table, sequential insert ===" << std::endl;
	AsymptoticAnalyst analist;

	for (unsigned i = 0; i < iterations.size(); i++)
	{
		iterationCount = iterations[i];
		analist.measure(iterationCount, [](std::function<void()> start, std::function<void()> end) {
			HashTable<ull, ull> hashTable((unsigned)(iterationCount * 1.3), hf);
			start();
			for (ull i = 0; i < iterationCount; i++)
				hashTable.insert(i, i);
			end();
		});
	}

	analist.getResult(out);
	out << std::endl << std::endl;
}

void HashTableTreeRandomInsert(std::ostream& out, std::vector<ull> iterations)
{
	out << "=== Hash table, sequential insert ===" << std::endl;
	AsymptoticAnalyst analist;

	for (unsigned i = 0; i < iterations.size(); i++)
	{
		iterationCount = iterations[i];
		analist.measure(iterationCount, [](std::function<void()> start, std::function<void()> end) {
			HashTable<ull, ull> hashTable((unsigned)(iterationCount * 1.3), hf);
			start();
			for (ull i = 0; i < iterationCount; i++)
				hashTable.insert(randomValues[i], i);
			end();
		});
	}

	analist.getResult(out);
	out << std::endl << std::endl;
}


int main() {

#if CONSOLE_OUTPUT
	std::ostream& out = std::cout;
#else
	std::ofstream myfile;
	myfile.open(JsonDataFileName);
	std::ostream& out = myfile;
#endif
	std::vector<ull> vec1;
	for (ull i = 500; i < 8000; i = (ull)(i*1.7))
		vec1.push_back(i);

	std::vector<ull> vec2;
	for (ull i = 500; i < randomSize; i *= 2)
		vec2.push_back(i);

	for (ull i = 0; i < randomSize; i++)
		randomValues[i] = i;
	for (int i = randomSize - 1; i > 0; i--)
		std::swap(randomValues[i], randomValues[rand() % i]);

	BinaryTreeSequentialInsert(out, vec1);
	BinaryTreeRandomInsert(out, vec2);
	BinaryTreeRandomFind(out, vec2);
	RedBlackTreeSequentialInsert(out, vec2);
	RedBlackTreeRandomInsert(out, vec2); 
	RedBlackTreeRandomFind(out, vec2);
	HashTableSequentialInsert(out, vec2);
	HashTableTreeRandomInsert(out, vec2);

#if !CONSOLE_OUTPUT
	myfile.close();
#endif
	return 0;
}