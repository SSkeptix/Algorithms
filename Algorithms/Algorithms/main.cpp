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

	for (int i = 0; i < 10; i++) {
		binaryTree.insert(i);
		binaryTree.toJson(out);
		out << ",\n";
	}
	for (int i = 0; i < 10; i++) {
		tree.insert(i);
		tree.toJson(out);
		out << ",\n";
	}

	out << " ]\n";

	return 0;
}