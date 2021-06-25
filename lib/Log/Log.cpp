#include "Log.h"

#ifdef ARDUINO
    #ifdef STM32
        HardwareSerial LogSerial(PB7, PB6);
    #else
        #define LogSerial   Serial
    #endif
    Debug::Debug() {
        _port = &LogSerial;
    }
#endif