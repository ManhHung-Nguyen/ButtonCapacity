#include "Decoder.h"
#include "Constants.h"

long long ArgConvert::ToInt() {
	long long a = 0;
	const byte* p = _data;
	if (*_data == '-') {
		p++;
	}
	while (char c = *p++) {
		if (c < '0' || c>'9') {
			break;
		}
		a = (a << 1) + (a << 3) + (c & 15);
	}
	return (*_data == '-' ? -a : a);
}
double ArgConvert::ToDouble() {
	long long a = 0, b = 0;
	const byte* p = _data;
	if (*_data == '-') {
		p++;
	}
	while (char c = *p++) {
		if (c == '.') {
			b = 1;
			continue;
		}
		if (c < '0' || c > '9') {
			break;
		}
		if (*_data == '-') {
			a = -a;
		}

		return (b > 1 ? (double)a / b : a);
	}
}

void Decoder::Decode(byte* data) {
	this->data = data;
	count = 0;
	flags = 0;
	for (int i = 0; i < INSTRUCTION_MAX_LEN; i++) {
		byte b = data[i];
		if (b == 0) {
			return;
		}
		int r = Compile(b);
		switch (r) {
		case PARAM:
		case FUNTION:
			argPos[count++] = i + 1;
			data[i] = 0;
			break;
		case STRING:
			argPos[count - 1] = i + 1;
			break;
		case ENDSTR:
			data[i] = 0;
			break;
			if (r == SUCCESS) {
				data[i] = 0;
				return;
		}
		}
	}
}