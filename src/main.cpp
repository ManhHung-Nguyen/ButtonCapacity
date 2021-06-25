#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "CPU.h"
#include "Log.h"

Adafruit_MPR121 cap_sense = Adafruit_MPR121();

#define MPR121_ADDR 0x5A
#define ROW 3
#define COL 2
#define buttonsCount 6

Clock SysClock;
volatile bool readFlag = false;
int rowValue[ROW];
int colValue[COL];
int dataRow[ROW];
int dataCol[COL];
short buttonDownCount[buttonsCount];
int down = -1;

int clock_delay() {
  delayMicroseconds(100);
  return 10;
}

void resetDownCount() {
    for (int i = 0; i < buttonsCount; i++) {
        buttonDownCount[i] = 0;
    }
}

void begin() {
    int v = 5;
    while(v--){
        for(int i = 0; i < ROW; i++) {
            dataRow[i] = cap_sense.filteredData(i);
        };
        for(int i = 0; i < COL; i++) {
            dataCol[i] = cap_sense.filteredData(i+ROW);
        };
    };
    
}
int scanColumn() {
    for(int i = 0; i < COL; i++) {
        colValue[i] = cap_sense.filteredData(ROW+i);
    }
    int min = colValue[0];
    int add = -1;
    for(int i = 0; i < COL; i++) {
        if(dataCol[i] - colValue[i] > 10) {
            if(colValue[i] <= min) {
                min = colValue[i];
                add = i;
            }
        }
    }
    return add;
}
void scanRow() {
    for(int i = 0; i < ROW; i++) {
        rowValue[i]= cap_sense.filteredData(i);
        if (dataRow[i] - rowValue[i] > 50) {
            int c = scanColumn();
            if (c != -1) {
                buttonDownCount[i * 2 + c]++;
            }
        }
    }
}

void updateSensedFlagSet()
{
    readFlag = true;
}

void OnKeyDown(int k) {
    log << k + 1 << endl;
} 
void OnKeyUp(int k) {

}
void on_second() {
	log<<SysClock.Time() <<endl;
}
void RaiseEvent() {
    int m = 0;
    for (int i = 1; i < buttonsCount; i++) {
        if (buttonDownCount[i] > buttonDownCount[m]) {
            m = i;
        }
    }
    int k = -1;
    if (buttonDownCount[m] > 1) {
        k = m;
    }
    resetDownCount();
    if (k >= 0) {
        if (k != down) {
            OnKeyDown(k);
            down = k;
        }
        return;
    }
    if (down >= 0) {
        k = down;
        down = -1;
        OnKeyUp(k);
    }
}
void scan() {
    int m = SysClock[Clock::Milisecond];
    if((m & 3) == 0) {
        scanRow();
    }
    if ((m & 127) == 0) {
        RaiseEvent();
    }
}
void setup()
{
    Serial.begin(9600);
    while(!Serial);
    if(!cap_sense.begin(MPR121_ADDR))
    {
        Serial.println("Error setting up MPR121");
        while(1);
    }
    Serial.println("Ready to sense");
    attachInterrupt(digitalPinToInterrupt(2), updateSensedFlagSet, FALLING);

    begin();
    resetDownCount();
    
    SysClock.SetEvent(Clock::Milisecond, scan);
    SysClock.SetEvent(Clock::Second, on_second);
    SysClock.Begin();
}

void loop()
{

}

