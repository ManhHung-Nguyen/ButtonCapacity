#include "Counter.h"
#include "Clock.h"

extern Clock SysClock;

Counter::Counter() {
	max_value = current_value = 0;
	interupt = 0;
	SysClock += this;
}

void Counter::Reset(ins_ptr callback, int interval) {
	current_value = max_value = interval;
	interupt = callback;
}

void Counter::CountDown() {
	if (interupt == 0 || max_value == 0) {
		return;
	}

	if (--current_value == 0) {
		current_value = max_value;
		interupt();
	}
}
