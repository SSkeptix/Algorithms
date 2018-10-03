#include "Tree/BinaryTree.h"
#include <iostream>
#include <fstream>

const std::string DataPath = "B:\\study_projects\\Algorithms\\Data\\";
const std::string JsonDataFileName = DataPath + "data.json";

int main() {
	BinaryTree<int> tree = BinaryTree<int>();
	int* mass = new int[15]{ 3, 45, 234, 12, 423, 23, 645, 75, 234, 324, 36, 12, 72, 78, 77 };

	std::ofstream myfile;
	myfile.open(JsonDataFileName);
	
	std::ostream& out = myfile;

	for (int i = 0; i < 15; i++)
		tree.insert(mass[i]);

	out << "[ ";
	tree.toJson(out);
	out << ",\n";

	tree.remove(3);
	tree.toJson(out);
	out << ",\n";

	tree.remove(2222);
	tree.toJson(out);
	out << ",\n";

	tree.remove(234);
	tree.toJson(out);
	out << " ]\n";

	myfile.close();

	delete mass;
	return 0;
}