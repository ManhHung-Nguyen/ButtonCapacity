#pragma once
#include "Types.h"
#include "Compiler.h"
class ArgConvert
{
	const byte* _data;
	// chuyen du lieu sang kieu int
	long long ToInt();
	// chuyen du lieu sang double
	double ToDouble();
public:
	operator int() {
		return (int)ToInt();
	}
	operator long long() {
		return ToInt();
	}
	operator double() {
		return ToDouble();
	}
	operator char* () {
		return (char*)(_data);
	}

	ArgConvert& operator=(const byte* data) {
		_data = data;
		return *this;
	}

};
class Decoder : Compiler
{
	// mang chua tham so toi da 8 tham so
	byte argPos[8];
	// dem so luong tham so 
	byte count;

	ArgConvert arg;
	byte* data;
public:
	void Decode(byte* data);
public:
	int ArgCount() const { return count; }
	ArgConvert& operator[](int index) {
		return arg = (data + argPos[index]);
	}
	char* operator()() {
		return (char*)data;
	}
};

