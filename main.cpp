#include <HashTable.h>
#include <LinkedList.h>
#include <Timer.h>
#include <BinarySearchTree.h>
#include <AVLTree.h>
#include <random>
#include <iostream>
#include <functional>
#include <algorithm>
#include <exception>
#include <vector>

const std::string randomStrGen(const size_t &length, const size_t &rndNum)
{
	const static std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::string result;
	result.resize(length);

	for (size_t i = 0; i < length; ++i)
		result[i] = charset[rndNum % charset.length()];

	return result;
}

// This section is for testing the LinkedList
int testingLinkedList()
{
	try
	{
		LinkedList<std::string> ll(std::string("Hallo"));
		ll.insertAtHead(std::string("Yo"));
		ll.insertAtHead(std::string("No"));
		ll.insertAtHead(std::string("No"));
		ll.insertAtHead(std::string("No"));
		ll.deleteNodesGivenData(std::string("No"));
		ll.deleteNodesGivenData(std::string("Hallo"));
		ll.printNodes();
		const auto getANode = ll.getNode(std::string("Yo"));
		if (getANode != nullptr)
		{
			std::cout << *(getANode) << std::endl;
		}
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

int testingHashTableWithBenchmark()
{
	// Constants
	static constexpr auto LOOP_ITERATIONS_POPULATION = 500;
	static constexpr auto UNIFORM_DIST_RND_MIN = 0;
	static constexpr auto UNIFORM_DIST_RND_MAX = 500000;
	static constexpr auto RND_STIRNGS_LEN = 5;
	static constexpr auto HASH_TABLE_CAP = 15;

	try
	{
		// Initialize the uniform int generator and create binds to use the generator and random string generator
		// as functions. This is done to have a uniform distribution of inputs so that a good hash can uniformaly distribute inputs
		// throughout the bins.
		std::random_device rd;																				 // obtain a random number from hardware
		std::mt19937 generator(rd());																		 // seed the generator
		std::uniform_int_distribution<std::size_t> distribution(UNIFORM_DIST_RND_MIN, UNIFORM_DIST_RND_MAX); // define the range
		auto roll_dice = std::bind(distribution, generator);
		const auto getRandomString = std::bind(&randomStrGen, std::placeholders::_1, std::placeholders::_2);

		// Init hash table
		HashTable<std::string, size_t> ht(HASH_TABLE_CAP);

		// Init vectors for randomly generated keys and values
		std::vector<std::string> rndStrs;
		std::vector<size_t> rndVals;
		rndStrs.clear();
		rndStrs.reserve(LOOP_ITERATIONS_POPULATION);
		rndVals.clear();
		rndVals.reserve(LOOP_ITERATIONS_POPULATION);

		for (size_t i = 0; i < LOOP_ITERATIONS_POPULATION; ++i)
		{
			rndStrs.emplace_back(getRandomString(RND_STIRNGS_LEN, roll_dice()));
			rndVals.emplace_back(roll_dice());
		}

		// Popluating Ht with benchmarking for put
		{
			Timer timer;
			for (size_t i = 0; i < LOOP_ITERATIONS_POPULATION; ++i)
			{
				ht.put(rndStrs.at(i), rndVals.at(i));
			}
		}

		// Some Informational print outs for debugging
		ht.get(rndStrs[0]).printNodes();
		ht.printBinsInfo();

		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

int testingBinarySearchTree()
{
	try
	{
		BinarySearchTree<float> bst;
		bst.insertNode(22);
		bst.insertNode(13);
		bst.insertNode(46);
		bst.insertNode(37);
		bst.insertNode(32);
		bst.insertNode(82);
		bst.insertNode(94);
		bst.insertNode(95);
		bst.insertNode(86);
		bst.insertNode(79);
		bst.insertNode(59);
		bst.insertNode(76);
		bst.insertNode(47);
		bst.insertNode(48);
		bst.insertNode(54);
		// std::cout << bst.DFS(5)->getData() << std::endl;
		std::cout << "Original Tree: \n";
		bst.printTree();
		std::cout << "removing leaf node case 1: \n";
		bst.removeNode(54);
		bst.printTree();
		std::cout << "\n\nremoving root node case 2: \n";
		bst.removeNode(22);
		bst.printTree();
		// std::cout << "\n\nremoving root node case 3: \n";
		// bst.printTree();
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

int testAVLTree()
{
	AVLTree<int> t(9);
	// t.insertNode(50);
	// t.insertNode(60);
	// t.insertNode(70);
	// t.insertNode(40);
	// t.insertNode(30);
	// t.insertNode(80);
	// t.insertNode(75);
	// t.insertNode(20);
	// t.insertNode(25);
	// t.insertNode(15);
	t.insertNode(10);
	t.insertNode(11);
	t.insertNode(12);
	t.insertNode(8);
	t.insertNode(7);
	t.insertNode(6);
	t.insertNode(5);
	t.insertNode(4);
	t.insertNode(3);
	t.insertNode(2);
	t.insertNode(1);
	t.insertNode(1);
	t.insertNode(19);
	t.insertNode(20);
	t.insertNode(21);
	t.insertNode(22);
	t.insertNode(23);
	t.insertNode(24);
	t.insertNode(25);
	t.insertNode(26);
	std::cout << t.findInorderSuccessor(t.getRoot()->getRight())->getData() << std::endl;
	std::cout << t.findInorderSuccessor(t.getRoot()->getRight())->getLeft() << std::endl;
	std::cout << t.findInorderSuccessor(t.getRoot()->getRight())->getRight() << std::endl;
	std::cout << t.findInorderSuccessor(t.getRoot()->getRight())->getParent() << std::endl;
	t.printTree();

	return 0;
}

int main(int argc, char *argv[])
{
	// return testingHashTableWithBenchmark();
	// return testingBinarySearchTree();
	return testAVLTree();
}