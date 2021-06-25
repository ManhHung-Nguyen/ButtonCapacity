#pragma once
#include "Types.h"

class Counter
{
protected:
	int max_value;
	int current_value;
	ins_ptr interupt;
public:
	// tao mot counter va dang ki vao sysclock
	Counter();
public:
	// reset counter
	void Reset(ins_ptr callback = 0, int interval = 0);
	// dem lui den gia tri limit thi thuc hien event
	void CountDown();
};

