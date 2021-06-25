#include "RAM.h"

Memory::Memory(int size, byte* buffer) {
	capacity = available = size;
	this->buffer = buffer ? buffer : new byte[size];
}

byte* Memory::Create(int size) {
	return buffer + (available -= size);
}
void Memory::Delete(int size) {
	available += size;
}
void Memory::Reset(byte value) {
	for (int i = 0; i < capacity; i++) {
		buffer[i] = value;
	}
}
