#pragma once
#include <iostream>
using namespace std;

template <class Key, class Value>
class Map {
private:
	struct Pair {
		Key key;
		Value value;
		int index;
	};
	Pair* v;
	int counter, capacity;
public:
	Map() {
		this->v = new Pair[1];
		this->counter = 0;
		this->capacity = 1;
	}
	~Map() {
		delete[] this->v;
	}

	Value& operator[](const Key& k) {
		for (int i = 0; i < this->counter; i++) {
			if (this->v[i].key == k) {
				return this->v[i].value;
			}
		}
		if (this->counter == this->capacity) {
			Pair* newV = new Pair[this->capacity * 2];
			for (int i = 0; i < this->counter; i++) {
				newV[i] = this->v[i];
			}
			delete[] this->v;
			this->v = newV;
			this->capacity *= 2;
		}
		this->v[this->counter].key = k;
		this->v[this->counter].index = this->counter;
		return this->v[this->counter++].value;
	}

	void Set(Key k, Value v) {
		for (int i = 0; i < this->counter; i++) {
			if (this->v[i].key == k) {
				this->v[i].value = v; 
				return; 
			}
		}

		if (this->counter == this->capacity) {
			Pair* newV = new Pair[this->capacity * 2];
			for (int i = 0; i < this->counter; i++) {
				newV[i] = this->v[i];
			}
			delete[] this->v;
			this->v = newV;
			this->capacity *= 2;
		}

		this->v[this->counter].key = k;
		this->v[this->counter].value = v;
		this->v[this->counter].index = this->counter;
		this->counter++;
	}


	bool Get(const Key& k, const Value& v) {
		for (int i = 0; i < this->counter; i++) {
			if (this->v[i].key == k && this->v[i].value == v) {
				return true;
			}
		}
		return false;
	}

	int Count() {
		return this->counter;
	}

	void Clear() {
		delete[] this->v;
		this->v = new Pair[1];
		this->counter = 0;
		this->capacity = 1;
	}

	bool Delete(const Key& k) {
		int poz = 0;
		bool ok = false;
		for (int i = 0; i < this->counter; i++) {
			if (this->v[i].key == k) {
				poz = i;
				ok = true;
			}
		}
		for (int i = poz; i < this->counter - 1; i++) {
			this->v[i].key = this->v[i + 1].key;
			this->v[i].value = this->v[i + 1].value;
		}
		this->counter--;
		return ok;
	}

	bool Includes(const Map<Key, Value>& map) {
		bool ok;
		for (int i = 0; i < map.counter; i++) {
			ok = false;
			for (int j = 0; j < this->counter; j++) {
				if (map.v[i].key == this->v[j].key && map.v[i].value == this->v[j].value) {
					ok = true;
					break;
				}
			}
			if (ok == false)
				return false;
		}
		return true;
	}

	const Pair* begin() { return &this->v[0]; }
	const Pair* end() { return &this->v[this->counter]; }
};

int main()
{
    Map<int, const char*> m;
    m[10] = "C++";
    m[20] = "test";
    m[30] = "Poo";

    for (auto [key, value, index] : m)
    {
        printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
    }
	printf("\n");

    m[20] = "result";
    for (auto [key, value, index] : m)
    {
        printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
    }
	printf("\n");

	m.Set(30, "adam");
	m.Set(35, "123");
	m.Set(40, "Daniel");

	for (auto [key, value, index] : m)
	{
		printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
	}

	printf("Count: %d\n", m.Count());
	printf("\n%d\n", m.Get(30, "adam"));
	printf("%d\n\n", m.Get(30, "tessss"));

	m.Delete(30);
	m.Delete(30);
	for (auto [key, value, index] : m)
	{
		printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
	}
	printf("Count: %d\n\n", m.Count());

	m.Clear();

	m.Set(1, "val1");
	m.Set(2, "val2");
	m[10] = "val3";
	for (auto [key, value, index] : m)
	{
		printf("Index:%d, Key=%d, Value=%s\n", index, key, value);
	}
	printf("Count: %d\n\n", m.Count());

	Map<int, const char*> n;
	n.Set(1, "val1");
	if (m.Includes(n))
		printf("n este inclus in m\n");
	else
		printf("n NU este inclus in m\n");

	
	Map<int, const char*> p;
	p.Set(2, "val222");
	if (m.Includes(p))
		printf("p este inclus in m\n");
	else
		printf("p NU este inclus in m\n");

    return 0;
}

