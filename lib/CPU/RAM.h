#pragma once
#include "Types.h"

class Memory
{
	int capacity;
	int available;
	byte* buffer;
public:
	Memory(int size, byte* buffer = 0);
	operator byte* () { return buffer; }

	int Capacity() const { return this->capacity; }
	byte* Handle() const { return buffer; }

	byte* Create(int size);
	void Delete(int size);
	void Reset(byte value = 0);

};

