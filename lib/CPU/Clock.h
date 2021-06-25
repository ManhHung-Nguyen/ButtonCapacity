#pragma once
#include "Buffer.h"
#include "Counter.h"

class Clock : Buffer
{
	// tang gia tri 
	void inc(int i);
public:
	// tao ra 1 clock  mac dinh chua 16 counter
	Clock(int size = 16);
public:
	// them counter vao trong clock
	Clock& operator+=(Counter* counter);
	// gan thoi gian dang chuoi vao trong clock
	Clock& operator=(const char* text);
	// lay thoi gian
	operator char* ();
	// lay thoi gian o vi tri index
	int& operator[](int index);
public:
	enum { Milisecond, Second, Minute, Hour, Day, Month, Year };
	// lay thoi gian
	char* Time() const;
	// lay ngay thang nam
	char* Date() const;
	// them su kien vao clock
	void SetEvent(int index, ins_ptr event);
	// dat ngay thang nam
	void SetCalendar(int day, int month, int year);
	// lay nam, thang, ngay, gio, phut
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;
	int GetMilisecond() const;
	// lay thu
	int WeekDay() const;
public:
	// bat dau chay sysclock
	void Begin();
};

