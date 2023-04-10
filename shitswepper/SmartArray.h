#pragma once
#include <string.h>
#include <iostream>
template <class DataType>
class SmartArray //Ya ne ponyal zachem ya yeho napisal, deque luchshe budet v 100 raz, hotya budet zhrat bolse pamyati no zato slozhnost budet menyshe v 1000 raz vmesto O(n) O(1) ya dumayu.
{
public:
	template<typename T>
	int find(T& data) {
		for (unsigned i{}; i < size; ++i) {
			if (this->data[i] == data) {
				return i;
			}
		}
		return -1;
	}				
	unsigned getSize() const { return size; }
	SmartArray() { this->data = new DataType[1]; }
	template<typename T>
	void push_front(T& data) {
		if (capacity == size)
			this->tsttt(capacity * 2);
		for (unsigned i{ size }; i > 1; --i) {
			this->data[i] = this->data[i - 1];
		}
		this->data[0] = data;
		size++;
	}
	template<typename T>
	void push_back(T& data) {
		if (capacity == size)
			this->tsttt(capacity * 2);
		this->data[size++] = data;
	}
	template<typename T>
	void push_front(const T& data) {
		if (capacity == size)
			this->tsttt(capacity * 2);
		for (unsigned i{ size }; i > 1; --i) {
			this->data[i] = this->data[i - 1];
		}
		this->data[0] = data;
		size++;
	}
	template<typename T>
	void push_back(const T& data) {
		if (capacity == size)
			this->tsttt(capacity * 2);
		this->data[size++] = data;
	}
	DataType& operator[](const unsigned& u) { return data[u]; }
	void clear() {
		if (data) {
			delete[] data;
		}
		capacity = 1;
		data = new DataType[capacity];
		size = 0;
	}
	~SmartArray() {
		if (data) {
			delete[] data;
		}
	}
private:
	void tsttt(unsigned capacity) {

		try {
			DataType* buf = new DataType[capacity];
			memcpy(buf, this->data, sizeof(DataType) * size);
			delete[] data;
			data = buf;
			buf = nullptr;
			this->capacity = capacity;
		}
		catch (std::bad_alloc& a) {
			std::cout << "ALLOCATION FAILED " << a.what() << '\n';
		}
		catch (std::exception& e) {
			std::cout << "SOMETHING WENT WRONG " << e.what() << '\n';
		}

	}
	DataType* data;
	unsigned size = 0;
	unsigned capacity = 1;
};

