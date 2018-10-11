#pragma once
#include<vector>

typedef int THash;

template <class TKey, class TValue>
class HashTable {
public:
	HashTable(unsigned length, THash(*hashFunction)(TKey key));

	bool hasKey(TKey key);
	TValue& operator[](TKey);
	void insert(TKey key, TValue value);
	TValue& remove(TKey key);

protected:
	struct Container {
		Container() 
			: isUsed(false)
		{ }
		Container(TKey key, TValue value)
			: key(key), value(value), isUsed(true), next(NULL)
		{ }

		Container *next;
		bool isUsed;

		TKey key;
		TValue value;
	};

	inline THash getHash(TKey key);
	THash(*_hashFunction)(TKey key);

	unsigned _currentLength;
	std::vector<Container> _vec;
};



template <class TKey, class TValue>
HashTable<TKey, TValue>::HashTable(unsigned length, THash(*hashFunction)(TKey key)) 
	: _vec(length), _hashFunction(hashFunction), _currentLength(0)
{ }

template <class TKey, class TValue>
inline THash HashTable<TKey, TValue>::getHash(TKey key) {
	return _hashFunction(key) % _vec.length;
}

template <class TKey, class TValue>
bool HashTable<TKey, TValue>::hasKey(TKey key) {
	THash hash = getHash(key);
	Container *container = &_vec[hash];

	do {
		if (container->key == key)
			return container->isUsed;

		container = container->next;
	} while (container != NULL);

	return false;
}

template<class TKey, class TValue>
inline TValue& HashTable<TKey, TValue>::operator[](TKey key)
{
	Container *container = &_vec[getHash(key)];
	while (container->key != key)
		container = container->next;

	return container->value;
}

template<class TKey, class TValue>
void HashTable<TKey, TValue>::insert(TKey key, TValue value)
{
	THash hash = getHash(key);
	Container *container = &_vec[hash];
	
	do {
		if (container->isUsed)
			container = container->next;
	} while (container != NULL);

	container = new Container(key, value);
	_currentLength++;
}