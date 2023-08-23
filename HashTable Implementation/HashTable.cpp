#pragma once

#include "HashTable.h"

template<typename T, size_t S>
void HashTable<T, S>::insert(T&& element) {
	size_t hash{ customHash(element) };

	auto linkedListPtr{ hashTable[hash % S].get() };
	if (linkedListPtr != nullptr) {
		while (linkedListPtr->next != nullptr) {
			linkedListPtr = linkedListPtr->next.get();
		}
		linkedListPtr->next = std::make_unique<LinkedList<T>>(hash, std::move(element));
	}
	else {
		hashTable[hash % S] = std::make_unique<LinkedList<T>>(hash, std::move(element));
	}
	_size++;
}

template<typename T, size_t S>
void HashTable<T, S>::remove(size_t hash) {
	auto linkedListPtr{ hashTable[hash % S].get() };
	if (linkedListPtr == nullptr) {
		return;
	}
	else {
		if (linkedListPtr->hash == hash) {
			hashTable[hash % S] = std::move(linkedListPtr->next);
			_size--;
			return;
		}
		while (linkedListPtr->next != nullptr) {
			auto nextPtr{ linkedListPtr->next.get() };
			if (nextPtr->hash == hash) {
				linkedListPtr->next = std::move(nextPtr->next);
				_size--;
				return;
			}
			linkedListPtr = linkedListPtr->next.get();
		}
	}
}

template<typename T, size_t S>
void HashTable<T, S>::remove(T const& element) {
	remove(customHash(element));
}

template<typename T, size_t S>
const T* HashTable<T, S>::find(size_t hash) const {
	auto linkedListPtr{ hashTable[hash % S].get() };
	if (linkedListPtr == nullptr) {
		return nullptr;
	}
	else {
		if (linkedListPtr->hash == hash) {
			return linkedListPtr->valuePtr.get();
		}
		while (linkedListPtr->next != nullptr) {
			linkedListPtr = linkedListPtr->next.get();
			
			if (linkedListPtr->hash == hash) {
				return linkedListPtr->valuePtr.get();
			}
		}
		return nullptr;
	}
}

template<typename T, size_t S>
bool HashTable<T, S>::contains(size_t hash) const {
	return find(hash) != nullptr;
}

template<typename T, size_t S>
bool HashTable<T, S>::contains(T const& element) const {
	return find(customHash(element)) != nullptr;
}