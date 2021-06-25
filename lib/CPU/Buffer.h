#pragma once

#include "Types.h"
class Buffer
{
protected:
	byte* data;
	byte* it;
	int capacity;
public:
	Buffer(int size = 64, byte* src = 0) {
		if (src == 0) {
			src = new byte[size];
		}
		data = it = src;
		capacity = size;
	}
protected:
	// copy mot chuoi vao buffer voi do dai len
	void _copy(const byte* src, int len = 0);
	// copy mot chuoi vao buffer chua biet do dai
	void _copy(const char* src);
public:
	virtual void Reset() { it = data; }
	// reset buffer
	void Reset(byte value);
	// tro toi mot vi tri bat ki
	byte* Seek(int position) {
		return it = data + position;
	}
public:
	// lay vi tri con tro data
	virtual byte* Handle();
public:
	// chuyen so nguyen 8 byte sang chuoi
	const char* FromInt64(long long value);
	// chuyen so nguyen sang chuoi
	const char* FromInt(int value);
	// chuyen so nguyen sang chuoi
	const char* FromInt(int value, int space);
public:
	operator char* ();
	byte& operator++();
	byte& operator++(int);
	byte& operator[](int index);
	// them ki tu vao buffer
	Buffer& operator<<(const char* src) {
		_copy(src);
		return *this;
	}
	// them so nguyen vao buffer
	Buffer& operator<<(int value) {
		_copy(FromInt(value));
		return *this;
	}
};

