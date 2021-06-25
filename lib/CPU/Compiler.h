#pragma once
#include "Types.h"
class Compiler
{
protected:
	int flags;

	enum { NONE, ERR, SUCCESS, FUNTION = 4, STRING = 8, ENDSTR, PARAM, JOBJECT = 16, JLIST = 32};
	bool Has(int f) {
		return flags & f;
	}
	void Invert(int f) {
		flags ^= f;
	}
	int Reset(int f) {
		flags &= ~f;
		return NONE;
	}
	int Set(int f) {
		flags |= f;
		return f;
	}
public:
	// check byte b
	int Compile(byte b);
};

