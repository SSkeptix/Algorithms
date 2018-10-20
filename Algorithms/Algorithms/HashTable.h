#pragma once
#include <vector>
#include <iostream>

typedef int THash;

template <class TKey, class TValue>
class HashTable {
public:
	HashTable(unsigned length, THash(*hashFunction)(TKey key));
	~HashTable();

	bool hasKey(TKey key);
	TValue& operator[](TKey);

	TValue& insert(TKey key, TValue value);
	TValue& get(TKey key);
	TValue& remove(TKey key);

	void toJson(std::ostream& out);

protected:
	struct Container {
		Container() 
			: next(NULL), isUsed(false)
		{ }

		Container(TKey key, TValue value)
			: key(key), value(value), next(NULL), isUsed(true)
		{ }

		void toJson(std::ostream& out);

		Container *next;

		TKey key;
		TValue value;
		bool isUsed;
	};

	inline THash getHash(TKey key);
	THash(*_hashFunction)(TKey key);

	std::vector<Container> _vec;
};



template <class TKey, class TValue>
HashTable<TKey, TValue>::HashTable(unsigned length, THash(*hashFunction)(TKey key)) 
	: _vec(length), _hashFunction(hashFunction)
{ }

template <class TKey, class TValue>
HashTable<TKey, TValue>::~HashTable() {
	Container *current, *toRemove;

	for (unsigned i = 0; i < _vec.size(); i++) {
		current = _vec[i].next;
		while (current != NULL) {
			toRemove = current;
			current = current->next;
			delete toRemove;
		}
	}
}

template <class TKey, class TValue>
inline THash HashTable<TKey, TValue>::getHash(TKey key) {
	return _hashFunction(key) % _vec.size();
}

template <class TKey, class TValue>
bool HashTable<TKey, TValue>::hasKey(TKey key) {
	THash hash = getHash(key);
	Container *container = &_vec[hash];

	while (true) {
		if (container->key == key)
			return container->isUsed;
		if (container->next == NULL)
			return false;

		container = container->next;
	}
}

template<class TKey, class TValue>
inline TValue& HashTable<TKey, TValue>::operator[](TKey key) {
	return hasKey(key)
		? get(key)
		: insert(key, TValue());
}

template<class TKey, class TValue>
TValue& HashTable<TKey, TValue>::insert(TKey key, TValue value) {
	THash hash = getHash(key);
	Container *container = &_vec[hash];

	while (true) {
		if (!container->isUsed) {
			container->isUsed = true;
			container->key = key;
			container->value = value;
			return container->value;
		}
		if (container->next == NULL) {
			container->next = new Container(key, value);
			return container->next->value;
		}
		container = container->next;
	}
}

template<class TKey, class TValue>
TValue& HashTable<TKey, TValue>::get(TKey key) {
	THash hash = getHash(key);
	Container *container = &_vec[hash];

	while (!(container->key == key && container->isUsed))
		container = container->next;

	return container->value;
}

template<class TKey, class TValue>
TValue& HashTable<TKey, TValue>::remove(TKey key) {
	THash hash = getHash(key);
	Container *container = &_vec[hash];

	while ( !(container->key == key && container->isUsed) )
		container = container->next;

	container->isUsed = false;
	return container->value;
}

template<class TKey, class TValue>
inline void HashTable<TKey, TValue>::Container::toJson(std::ostream& out) {
	out << "{ \"Key\": " << key
		<< ", \"Value\": " << value
		<< ", \"IsUsed\": " << (isUsed ? "true" : "false")
		<< ", \"Next\": ";
	
	if (next == NULL)
		out << "null";
	else
		next->toJson(out);

	out << " }";
}

template<class TKey, class TValue>
void HashTable<TKey, TValue>::toJson(std::ostream& out) {
	Container *container;
	out << "[ ";
	for (int i = 0; i < _vec.size() - 1; i++) {
		_vec[i].toJson(out);
		out << ", ";
	}
	if (_vec.size() > 0)
		_vec[_vec.size() - 1].toJson(out);

	out << " ]";
}

