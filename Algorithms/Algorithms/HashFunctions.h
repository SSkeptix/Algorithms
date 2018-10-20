#pragma once

#include <string>
#include "HashTable.h"

THash hashFunction(int key) {
	return (THash)key;
}

THash hashFunction(long key) {
	return (THash)key;
}

THash hashFunction(float key) {
	return (THash)key;
}

THash hashFunction(double key) {
	return (THash)key;
}

const unsigned short LettersCount = 5;
THash hashFunction(std::string key) {
	THash hash = 0;
	int length = key.length();
	for (int i = 0; (i < length && i < LettersCount); i++)
		hash += (THash)(std::pow(96, LettersCount - i - 1) * (key[i] - 32));
	return hash;
}