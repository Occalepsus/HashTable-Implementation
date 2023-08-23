#include "HashTable.h"

#include <iostream>
#include <cassert>

int main() {
	HashTable<int, 10> testTable{};

	assert(testTable.empty());
	assert(!testTable.contains(0));
	assert(testTable.find(customHash(0)) == nullptr);
	testTable.insert(0);
	assert(!testTable.empty());
	assert(testTable.size() == 1);
	assert(testTable.contains(0));
	assert(testTable.find(customHash(0)) != nullptr);
	testTable.insert(3);
	assert(testTable.contains(3));
	assert(!testTable.contains(10));
	testTable.insert(10);
	testTable.insert(30);
	assert(testTable.size() == 4);
	assert(testTable.contains(10));
	assert(*testTable.find(0) == 0);
	assert(*testTable.find(0) != 10);
	assert(*testTable.find(10) != 0);
	assert(*testTable.find(10) == 10);
	assert(*testTable.find(30) != 0);
	assert(*testTable.find(30) != 10);
	testTable.remove(10);
	assert(testTable.size() == 3);
	assert(!testTable.contains(10));
	assert(testTable.contains(30));
	assert(*testTable.find(30) == 30);

	std::cout << "All tests passed!" << std::endl;

	return 0;
}