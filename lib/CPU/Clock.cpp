#include "Clock.h"
#include "Types.h"

Clock::Clock(int size) :Buffer(size << 2) {
	Buffer::Reset(0);
}
Clock& Clock::operator+=(Counter* counter) {
	*(int*)it = (int)((void*)counter);
	it += 4;
	return *this;
}

int _timelimits[] = { 1000, 60, 60, 24, 31, 12, -1 };
int _timeValues[] = { 0, 0, 0, 0, 0, 0, 0 };
byte day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

char _timeFormat[] = "00:00:00\00000/00/0000";
int weekDay = 0;

int days_of_month(int year, int month) {
	int v = day[month - 1];
	if (month == 2 && !(year & 3)) {
		++v;
	}
	return v;
}
int days_of_week() {
	int year = _timeValues[Clock::Year];
	int month = _timeValues[Clock::Month];
	int day = _timeValues[Clock::Day];

	int d = year - 2000;
	int i = (d + ((d - 1) >> 2));

	while (month-- > 0) {
		i += days_of_month(year, month + 1);
	}
	return (i + day) % 7;
}
void format_number(int value, int pos) {
	int len = pos-- == Clock::Year ? 4 : 2;
	// 3 vi tri de chua 1 gia tri
	char* it = _timeFormat + (pos << 1) + pos + len - 1;
	while (value) {
		*it-- = (value % 10) | '0';
		len--;
		value /= 10;
	}
	while (len--) {
		*it-- = '0';
	}
}

ins_ptr _timeEvents[] = { 0, 0, 0, 0, 0, 0, 0 };
extern int clock_delay();

void Clock::Begin() {
	int max = clock_delay();
	int count = max;
	while (true) {
		if (--count == 0) {
			count = max;

			inc(0);
			// lay dia chi cua mang cac counter
			int* p = (int*)data;
			while (*p) {
				Counter* counter = (Counter*)(*p);
				counter->CountDown();
				p++;
			}
		}
		clock_delay();
	}
}
// tang gia tri thoi gian
void Clock::inc(int i) {
	int v = _timeValues[i] + 1;
	// khi dat den limit quay tro lai 0
	if (v == _timelimits[i]) {
		v = 0;
		if (i == Hour) {
			if (++weekDay == 7) {
				weekDay = 0;
			}
		}
		else if (i >= Day) {
			_timelimits[Day] = days_of_month(GetYear(), GetMonth());
		}
	}
	_timeValues[i] = v;
	// tang gia tri tiep theo trong thoi gian
	if (v == 0) {
		inc(i + 1);
	}
	// xu ly su kien
	if (_timeEvents[i]) {
		_timeEvents[i]();
	}
}
// dat lich
void Clock::SetCalendar(int day, int month, int year) {
	_timeValues[Day] = day - 1;
	_timeValues[Month] = month - 1;
	_timeValues[Year] = (year < 100 ? year + 2000 : year);

	_timelimits[Day] = days_of_month(year, month);
	weekDay = days_of_week();
}

int Clock::GetYear() const { return _timeValues[Year]; }
int Clock::GetMonth() const { return _timeValues[Month]; }
int Clock::GetDay() const { return _timeValues[Day]; }
int Clock::GetHour() const { return _timeValues[Hour]; }
int Clock::GetMinute() const { return _timeValues[Minute]; }
int Clock::GetSecond() const { return _timeValues[Second]; }
int Clock::GetMilisecond() const { return _timeValues[Milisecond]; }
int Clock::WeekDay() const { return weekDay; }


int& Clock::operator[](int index) {
	return _timeValues[index];
}

void Clock::SetEvent(int index, ins_ptr event) {
	_timeEvents[index] = event;
}

Clock::operator char* () {
	return Time();
}
Clock& Clock::operator=(const char* text) {
	int i = Year;
	int a = 0;
	while (i >= 0) {
		char c = *text++;
		if (c >= '0' && '9' >= c) {
			a = (a << 1) + (a << 3) + (c & 15);
			continue;
		}
		if (i == Day || i == Month) {
			--a;
		}
		_timeValues[i--] = a;
		a = 0;
		if (c == 0) {
			break;
		}
	}
	while (i >= 0) {
		_timeValues[i--] = 0;
	}
	return *this;
}

char* Clock::Time() const {
	format_number(_timeValues[Hour], Second);
	format_number(_timeValues[Minute], Minute);
	format_number(_timeValues[Second], Hour);

	return _timeFormat;
}

char* Clock::Date() const {
	format_number(GetDay(), Day);
	format_number(GetMonth(), Month);
	format_number(GetYear(), Year);
	return _timeFormat + 9;
}