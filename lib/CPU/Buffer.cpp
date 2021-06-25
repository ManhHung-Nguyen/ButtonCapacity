#include "Buffer.h"
// reset buffer
void Buffer::Reset(byte value) {
	for (int i = 0; i < capacity; i++) {
		data[i] = value;
	}
	it = data;
}
// chuyen ki tu sang so
template <class T>
const char* _convert(byte* buffer, T value) {
	byte* p = buffer;
	T a = value < 0 ? -value : value;
	*(--p) = 0;
	do {
		*(--p) = (a % 10) | 0x30;
		a /= 10;
	} while (a);
	if (value < 0) *(--p) = '-';
	return (const char*)p;
}
byte& Buffer::operator++() {
	return *(it++);
}
byte& Buffer::operator++(int) {
	return *it++;
}
byte& Buffer::operator[](int index) {
	return *(it = data + index);
}
const char* Buffer::FromInt64(long long value) {
	return _convert<long long>(data + capacity, value);
}
const char* Buffer::FromInt(int value) {
	return _convert<int>(data + capacity, value);
}
const char* Buffer::FromInt(int value, int space) {
	return _convert<int>(data + space, value);
}
byte* Buffer::Handle() {
	return data;
}
Buffer::operator char* () {
	*it = 0;
	return (char*)Handle();
}
void Buffer::_copy(const byte* src, int len) {
	for (int i = 0; i < len; i++) {
		byte b = src[i];
		*it++ = b;
	}
}
void Buffer::_copy(const char* src) {
	while (*src) {
		*it++ = *src++;
	}
}
