#include "Tree/BinaryTree.h"


int main() {
	BinaryTree<int> tree = BinaryTree<int>();
	int* mass = new int[15]{ 3, 45, 234, 12, 423, 23,645, 75, 234, 324, 36, 12, 72, 78, 77 };

	for (int i = 0; i < 15; i++)
		tree.insert(mass[i]);

	tree.toJson(std::cout);
	std::cout << "\n\n\n";

	tree.remove(3);
	tree.toJson(std::cout);
	std::cout << "\n\n\n";

	tree.remove(2222);
	tree.toJson(std::cout);
	std::cout << "\n\n\n";

	tree.remove(234);
	tree.toJson(std::cout);
	std::cout << "\n\n\n";


	delete mass;
	return 0;
}