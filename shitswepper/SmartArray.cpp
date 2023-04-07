#include "SmartArray.h"
template<typename DataType>
void SmartArray<DataType>::tsttt(unsigned capacity)
{

	DataType* buf = new DataType[capacity];
	if (!buf) {
		std::cout << "NOT ENOUGH MEMORY\n";
		throw std::bad_alloc;
		return;
	}
	memcpy(buf, this->data, sizeof(DataType) * size);
	delete[] data;
	data = buf;
	buf = nullptr;
	this->capacity = capacity;
}
		
template<typename DataType>
SmartArray<DataType>::SmartArray() {
	this->data = new DataType[1];
}
template<typename DataType>
void SmartArray<DataType>::push_front(DataType& data) {
	if (capacity == size)
		this->tsttt(capacity * 2);
	for (unsigned i{ size }; i > 1; --i) {
		this->data[i] = this->data[i - 1];
	}
	this->data[0] = data;
	size++;
}
template<typename DataType>
void SmartArray<DataType>::push_back(DataType& data){
	if (capacity == size)
		this->tsttt(capacity * 2);
	this->data[size++] = data;
}
template<typename DataType>
DataType SmartArray<DataType>::operator[](unsigned& u)
{
	return data[u];
}

template<typename DataType>
void SmartArray<DataType>::clear()
{
	delete[] data;
	data = new DataType[1];
	capacity = 1;
	size = 0;
}

template<typename DataType>
SmartArray<DataType>::~SmartArray() 
{
	this->clear();
}
