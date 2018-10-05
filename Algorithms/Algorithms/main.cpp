#include "Tree/BinaryTree.h"
#include "Tree/BlackRedTree.h"
#include <iostream>
#include <fstream>

const std::string DataPath = "B:\\study_projects\\Algorithms\\Data\\";
const std::string JsonDataFileName = DataPath + "data.json";

int main() {
	BinaryTree<int> binaryTree;
	BlackRedTree<int> tree;

	std::ofstream myfile;
	myfile.open(JsonDataFileName);
	std::ostream& out = myfile;

	out << "[ ";

	// Case 1 - check root deletion.
	tree.insert(0);
	tree.remove(0);
	tree.toJson(out);
	out << ",\n";

	for (int i = 0; i < 38; i++)
		tree.insert(i);

	// Case 4 & 3.
	tree.remove(15);
	tree.toJson(out);
	out << ",\n";

	// Case 2 & 4.
	tree.remove(32);
	tree.toJson(out);
	out << ",\n";

	tree.remove(37);
	tree.toJson(out);
	out << ",\n";

	tree.remove(33);
	tree.toJson(out);
	out << ",\n";

	// Case 5 & 6.
	BlackRedTree<int> tree2;
	tree2.toJson(out);
	out << ",\n";
	for (int i = 0; i < 36; i++)
		tree2.insert(i);
	tree2.insert(37);
	tree2.insert(36);
	tree2.toJson(out);
	out << ",\n";
	tree2.remove(34);
	tree2.toJson(out);

	out << " ]\n";

	return 0;
}