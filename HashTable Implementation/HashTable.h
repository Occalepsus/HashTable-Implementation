#pragma once

#include <memory>
#include <array>
#include <cmath>

template<typename T>
class LinkedList {
public:
	size_t hash;
	std::unique_ptr<T> valuePtr;
	std::unique_ptr<LinkedList<T>> next;

	LinkedList(size_t hash, T element) : hash{ hash }, valuePtr{ std::make_unique<T>(element) } {}
};

template<typename T, size_t S = 1024>
class HashTable {
private:
	size_t _size{ 0 };
	std::array<std::unique_ptr<LinkedList<T>>, S> hashTable;

public:
	HashTable() = default;

	void insert(T&& element);
	void remove(size_t hash);
	void remove(T const& element);
	// Const so that the user cannot modify the value, so that the hash remains the same
	const T* find(size_t hash) const;
	bool contains(size_t hash) const;
	bool contains(T const& element) const;

	bool empty() const { return _size == 0; }
	size_t size() const { return _size; }
};

template<typename T>
extern size_t customHash(T value) {
	return static_cast<size_t>(value);
}

#include "HashTable.cpp"
