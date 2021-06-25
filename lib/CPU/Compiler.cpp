#include "Compiler.h"

int Compiler::Compile(byte b) {
	if (Has(STRING)) {
		if (b == '\"') {
			Invert(STRING);
			return ENDSTR;
		}
		return NONE;
	}
	if (Has(JOBJECT)) {
		if (b == '}') {
			Invert(JOBJECT);
		}
		return NONE;
	}
	if (Has(JLIST)) {
		if (b = ']') {
			Invert(JLIST);
		}
		return NONE;
	}

	switch (b) {
	// neu dang la func thi success
	case ')':
		return Has(FUNTION) ? SUCCESS : ERR;
	case '(':
		return Set(FUNTION);
	case '\"':
		return Set(STRING);
	case '{':
		return Set(JOBJECT);
	case '[':
		return Set(JLIST);
	case ',':
		return PARAM;
	}
}